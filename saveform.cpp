#include "saveform.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QPainter>
#include <qDebug>

#include "ui_saveform.h"
#define USER_ROLE 1

saveForm::saveForm(QWidget* parent) : QWidget(parent), ui(new Ui::saveForm) {
    ui->setupUi(this);
    scaledbg = QPixmap(":/startBackground.jpg")
                   .scaled(this->size(), Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    init();
    connect(ui->listSavings, &QListWidget::itemClicked, this,
            &saveForm::onSaveItemClicked);
    setFixedSize(722, 563);
}

saveForm::~saveForm() { delete ui; }

void saveForm::init() {
    ui->listSavings->clear();
    tot = 0;
    bool flag = 1;
    do {
        QString exeDir = QCoreApplication::applicationDirPath();
        QString fileName =
            QDir(exeDir).filePath("data/save/historySavings/HistoryFile");
        fileName += QString::number(tot + 1) + ".json";
        QString dataDir = QDir(exeDir).filePath("data/save/historySavings");
        QDir().mkpath(dataDir);
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "number of savings: " << tot;
            flag = 0;
            continue;
        }
        tot++;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        QJsonArray allItems = doc.array();
        QJsonObject obj = allItems[0].toObject();
        int time = obj["time"].toInt();
        int score = obj["score"].toInt();
        int steps = obj["step"].toInt();
        QString name = obj["name"].toString();
        QString s = "存档" + QString::number(tot) + ": " + name + "耗时" +
                    QString::number(time) + "秒，得分" +
                    QString::number(score) + "，走了" + QString::number(steps) +
                    "步。";
        QListWidgetItem* item = new QListWidgetItem(s);
        item->setData(USER_ROLE, fileName);
        ui->listSavings->addItem(item);
    } while (flag);
    if (!tot) {
        QListWidgetItem* item = new QListWidgetItem("存档1: 暂无存档");
        item->setData(USER_ROLE, "");
        ui->listSavings->addItem(item);
    }
}
void saveForm::start() {
    init();
    this->show();
}
void saveForm::paintEvent(QPaintEvent*) {
    // qDebug() << "Trigerring paintEvent!";
    QPainter painter(this);
    painter.drawPixmap(rect(), scaledbg, QRect());
}
void saveForm::record(int time, int step, QString name) {
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/save/file.json");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in reading the file.json.";
        return;
    }
    QByteArray d = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(d);
    QJsonArray allSteps = doc.array();
    QJsonArray arr = allSteps.last().toArray();
    QJsonObject obj;
    obj["time"] = time;
    obj["step"] = step;
    obj["name"] = name;
    obj["score"] = arr[0].toObject()["score"];
    allSteps.insert(0, obj);
    QString fileName =
        QDir(exeDir).filePath("data/save/historySavings/HistoryFile") +
        QString::number(tot + 1) + ".json";
    tot++;
    QFile newFile(fileName);
    if (!newFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in recording.";
        return;
    }
    QJsonDocument doc2(allSteps);
    newFile.write(doc2.toJson());
    newFile.close();
}

void saveForm::on_pushBack_clicked() {
    this->hide();
    emit back();
}

void saveForm::onSaveItemClicked(QListWidgetItem* item) {
    if (!tot) {
        QMessageBox::information(this, "Bit2048", "暂无存档(｡･ω･｡)！！");
        return;
    }
    QString filePath = item->data(USER_ROLE).toString();
    this->hide();
    emit startGame(filePath);
}
void saveForm::contextMenuEvent(QContextMenuEvent* event) {
    QListWidgetItem* item =
        ui->listSavings->itemAt(ui->listSavings->mapFromGlobal(QCursor::pos()));
    if (!item) return;
    if (item->data(USER_ROLE).toString() == "") return;
    QMenu menu(this);
    QAction* action = menu.addAction("删除这个存档");
    connect(action, &QAction::triggered, this, [=]() {
        bool deleteOk = deleteSave(item);
        if (deleteOk) {
            QMessageBox::information(this, "成功", "存档删除成功！");
            init();
        } else {
            QMessageBox::warning(this, "失败", "存档删除失败！");
        }
    });

    // 显示菜单（在鼠标右键位置）
    menu.exec(QCursor::pos());
}

void saveForm::on_pushClear_clicked() {
    bool ok;
    QMessageBox::StandardButton res =
        QMessageBox::question(this, "Bit2048", "你确定要清空所有存档吗？",
                              QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes) {
        QList<QListWidgetItem*> allItems =
            ui->listSavings->findItems("*", Qt::MatchWildcard);

        for (const auto& item : allItems) {
            if (!item) continue;
            QString filePath = item->data(USER_ROLE).toString();
            if (filePath == "") continue;
            QFile file(filePath);
            if ((!file.exists()) || (!file.remove())) {
                qDebug() << "Wrong file path when clearing.";
                continue;
            }
        }
        ui->listSavings->clear();
        init();
    }
}

bool saveForm::deleteSave(QListWidgetItem* item) {
    QString filePath = item->data(USER_ROLE).toString();
    if (filePath == "") return 0;
    int idx = getIdx(filePath);
    QFile file(filePath);
    if ((!file.exists()) || (!file.remove())) {
        qDebug() << "Wrong file path when deleting.";
        return 0;
    }
    ui->listSavings->removeItemWidget(item);
    delete item;
    QString exeDir = QCoreApplication::applicationDirPath();
    do {
        QString fileName =
            QDir(exeDir).filePath("data/save/historySavings/HistoryFile") +
            QString::number(idx + 1) + ".json";

        QFile tFile(fileName);
        if (!tFile.exists()) {
            break;
        }
        QString newName =
            QDir(exeDir).filePath("data/save/historySavings/HistoryFile") +
            QString::number(idx) + ".json";
        tFile.rename(newName);
        idx++;
    } while (1);
    return 1;
}
int saveForm::getIdx(QString filePath) {
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString nameWithoutExt = fileName.left(fileName.lastIndexOf("."));
    QString numStr = nameWithoutExt.remove("HistoryFile");

    bool ok;
    int num = numStr.toInt(&ok);
    if (ok) {
        return num;
    } else {
        qDebug() << "Error in analysing the idx";
        return -1;
    }
}
