#include "GameThread.h"

QDataStream & operator>>(QDataStream & in, MoveData& m1)
{
    quint8 row, col, lastRow, lastCol;
    quint64 count;
    in >> row; m1.row = row;
    in >> col; m1.col = col;
    in >> lastRow; m1.lastRow = lastRow;
    in >> lastCol; m1.lastCol = lastCol;
    in >> count; m1.count = count;

    return in;
}

QDataStream & operator<<(QDataStream & out, const MoveData& m1)
{
    out << m1.row;
    out << m1.col;
    out << m1.lastRow;
    out << m1.lastCol;
    out << m1.count;

    return out;
}

GameThread::GameThread(int argc, char ** argv) :
	m_argc(argc),
	m_argv(argv),
	m_finished(false)
{
    for (int x = 0; x < ROWS; ++x)
        for (int y = 0; y < COLS; ++y)
            m_board[x][y] = B;

    pLastMove = new MoveData();
    pKnowledge = new QList<MoveData>();
     pData = new QFile("data.ai");
     if (!pData->open(QIODevice::ReadOnly))
        Q_EMIT ioError(QString("Unable to read file!"));
     else
     {
        QDataStream in(pData);
		

        while (!in.atEnd())
        {
            MoveData temp;
            in >> temp;//move the next input into the temp object.
            pKnowledge->push_back(temp);
        }//loop through the file and add it.
     }
}

inline void GameThread::addMoveToList(MoveData toAdd)
{
    if (!pKnowledge->contains(toAdd))
	{
		//there was no copy of the thing.
		//we should add it.
        toAdd.count = 1;
        pKnowledge->push_back(toAdd);
	}
	else
	{
        MoveData temp = pKnowledge->at(pKnowledge->indexOf(toAdd));
        temp.incCount();
        pKnowledge->removeAt(pKnowledge->indexOf(toAdd));
        pKnowledge->push_back(temp);
	}//take it out then put it back.
}

void GameThread::receiveMove(quint8 x, quint8 y)
{
	pLastMove->row = x;
	pLastMove->col = y;

    m_board[x][y] = X;
    addMoveToList(*pLastMove);
	delete pLastMove;
    pLastMove = new MoveData();
	Q_EMIT gotMove();
}

void GameThread::saveData()
{
    pData->remove();
    delete pData;
    pData = new QFile("data.ai");

    if (!pData->open(QIODevice::WriteOnly))
        Q_EMIT ioError(QString("Could not save data file!"));

    QDataStream out(pData);
    for (int x = 0; x < pKnowledge->size(); ++x)
        out << pKnowledge->at(x);
}

void GameThread::aiTurn()
{
    bool done = false;
    for (quint8 x = 0; x < 3; x++) {
        for (quint8 y = 0; y < 3; y++) {
            if (!isOccupied(x, y))
            {
                Q_EMIT(aiMove(x, y));
                Q_EMIT aiHasMoved();
                done = true;
                break;
            }
        }
        if (done)
            break;
    }
}

void GameThread::run()
{
    std::cout<<"Hello from the game thread!"<<std::endl;
    QString gameWinner;
	while (!m_finished)
	{
        if (hasWinner(&gameWinner) && gameWinner != " ")
        {
            std::cout<<"The game was won by "<<gameWinner.toStdString()<<"."<<std::endl;
            saveData();
            m_finished = true;
        }
	}
}

inline bool GameThread::isOccupied(quint8 row, quint8 col)
{
    return m_board[row][col] != B;
}

bool GameThread::hasWinner(Board board[ROWS][COLS], QString *winner)
{
    for (int x = 0; x < ROWS; ++x)
    {
        if (board[x][0] == board[x][1] && board[x][0] == board[x][2])
        { *winner = QString((char) board[x][0]); if (board[x][0] != ' '){return true;} }

        if (board[0][x] == board[1][x] && board[0][x] == board[2][x])
        { *winner = QString((char) board[0][x]); if (board[0][x] != ' '){return true;} }

    }//end for

    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]))
    { *winner = QString((char) board[1][1]); if (board[0][0] != ' '){ return true; } }
    if ((board[2][0] == board[1][1] && board[0][2] == board[2][0]))
    { *winner = QString((char) board[1][1]); if (board[1][1] != ' '){ return true; } }

    return false;
}

bool GameThread::hasWinner(QString *winner)
{
    return hasWinner(m_board, winner);
}

void GameThread::closeThread()
{ m_finished = true; }
