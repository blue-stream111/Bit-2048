#include "mainwindow.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QPainter>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // game = new Game();
    bg = QPixmap(":/startBackground.jpg")
             .scaled(this->size(), Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);
    setFixedSize(1002, 598);
    infoTimer = new QTimer(this);
    // infoTimer->start(100);
    connect(infoTimer, &QTimer::timeout, this, &MainWindow::showInfo);
    gameIsOn = 0;
    tail = -1;
    for (int i = 0; i < 7; i++) scores[i].score = 0, scores[i].time = 0;
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_LENGTH; j++) {
            MyLabel* label = qobject_cast<MyLabel*>(
                ui->gridLayout->itemAtPosition(i, j)->widget());
            if (label == nullptr)
                qDebug() << "Error in visiting a nullptr!\n";
            else
                connect(label, &MyLabel::bomb, this, &MainWindow::handleBomb);
        }

    updateRank(1);
    // qDebug() << "game is on? " << gameIsOn;
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::paintEvent(QPaintEvent*) {
    // qDebug() << "Trigerring paintEvent!";
    QPainter painter(this);
    painter.drawPixmap(rect(), bg, QRect());
}
void MainWindow::updateRank(bool first) {
    loadRank();
    if (!first) {
        if (tail < 6) tail++;
        if (tail > 6) {
            qDebug() << "Out of bound.";
            return;
        }
        scores[tail].time = game->getTime();
        scores[tail].name = game->getName();
        scores[tail].score = game->getScore();
        std::sort(scores, scores + tail + 1);
    }
    for (int i = 0; i < qMin(6, tail + 1); i++) {
        QLabel* label_rk = qobject_cast<QLabel*>(
            ui->formLayout->itemAt(i, QFormLayout::LabelRole)->widget());
        QLabel* label_score = qobject_cast<QLabel*>(
            ui->formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        QString s_rk = "第" + QString::number(i + 1) + "名";
        label_rk->setText(s_rk);
        QString s_score = scores[i].name + "总计" +
                          QString::number(scores[i].score) + "分，耗时" +
                          handleTime(scores[i].time);
        label_score->setText(s_score);
    }
    if (!first) saveRank();
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
void MainWindow::openNewGame(QString name, QString filePath) {
    if (gameIsOn) return;
    gameIsOn = 1;
    if (filePath == "") {
        game = new Game();
        game->setName(name);
    } else
        game = new Game(filePath);
    connect(game, &Game::lose, this, &MainWindow::handleLose);
    connect(game, &Game::win, this, &MainWindow::handleWin);

    game->start();
    drawBoard();
    updateRank(1);
    infoTimer->start(100);
}
void MainWindow::loadRank() {
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/rank.json");
    QString dataDir = QDir(exeDir).filePath("data");
    QDir().mkpath(dataDir);
    QFile file(filePath);
    if (!file.exists()) {                                   // 检查文件是否存在
        file.open(QIODevice::WriteOnly | QIODevice::Text);  // 不存在则创建
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in reading the file.";
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray allItems = doc.array();
    int tot = allItems.size();
    if (allItems.size() > 6) tot = 6;
    for (int i = 0; i < tot; i++) {
        scores[i].name = allItems[i].toObject()["name"].toString();
        scores[i].score = allItems[i].toObject()["score"].toInt();
        scores[i].time = allItems[i].toObject()["time"].toInt();
    }
    tail = tot - 1;
}
void MainWindow::saveRank() {
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/rank.json");
    QString dataDir = QDir(exeDir).filePath("data");
    QDir().mkpath(dataDir);
    QFile file(filePath);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in writing the file.";
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray allItems = doc.array();
    QList<QJsonObject> newScores;
    for (int i = 0; i <= tail; i++) {
        QJsonObject obj;
        obj["name"] = scores[i].name;
        obj["score"] = scores[i].score;
        obj["time"] = scores[i].time;
        newScores << obj;
    }
    int tot = allItems.size();
    for (int i = std::min(5, tot - 1); i >= 0; i--) {
        allItems.removeAt(0);
    }
    for (int i = 0; i < newScores.size(); i++) allItems.insert(i, newScores[i]);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in writing back.";
        return;
    }
    QJsonDocument doc2(allItems);
    file.write(doc2.toJson());
    file.close();
}
void MainWindow::on_pushStart_clicked() {
    // qDebug() << "game is on?" << gameIsOn;
    if (!gameIsOn) {
        bool ok;
        QString name = QInputDialog::getText(
            this, "Bit 2048", "欢迎来到Bit2048！请告诉我们你的名字吧！",
            QLineEdit::Normal, "", &ok);
        if (!ok) return;
        openNewGame(name);
        qDebug() << "Now draw the board.";
        drawBoard();
        showInfo();
        ui->pushStart->setText(QString("重新开始（R）"));
        ui->pushBack->setText(QString("退出游戏（Q）"));
    } else {
        QMessageBox::StandardButton res = QMessageBox::question(
            this, "Bit2048", "你确定要重新开始吗？这一局的分数也将会被记录。",
            QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes) {
            QString name = game->getName();
            gameOver();
            openNewGame(name);
        }
    }
}

void MainWindow::on_pushSuspend_clicked() {
    if (gameIsOn == 0) {
        QMessageBox::information(this, "Bit2048",
                                 "你只有在游戏中才能暂停哟(｡･ω･｡)");
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

void MainWindow::getStartGame(QString fileName) {
    if (fileName != "") {
        openNewGame("", fileName);
        on_pushSuspend_clicked();
        drawBoard();
        showInfo();
        ui->pushStart->setText(QString("重新开始（R）"));
        ui->pushBack->setText(QString("退出游戏（Q）"));
    }

    this->show();
}
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
            Num* num = game->read(i, j);
            MyLabel* label = qobject_cast<MyLabel*>(
                ui->gridLayout->itemAtPosition(i, j)->widget());

            // qDebug() << ui->gridLayout->itemAtPosition(i, j)->widget() <<
            // "在第" << i + 1 << "行第" << j + 1 << "列";
            label->match(num, i, j);
        }
        // qDebug() << "\n";
    }

    ui->labelScore->setText(QString::number(game->getScore()));
    ui->labelStep->setText(QString::number(game->getStep()));
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (gameIsOn == 0 || game->isActive() == 0) return;
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
    // qDebug() << "After generating: ";
    // game->debData();
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
void MainWindow::handleBomb(int x, int y) {
    if (gameIsOn == 0) {
        qDebug() << "error! game is over already.";
        return;
    }
    game->Bomb(x, y);
    drawBoard();
}

void MainWindow::on_pushLast_clicked() {
    if (gameIsOn == 0) {
        QMessageBox::information(this, "Bit2048",
                                 "你只有在游戏中才能查看上一步哟(｡･ω･｡)");
        return;
    }
    if (game->getStep() == 0) {
        QMessageBox::information(
            this, "Bit2048",
            "你只有在游戏中进行了至少一步才能查看上一步哟(｡･ω･｡)");
        return;
    }
    game->recoverLastStep();
    drawBoard();
}

void MainWindow::on_pushSave_clicked() {
    if (!gameIsOn) {
        QMessageBox::information(this, "Bit 2048",
                                 "游戏尚未开始或已经结束，无法进行存档。");
        return;
    }
    emit recordSaving(game->getTime(), game->getStep(), game->getName());
}
