#include "mainwindow.h"

#include <QDebug>
#include <QMessageBox>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // game = new Game();
    infoTimer = new QTimer(this);
    // infoTimer->start(100);
    connect(infoTimer, &QTimer::timeout, this, &MainWindow::showInfo);
    gameIsOn = 0;
    tail = -1;
    for (int i = 0; i < 7; i++) scores[i].score = 0, scores[i].time = 0;
    // qDebug() << "game is on? " << gameIsOn;
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::updateRank() {
    if (tail < 6) tail++;
    scores[tail].time = game->getTime(), scores[tail].score = game->getScore();
    std::sort(scores, scores + tail + 1);
    for (int i = 0; i < qMin(6, tail + 1); i++) {
        QLabel* label_rk = qobject_cast<QLabel*>(
            ui->formLayout->itemAt(i, QFormLayout::LabelRole)->widget());
        QLabel* label_score = qobject_cast<QLabel*>(
            ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        QString s_rk = "第" + QString::number(i + 1) + "名";
        label_rk->setText(s_rk);
        QString s_score = "总计" + QString::number(scores[i].score) +
                          "分，耗时" + handleTime(scores[i].time);
        label_score->setText(s_score);
    }
}
void MainWindow::gameOver() {
    if (gameIsOn == 0) return;
    updateRank();
    gameIsOn = 0;
    infoTimer->stop();
    disconnect(game, &Game::lose, this, &MainWindow::handleLose);
    disconnect(game, &Game::win, this, &MainWindow::handleWin);
    delete game;
    game = nullptr;
}
void MainWindow::openNewGame() {
    if (gameIsOn) return;
    gameIsOn = 1;
    game = new Game();
    connect(game, &Game::lose, this, &MainWindow::handleLose);
    connect(game, &Game::win, this, &MainWindow::handleWin);
    game->start();
    infoTimer->start(100);
}
void MainWindow::on_pushStart_clicked() {
    // qDebug() << "game is on?" << gameIsOn;
    if (!gameIsOn) {
        openNewGame();
        drawBoard();
        showInfo();
        ui->pushStart->setText(QString("重新开始（R）"));
        ui->pushBack->setText(QString("退出游戏（Q）"));
    } else {
        QMessageBox::StandardButton res = QMessageBox::question(
            this, "Bit2048", "你确定要重新开始吗？这一局的分数也将会被记录。",
            QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes) {
            gameOver();
            openNewGame();
        }
    }
}

void MainWindow::on_pushSuspend_clicked() {
    if (gameIsOn == 0) {
        QMessageBox::information(this, "Bit2048", "你尚未开始游戏！");
        return;
    }
    if (game->isActive()) {
        game->suspend();
        ui->pushSuspend->setText(QString("继续"));
    } else {
        game->goOn();
        ui->pushSuspend->setText(QString("暂停"));
    }
}

void MainWindow::on_pushBack_clicked() {
    if (gameIsOn) {
        QMessageBox::StandardButton res =
            QMessageBox::question(this, "Bit2048", "你想要现在结束这局游戏吗？",
                                  QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes) {
            gameOver();
            ui->pushBack->setText(QString("返回"));
            ui->pushStart->setText(QString("开始游戏"));
        }
    } else {
        this->hide();
        emit back();
    }
}

void MainWindow::getStartGame() { this->show(); }
QString MainWindow::handleTime(int sec) {
    int min = sec / 60;
    QString s;
    if (min) s = QString::number(min) + "分钟";
    sec %= 60;
    s += QString::number(sec) + "秒";
    return s;
}
void MainWindow::showInfo() {
    if (gameIsOn == 0) return;
    // drawBoard();
    int sec = game->getTime();
    QString s = handleTime(sec);
    ui->labelTimer->setText(s);
}

void MainWindow::drawBoard() {
    if (gameIsOn == 0) return;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            int val = game->read(i, j);
            // qDebug() << val << ' ';
            QLabel* label = qobject_cast<QLabel*>(
                ui->gridLayout->itemAtPosition(i, j)->widget());
            label->setText(toBinary(val));
            setColor(i, j, val);
        }
        // qDebug() << "\n";
    }

    ui->labelScore->setText(QString::number(game->getScore()));
}

QString MainWindow::toBinary(int val) {
    if (val == 0) return "";
    QString s = QString::number(1);
    while (val > 1) {
        s = s + QString::number(0);
        val /= 2;
    }
    while (s.length() < 4) s = QString::number(0) + s;
    return s;
}

void MainWindow::setColor(int x, int y, int val) {
    QString rgb;
    switch (val) {
        case 0:
            rgb = "rgb(255, 170, 127);";
            break;
        case 1:
            rgb = "rgb(238, 228, 218);";
            break;
        case 2:
            rgb = "rgb(237, 224, 200);";
            break;
        case 4:
            rgb = "rgb(242, 177, 121);";
            break;
        case 8:
            rgb = "rgb(245, 150, 100);";
            break;
        case 16:
            rgb = "rgb(245, 125, 95);";
            break;
        case 32:
            rgb = "rgb(245, 95, 60);";
            break;
        case 64:
            rgb = "rgb(237, 207, 114);";
            break;
        case 128:
            rgb = "rgb(237, 204, 97);";
            break;
        case 256:
            rgb = "rgb(237, 204, 97);";
            break;
        case 512:
            rgb = "rgb(237, 204, 97);";
            break;
        case 1024:
            rgb = "rgb(237, 204, 97);";
            break;
        case 2048:
            rgb = "rgb(106, 0, 95);";
            break;
        defalt:
            break;
    }
    QString setting = "background-color: " + rgb;
    QLabel* label =
        qobject_cast<QLabel*>(ui->gridLayout->itemAtPosition(x, y)->widget());
    label->setStyleSheet(setting);
    return;
}
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!gameIsOn) return;
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            game->moveUp();
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            game->moveDown();
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            game->moveLeft();
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            game->moveRight();
            break;
        case Qt::Key_R:
            on_pushStart_clicked();
            break;
        case Qt::Key_Q:
            on_pushBack_clicked();
            break;
        default:
            break;
    }
    drawBoard();
}
void MainWindow::handleLose() {
    if (gameIsOn == 0) return;
    int sec = game->getTime();
    int min = sec / 60;
    QString time;
    if (min) time = QString::number(min) + "分钟";
    sec %= 60;
    time += QString::number(sec) + "秒";
    QString message = "游戏结束，本局共计得分" +
                      QString::number(game->getScore()) + "，用时" + time +
                      "，本局最大方块为" + QString::number(game->getMaxTile()) +
                      "。";
    qDebug() << game;
    gameOver();
    qDebug() << game;
    QMessageBox::information(this, "Bit2048", message);
    ui->pushBack->setText(QString("返回"));
    ui->pushStart->setText(QString("开始游戏"));
}
void MainWindow::handleWin() {
    if (gameIsOn == 0) return;
    int sec = game->getTime();
    int min = sec / 60;
    QString time;
    if (min) time = QString::number(min) + "分钟";
    sec %= 60;
    time += QString::number(sec) + "秒。";
    QString message = "恭喜你成功合成2048！本局共计得分" +
                      QString::number(game->getScore()) + "，用时" + time;
    gameOver();
    QMessageBox::information(this, "Bit2048", message);
    ui->pushBack->setText(QString("返回"));
    ui->pushStart->setText(QString("开始游戏"));
}
