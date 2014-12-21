#include "boardUI.h"
BoardUI::BoardUI(QWidget * parent)
	: QWidget(parent)
{
	/** Set up the buttons for the UI **/
	pUL = new QPushButton(); pUM = new QPushButton(); pUR = new QPushButton();
	pML = new QPushButton(); pMM = new QPushButton(); pMR = new QPushButton();
	pLL = new QPushButton(); pLM = new QPushButton(); pLR = new QPushButton();


	pHorizontal = new QHBoxLayout();
	pVertical1 = new QVBoxLayout();
	pVertical2 = new QVBoxLayout();
	pVertical3 = new QVBoxLayout();

	pVertical1->addWidget(pUL);
	pVertical1->addWidget(pML);
	pVertical1->addWidget(pLL);

	pVertical2->addWidget(pUM);
	pVertical2->addWidget(pMM);
	pVertical2->addWidget(pLM);

	pVertical3->addWidget(pUR);
	pVertical3->addWidget(pMR);
	pVertical3->addWidget(pLR);

	pHorizontal->addLayout(pVertical1);
	pHorizontal->addLayout(pVertical2);
	pHorizontal->addLayout(pVertical3);

	setLayout(pHorizontal);
	show();

	setWindowTitle(tr("Adaptive Tic-Tac-Toe"));
}

BoardUI::~BoardUI()
{
	delete pHorizontal;//this should be all we need to clean?
}

void BoardUI::updateUI()
{

}