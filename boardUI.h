#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#define ROWS 3
#define COLS 3

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QString>

enum Board { X=88, O=79, B=92 };

class BoardUI : public QWidget
{
	Q_OBJECT

public:
	BoardUI(QWidget * parent = 0);
	~BoardUI();

	Q_SLOT void updateUI();
private:
	Board pBoard[ROWS][COLS];  //true = 'X'; false = 'O';

	QPushButton *pUL;//upper left
	QPushButton *pUM;
	QPushButton *pUR;
	QPushButton *pML;
	QPushButton *pMM;
	QPushButton *pMR;
	QPushButton *pLL;
	QPushButton *pLM;
	QPushButton *pLR;

	QHBoxLayout *pHorizontal;
	QVBoxLayout *pVertical1;
	QVBoxLayout *pVertical2;
	QVBoxLayout *pVertical3;
};
#endif