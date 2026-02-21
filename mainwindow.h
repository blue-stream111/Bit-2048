#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>
#include <algorithm>

#include "game.h"
#define BOARD_LENGTH 4
#define BOARD_WIDTH 4

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct SCORE {
    int score;
    int time;
    bool operator<(const SCORE& s) const {
        if (score == s.score) return time < s.time;
        return score > s.score;
    }
};
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushStart_clicked();

    void on_pushSuspend_clicked();

    void on_pushBack_clicked();

    void getStartGame();

    void showInfo();

    void drawBoard();

    void handleWin();

    void handleLose();

signals:
    void back();

private:
    Ui::MainWindow* ui;
    Game* game;
    QTimer* infoTimer;
    bool gameIsOn;
    QString toBinary(int val);
    void setColor(int x, int y, int val);
    void gameOver();
    void openNewGame();
    void updateRank();
    QString handleTime(int sec);
    SCORE scores[7];
    int tail;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif  // MAINWINDOW_H
