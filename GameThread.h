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

#include <QThread>
#include <QFile>
#include <QString>
#include <QHash>
#include <QDataStream>

#include "boardUI.h"

/**
 * This struct contains the data to be saved. For the AI
*/
struct moveData
{
	quint8 row;//row moved to
	quint8 col;//row moved to

	quint8 lastRow;
	quint8 lastCol;

	bool operator ==(const moveData& m1)
	{
		return lastRow == m1.lastRow &&
			   lastCol == m1.lastCol &&
			   row == m1.row &&
			   col == m1.col;
	}
};

class GameThread : public QThread
{
	Q_OBJECT

public:
	GameThread(int argc, char ** argv);

	void run();
	inline void addMoveToHash(moveData toAdd);

	Q_SIGNAL void ioError(QString);
	Q_SIGNAL void gotMove();
	Q_SLOT void aiTurn();
	Q_SLOT void receiveMove(quint8,quint8);
private:
	int m_argc;
	char ** m_argv;
	QFile  * pData;
	QHash<moveData, qint64> * pKnowledge;
	bool m_finished;
	moveData * pLastMove;

	BoardUI * pBoardUI;
};
#endif