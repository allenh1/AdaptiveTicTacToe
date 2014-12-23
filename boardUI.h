#ifndef BOARDUI_H
#define BOARDUI_H
#define ROWS 3
#define COLS 3

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <iostream>

enum Board { X=88, O=79, B=92 };

class BoardUI : public QWidget
{
	Q_OBJECT

public:
	BoardUI(QWidget * parent = 0);
	~BoardUI();

	Q_SLOT void updateUI(int clicked);
	Q_SLOT void madeMove(quint8,quint8);
private:
	Board pBoard[ROWS][COLS];  //true = 'X'; false = 'O';

	QPushButton pButtonArray[ROWS][COLS];

	QSignalMapper * pButtons;

	QHBoxLayout *pHorizontal;
	QVBoxLayout *pVertical1;
	QVBoxLayout *pVertical2;
	QVBoxLayout *pVertical3;
};
#endif