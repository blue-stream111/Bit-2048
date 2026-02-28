#include <QApplication>

#include "mainwindow.h"
#include "saveform.h"
#include "start.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    start s;
    s.setWindowTitle("Bit 2048");
    s.setFixedSize(794, 639);
    MainWindow w;
    w.setWindowTitle("Bit 2048");
    saveForm savings;
    QObject::connect(&s, &start::getSavings, &savings, &saveForm::start);
    QObject::connect(&savings, &saveForm::back, &s, &start::getBack);
    QObject::connect(&s, &start::startGame, &w, &MainWindow::getStartGame);
    QObject::connect(&w, &MainWindow::back, &s, &start::getBack);
    QObject::connect(&savings, &saveForm::startGame, &w,
                     &MainWindow::getStartGame);
    QObject::connect(&w, &MainWindow::recordSaving, &savings,
                     &saveForm::record);
    s.show();
    w.hide();
    return a.exec();
}
