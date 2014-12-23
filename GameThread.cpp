#include "GameThread.h"

GameThread::GameThread(int argc, char ** argv) :
	m_argc(argc),
	m_argv(argv),
	m_finished(false)
{
	pData = new QFile("data.ai");
	if (!pData.open(QIODevice::ReadOnly)
		Q_EMIT ioError(QString("Unable to read file!"));
	else
	{
		QDataStream in(pData);
		pKnowledge = new QHash();

		while (!in.atEnd())
		{
			/** This is where we read the file.
			 * If it does exist within the text, we increment.
			 * This is useful for probability calculations.
			 * The file is of type binary with the moveData
			 * datatype.
			 */

			moveData temp;
			in >> temp;//move the next input into the temp object.
			addMoveToHash(toAdd);
		}//loop through the file and add it.
	}
}

inline void GameThread::addMoveToHash(moveData toAdd)
{
	if (pKnowledge->value(toAdd) == NULL)
	{
		//there was no copy of the thing.
		//we should add it.
		pKnowledge->insert(toAdd, 1);
	}
	else
	{
		qint64 count = pKnowledge->take(toAdd);
		count++;
		pKnowledge->insert(toAdd, count);
	}//take it out then put it back.
}

void receiveMove(quint8 x, quint8 y)
{
	pLastMove->row = x;
	pLastMove->col = y;

	addMoveToHash(*pLastMove);
	delete pLastMove;
	pLastMove = new moveData();
	Q_EMIT gotMove();
}

void GameThread::aiTurn()
{
	//TODO: here the ai decides the best move.
	//      this is the heart of the algorithm.
	//		after a move is decided, the game stores
	//		the next move as pLastMove with what we did.
	//		After the player moves, it is updated and
	//		the result is added to the hash.
}

void GameThread::run()
{
	std::cout<<"Hello from the game thread!"<<std::endl;
	pBoardUI = new BoardUI();
	pBoardUI->show();
	pLastMove = new moveData();

	connect(this, SIGNAL(gotMove()), this, SLOT(aiTurn()));
	connect(pBoardUI, SIGNAL(madeMove(quint8,quint8)), this, SLOT(receiveMove(quint8,quint8)));

	while (!m_finished)
	{

	}

	delete pBoardUI;
}
