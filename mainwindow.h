#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>
#include <algorithm>

#include "game.h"
#include "mylabel.h"
#define BOARD_LENGTH 4
#define BOARD_WIDTH 4

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct SCORE {
    QString name;
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
    void paintEvent(QPaintEvent*) override;
    ~MainWindow();

protected:
public slots:
    void on_pushStart_clicked();

    void on_pushSuspend_clicked();

    void on_pushBack_clicked();

    void getStartGame(QString fileName = "");

    void showInfo();

    void drawBoard();

    void handleWin();

    void handleLose();

    void handleBomb(int x, int y);

signals:
    void back();
    void recordSaving(int time, int steps, QString name);

private:
    Ui::MainWindow* ui;
    Game* game;
    QTimer* infoTimer;
    bool gameIsOn;
    QString toBinary(int val);
    // void setColor(int x, int y, int val);
    void gameOver();
    void openNewGame(QString name, QString filePath = "");
    void updateRank(bool first = 0);
    QString handleTime(int sec);
    void loadRank();
    void saveRank();
    SCORE scores[7];
    int tail;
    QPixmap bg;

protected:
    void keyPressEvent(QKeyEvent* event) override;
private slots:
    void on_pushLast_clicked();
    void on_pushSave_clicked();
};
#endif  // MAINWINDOW_H
