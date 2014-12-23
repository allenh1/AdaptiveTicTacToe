#include "GameThread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameThread w(argc, argv);
    w.run();

    return a.exec();
}
