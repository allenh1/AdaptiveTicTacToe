#ifndef GAMETHREAD_H
#define GAMETHREAD_H
/**
 * The game thread controls the board. The UI is a member variable of this class.
 * The game thread has some responsibilities:
 *
 * 1. Take the user input and correctly handle it (done by the main window connections)
 * 2. Handle the rules of the game.
 * 3. This thread also controls the A.I. for the game.
*/
#define ROWS 3
#define COLS 3
#include <iostream>
#include <QThread>
#include <QFile>
#include <QString>
#include <QList>
#include <QDataStream>
#include <QObject>

/**
 * This struct contains the data to be saved. For the AI
*/
enum Board { X=88, O=79, B=' ' };

class MoveData
{
public:
    MoveData(){}
    quint8 row = 0;//row moved to
    quint8 col = 0;//row moved to

    quint8 lastRow = 0;
    quint8 lastCol = 0;
    double probability = 0;

    bool operator==(const MoveData& other)
    {
        return other.row == row &&
               other.col == col &&
               other.lastRow == lastRow &&
               other.lastCol == lastCol;
    }

    bool operator=(const MoveData& m2)
    {
        row = m2.row;
        col = m2.col;
        lastRow = m2.lastRow;
        lastCol = m2.lastCol;
        return true;
    }

    quint64 count = 0;
    void incCount(){ count++; }
    QString asString;

    const QString& toString(){ return asString = QString("Countered (" + QString().number(lastRow) + ", " + QString().number(lastCol) +
                                                         ")  with (" + QString().number(row) + ", " + QString().number(col) + ") ") +
                                                         QString().number(count) + " times."; }
};

struct MoveSequence
{
    QList<MoveData> sequence;
};

class GameThread : public QThread
{
	Q_OBJECT

public:
	GameThread(int argc, char ** argv);

	void run();
    inline void addMoveToList(MoveData toAdd);

	Q_SIGNAL void ioError(QString);
	Q_SIGNAL void gotMove();
    Q_SIGNAL void aiMove(quint8,quint8);
    Q_SIGNAL void aiHasMoved();
    Q_SLOT void closeThread();
	Q_SLOT void aiTurn();
	Q_SLOT void receiveMove(quint8,quint8);

    bool tryPath(QList<MoveData> * pAll, MoveSequence * sequence);
    void saveData();

    bool hasWinner(QString * winner);
    bool hasWinner(Board board[ROWS][COLS], QString * winner);
    bool isOccupied(quint8 row, quint8 col);
private:
    Board m_board[ROWS][COLS];
	int m_argc;
	char ** m_argv;
	QFile  * pData;
    QList<MoveData> * pKnowledge;
	bool m_finished;
    bool m_wake = true;
    MoveData * pLastMove;
};
#endif
