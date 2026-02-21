#include <QApplication>

#include "mainwindow.h"
#include "start.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    start s;
    MainWindow w;
    QObject::connect(&s, &start::startGame, &w, &MainWindow::getStartGame);
    QObject::connect(&w, &MainWindow::back, &s, &start::getBack);
    s.show();
    w.hide();
    return a.exec();
}
