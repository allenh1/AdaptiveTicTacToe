#ifndef BOARDUI_H
#define BOARDUI_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include "GameThread.h"
#include <iostream>

class BoardUI : public QWidget
{
	Q_OBJECT

public:
    BoardUI(int argc, char **argv, QWidget * parent = 0);
	~BoardUI();

	Q_SLOT void updateUI(int clicked);
    Q_SIGNAL void madeMove(quint8,quint8);
    Q_SLOT void markUI(quint8,quint8);
    Q_SIGNAL void aiHasMoved();
    Q_SIGNAL void aiTurn();
    Q_SLOT void unlockMoves();
    Q_SLOT void lockMoves();
private:
	Board pBoard[ROWS][COLS];  //true = 'X'; false = 'O';

	QPushButton pButtonArray[ROWS][COLS];
    bool m_locked;
	QSignalMapper * pButtons;

	QHBoxLayout *pHorizontal;
	QVBoxLayout *pVertical1;
	QVBoxLayout *pVertical2;
	QVBoxLayout *pVertical3;

    GameThread m_gameThread;
};
#endif
