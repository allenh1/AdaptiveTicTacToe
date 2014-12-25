#include "boardUI.h"
BoardUI::BoardUI(int argc, char ** argv, QWidget * parent)
    : QWidget(parent),
      m_locked(false),
      m_gameThread(argc, argv)
{
	/** Set up the buttons for the UI **/
	// pButtonArray = new QPushButton[ROWS][COLS];

	// for (quint8 x = 0; x < ROWS; ++x)
	// 	for (quint8 y = 0; y < COLS; ++y)
	// 		pButtonArray[x][y] = new QPushButton();

	pHorizontal = new QHBoxLayout();
	pVertical1 = new QVBoxLayout();
	pVertical2 = new QVBoxLayout();
	pVertical3 = new QVBoxLayout();
	pButtons = new QSignalMapper();

	connect(pButtons, SIGNAL(mapped(int)), this, SLOT(updateUI(int)));
	/**
		this maps the first row to 0-2 (inclusive),
		the second to 3 - 5 (inclusive),
		and the bottom row to 6-8 (inclusive)
	*/
	for (quint8 x = 0; x < ROWS; ++x)
	{
		pButtons->setMapping(&pButtonArray[0][x], x);
		connect(&pButtonArray[0][x], SIGNAL(clicked()), pButtons, SLOT(map()));
		pButtons->setMapping(&pButtonArray[1][x], COLS + x);
		connect(&pButtonArray[1][x], SIGNAL(clicked()), pButtons, SLOT(map()));
		pButtons->setMapping(&pButtonArray[2][x], COLS + COLS + x);
		connect(&pButtonArray[2][x], SIGNAL(clicked()), pButtons, SLOT(map()));

		pVertical1->addWidget(&pButtonArray[x][0]);
		pVertical2->addWidget(&pButtonArray[x][1]);
		pVertical3->addWidget(&pButtonArray[x][2]);
	}

	pHorizontal->addLayout(pVertical1);
	pHorizontal->addLayout(pVertical2);
	pHorizontal->addLayout(pVertical3);

	setLayout(pHorizontal);
	show();

    connect(&m_gameThread, SIGNAL(gotMove()), &m_gameThread, SLOT(aiTurn()));
    connect(this, SIGNAL(madeMove(quint8,quint8)), &m_gameThread, SLOT(receiveMove(quint8,quint8)));
    connect(this, SIGNAL(destroyed()), &m_gameThread, SLOT(closeThread()));
    connect(this, SIGNAL(destroyed()), &m_gameThread, SLOT(terminate()));
    connect(&m_gameThread, SIGNAL(aiHasMoved()), this, SLOT(unlockMoves()));
    connect(this, SIGNAL(aiTurn()), this, SLOT(lockMoves()));
    connect(&m_gameThread, SIGNAL(aiMove(quint8,quint8)), this, SLOT(markUI(quint8,quint8)));
    m_gameThread.start();
	setWindowTitle(tr("Adaptive Tic-Tac-Toe"));
}

BoardUI::~BoardUI()
{
	delete pHorizontal;//this should be all we need to clean?
}

void BoardUI::lockMoves(){ m_locked = true; }
void BoardUI::unlockMoves(){ m_locked = false; }

void BoardUI::updateUI(int clicked)
{
    if (!m_locked)
    {
        quint8 col = clicked % 3;
        quint8 row = clicked / 3;

        pBoard[row][col] = X;

        pButtonArray[row][col].setText(tr("X"));
        Q_EMIT aiTurn();
        Q_EMIT madeMove(row, col);
    }
}

void BoardUI::markUI(quint8 row, quint8 col)
{
    pBoard[row][col] = O;

    pButtonArray[row][col].setText(tr("O"));
}
