#include "boardUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoardUI w;
    w.show();

    return a.exec();
}
