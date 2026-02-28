#include "start.h"

#include <QMessageBox>

#include "ui_start.h"
start::start(QWidget* parent) : QWidget(parent), ui(new Ui::start) {
    ui->setupUi(this);
    scaledBg = QPixmap(":/startBackground.jpg")
                   .scaled(this->size(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
}

start::~start() { delete ui; }

void start::on_pushStart_clicked() {
    this->hide();
    emit startGame();
}

void start::on_pushHelp_clicked() {
    QMessageBox::information(
        this, "Bit2048",
        "《Bit2048》是一款基于经典 2048 改编的益智类程序设计游戏：棋盘大小为"
        "4 × 4，所有方块数值以二进制形式显示，游戏规则、合并逻辑、计分方式 "
        "与原版 2048 完全一致。你可以使用W, S, A, D对游戏进行控制。");
}

void start::on_pushLeave_clicked() { QApplication::quit(); }

void start::getBack() {
    ui->pushStart->setText(QString("继续游戏"));
    this->show();
}
void start::paintEvent(QPaintEvent*) {
    // qDebug() << "Trigerring paintEvent!";
    QPainter painter(this);
    painter.drawPixmap(rect(), scaledBg, QRect());
}

void start::on_pushSave_clicked() {
    this->hide();
    emit getSavings();
}
