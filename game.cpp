#include "game.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <qDebug>
Game::Game() {
    qDebug() << "Now initial game.";
    clearFile();
    timer = new QTimer(this);
    score = 0;
    full = 0;
    time = 0;
    maxVal = 1;
    steps = 0;
    // maxTimes = 1;
    QObject::connect(timer, &QTimer::timeout, this, &Game::addTime);
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_LENGTH; j++) {
            set(data[i][j], 0);
            name = "";
        }
    generate();
    generate();
    saveFile();
}
Game::Game(QString filePath) {
    qDebug() << "Now initial game at " << filePath;
    timer = new QTimer(this);
    full = 0;
    maxVal = 1;
    QObject::connect(timer, &QTimer::timeout, this, &Game::addTime);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in finding file in " << filePath;
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonArray allItems = doc.array();
    QJsonArray arr = allItems.last().toArray();
    QJsonObject obj = allItems[0].toObject();
    time = obj["time"].toInt();
    score = obj["score"].toInt();
    steps = obj["step"].toInt();
    name = obj["name"].toString();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            int idx = i * BOARD_WIDTH + j + 1;
            data[i][j].isLocked = arr[idx].toObject()["isLocked"].toBool();
            data[i][j].val = arr[idx].toObject()["val"].toInt();
            QString s = arr[idx].toObject()["type"].toString();
            if (s == "NUMBER") {
                data[i][j].type = NUMBER;
                maxVal = qMax(maxVal, data[i][j].val);
            } else if (s == "LG2")
                data[i][j].type = LG2;
            else if (s == "BOMB")
                data[i][j].type = BOMB;
            else if (s == "AND")
                data[i][j].type = AND;
            else if (s == "OR")
                data[i][j].type = OR;
            else if (s == "BLACKHOLE")
                data[i][j].type = BLACKHOLE;
            else if (s == "XOR")
                data[i][j].type = XOR;
            else if (s == "BARRIER")
                data[i][j].type = BARRIER;
            else {
                qDebug() << "Error in type reading!";
                return;
            }
        }
    }
    allItems.removeFirst();
    QFile newFile("../../file.json");
    if (!newFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in transferring to file.json.";
        return;
    }
    QJsonDocument doc2(allItems);
    newFile.write(doc2.toJson());
    newFile.close();
}
Game::~Game() {}
void Game::clearFile() {
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/save/file.json");
    QString dataDir = QDir(exeDir).filePath("data/save");
    QDir().mkpath(dataDir);
    QFile file(filePath);
    if (!file.exists()) {                                   // 检查文件是否存在
        file.open(QIODevice::WriteOnly | QIODevice::Text);  // 不存在则创建
        file.close();
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in clearing file.json";
        return;
    }
    file.close();
}
void Game::start() { timer->start(1000); }
void Game::goOn() { timer->start(); }
void Game::suspend() { timer->stop(); }
Num* Game::read(int x, int y) { return &data[x][y]; }
bool Game::isActive() { return timer->isActive(); }
int Game::getScore() const { return score; }
int Game::getTime() const { return time; }
void Game::addTime() {
    time++;
    timer->start(1000);
}
void Game::set(Num& num, int n) {
    if (!is2Times(n)) {
        num.type = BARRIER;
        num.isLocked = 1;
    } else {
        num.isLocked = 0;
        num.type = NUMBER;
    }
    num.val = n;
}
void Game::handleMove(Num& fst, Num& snd) {
    bool suc = 0;
    if (fst.type == NUMBER && snd.type == NUMBER) {
        // suc = 1;
        if (fst.val == snd.val) {
            fst.val *= 2;
            score += fst.val;
            snd.val = 0;
        }
    } else if (fst.type == BLACKHOLE || snd.type == BLACKHOLE) {
        // suc = 1;
        set(fst, 0);
        set(snd, 0);
    } else if (fst.type == NUMBER || snd.type == NUMBER) {
        if (fst.type == LG2) {
            suc = 1;
            if (is2Times(snd.val)) {
                set(fst, lg2(snd.val));
                set(snd, 0);
            }
        } else if (snd.type == LG2) {
            suc = 1;
            if (is2Times(fst.val)) {
                set(fst, lg2(fst.val));
                set(snd, 0);
            }
        } else if (fst.type == AND || snd.type == AND) {
            suc = 1;
            set(fst, fst.val & snd.val);
            set(snd, 0);
        } else if (fst.type == OR || snd.type == OR) {
            suc = 1;
            set(fst, fst.val | snd.val);
            set(snd, 0);
        } else if (fst.type == XOR || snd.type == XOR) {
            suc = 1;
            set(fst, fst.val ^ snd.val);
            set(snd, 0);
        }
        if (!suc) qDebug() << "You fail to consider some situation...";
    }
    if (fst.val > maxVal) maxVal = fst.val;
}
void Game::moveLeft() {
    // 碰撞逻辑：只有fst和snd都没有被锁定或者snd是没锁定的黑洞才会发生效果
    steps++;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = 0;
        while (fst < BOARD_LENGTH) {
            while (fst < BOARD_LENGTH && (data[i][fst].val == 0)) fst++;
            if (fst >= BOARD_LENGTH) break;
            int snd = fst + 1;
            while (snd < BOARD_LENGTH && data[i][snd].val == 0) snd++;
            if (snd >= BOARD_LENGTH) break;
            if ((data[i][snd].isLocked == 0 && data[i][fst].isLocked == 0) ||
                (data[i][snd].type == BLACKHOLE &&
                 data[i][snd].isLocked == 0)) {
                handleMove(data[i][fst], data[i][snd]);
            }
            fst = snd;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = 0;
        while (fst < BOARD_LENGTH) {
            while (fst < BOARD_LENGTH && (data[i][fst].val != 0)) fst++;
            if (fst >= BOARD_LENGTH) break;
            int snd = fst + 1;
            while (snd < BOARD_LENGTH && data[i][snd].val == 0) snd++;
            if (snd >= BOARD_LENGTH) break;
            if (!data[i][snd].isLocked) {
                data[i][fst] = data[i][snd];
                set(data[i][snd], 0);
                fst++;
            } else {
                fst = snd + 1;
            }
        }
    }
    emitSignal();
    gen();
}
void Game::moveRight() {
    steps++;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = BOARD_LENGTH - 1, snd = BOARD_LENGTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && (data[i][fst].val == 0)) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[i][snd].val == 0) snd--;
            if (snd < 0) break;
            if ((data[i][snd].isLocked == 0 && data[i][fst].isLocked == 0) ||
                (data[i][snd].type == BLACKHOLE &&
                 data[i][snd].isLocked == 0)) {
                handleMove(data[i][fst], data[i][snd]);
            }
            fst = snd;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = BOARD_LENGTH - 1;
        while (fst >= 0) {
            while (fst >= 0 && data[i][fst].val != 0) fst--;
            if (fst < 0) break;
            int snd = fst - 1;
            while (snd >= 0 && data[i][snd].val == 0) snd--;
            if (snd < 0) break;
            if (data[i][snd].isLocked == 0) {
                data[i][fst] = data[i][snd];
                set(data[i][snd], 0);
                fst--;
            } else {
                fst = snd - 1;
            }
        }
    }
    emitSignal();
    gen();
}
void Game::moveUp() {
    steps++;
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = 0, snd = 0;
        while (fst < BOARD_WIDTH && snd < BOARD_WIDTH) {
            while (fst < BOARD_WIDTH && data[fst][j].val == 0) fst++;
            if (fst >= BOARD_WIDTH) break;
            snd = fst + 1;
            while (snd < BOARD_WIDTH && data[snd][j].val == 0) snd++;
            if (snd >= BOARD_WIDTH) break;
            if ((!data[snd][j].isLocked && !data[fst][j].isLocked) ||
                (!data[snd][j].isLocked && data[snd][j].type == BLACKHOLE)) {
                handleMove(data[fst][j], data[snd][j]);
            }
            fst = snd;
        }
    }
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = 0, snd = 0;
        while (fst < BOARD_WIDTH && snd < BOARD_WIDTH) {
            while (fst < BOARD_WIDTH && data[fst][j].val != 0) fst++;
            if (fst >= BOARD_WIDTH) break;
            snd = fst + 1;
            while (snd < BOARD_WIDTH && data[snd][j].val == 0) snd++;
            if (snd >= BOARD_WIDTH) break;
            if (!data[snd][j].isLocked) {
                data[fst][j] = data[snd][j];
                set(data[snd][j], 0);
                fst++;
            } else {
                fst = snd + 1;
            }
        }
    }
    emitSignal();
    gen();
}
void Game::moveDown() {
    steps++;
    // qDebug() << "Entering down-moving processing...";
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = BOARD_WIDTH - 1, snd = BOARD_WIDTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && (data[fst][j].val == 0)) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[snd][j].val == 0) snd--;
            if (snd < 0) break;
            if ((!data[snd][j].isLocked && !data[fst][j].isLocked) ||
                (!data[snd][j].isLocked && data[snd][j].type == BLACKHOLE)) {
                handleMove(data[fst][j], data[snd][j]);
            }
            fst = snd;
        }
    }
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = BOARD_WIDTH - 1, snd = BOARD_WIDTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && data[fst][j].val != 0) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[snd][j].val == 0) snd--;
            if (snd < 0) break;
            if (!data[snd][j].isLocked) {
                data[fst][j] = data[snd][j];
                set(data[snd][j], 0);
                fst--;
            } else {
                fst = snd - 1;
            }
        }
    }
    emitSignal();
    gen();
}
void Game::emitSignal() {
    // debData();
    gameState state = check();
    if (state == WIN)
        emit win();
    else if (state == LOSE)
        emit lose();
    return;
}
gameState Game::check() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (data[i][j].val == 0) {
                full = 0;
                return CONTINUE;
            }
            if (data[i][j].val == 2048) return WIN;
        }
    }
    full = 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++)
            if (data[i][j].type != NUMBER && data[i][j].type != BARRIER)
                return CONTINUE;
    }
    for (int j = 0; j < BOARD_LENGTH; j++)
        for (int i = 0; i < BOARD_WIDTH - 1; i++)
            if (data[i][j].val == data[i + 1][j].val) return CONTINUE;
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_LENGTH - 1; j++)
            if (data[i][j].val == data[i][j + 1].val) return CONTINUE;
    return LOSE;
}
void Game::generate(double prob1, double prob2, double prob4, double prob8,
                    double prob16, double bomb, double and_, double or_,
                    double xor_, double blackhole, double lg2) {
    // qDebug() << "before generating: ";
    // debData();
    if (prob1 + prob2 + prob4 + prob8 + prob16 + bomb + and_ + or_ + xor_ +
            blackhole + lg2 !=
        100)
        qDebug() << "Error in generating! ";
    if (full) return;
    int x, y;
    do {
        x = rand() % 4, y = rand() % 4;
    } while (data[x][y].val != 0);
    int r = rand() % 100;
    // qDebug() << r;
    int val;
    if (r < prob1)
        val = 1;
    else if (r < prob1 + prob2)
        val = 2;
    else if (r < prob1 + prob2 + prob4)
        val = 4;
    else if (r < prob1 + prob2 + prob4 + prob8)
        val = 8;
    else if (r < prob1 + prob2 + prob4 + prob8 + prob16)
        val = 16;
    else {
        val = 16;
        r -= (prob1 + prob2 + prob4 + prob8 + prob16);
        data[x][y].val = -1;
        data[x][y].isLocked = 1;
        if (r < bomb) {
            data[x][y].type = BOMB;
            // qDebug() << "BOMB";
        } else if (r < bomb + and_) {
            data[x][y].type = AND;
            data[x][y].val = val;
            // qDebug() << "AND";
        } else if (r < bomb + and_ + or_) {
            // qDebug() << "OR";
            data[x][y].type = OR;
            data[x][y].val = val;
        } else if (r < bomb + and_ + or_ + xor_) {
            // qDebug() << "XOR";
            data[x][y].type = XOR;
            data[x][y].val = val;
        } else if (r < bomb + and_ + or_ + xor_ + blackhole) {
            // qDebug() << "BLACKHOLE";
            data[x][y].type = BLACKHOLE;
        } else {
            // qDebug() << "LG2";
            data[x][y].type = LG2;
        }
        return;
    }
    // qDebug() << val;
    if (val > maxVal) maxVal = val;
    data[x][y].val = val;
}
void Game::gen() {
    // generate(2, 2, 2, 6, 2, 17, 24, 23, 8, 8, 6);
    switch (maxVal) {
        case 1:
        case 2:
            generate();
            break;
        case 4:
            generate(50, 40, 10);
            break;
        case 8:
            generate(30, 40, 25, 5);
            break;
        default:
            generate(17, 24, 23, 8, 8, 6, 2, 2, 2, 6, 2);
            break;
    }
    saveFile();
}
void Game::debData() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            qDebug() << data[i][j].val;
        }
        qDebug() << '\n';
    }
    qDebug() << '\n';
    qDebug() << '\n';
}
int Game::getMaxTile() const { return maxVal; }
bool Game::is2Times(int val) {
    if (val == 0) return 1;
    if (val < 0) return 0;
    while (val != 1) {
        if (val % 2) return 0;
        val /= 2;
    }
    return 1;
}
int Game::lg2(int val) {
    int times = 0;
    int t = 1;
    while (t < val) {
        t *= 2;
        times++;
    }
    return times;
}
void Game::Bomb(int x, int y) {
    set(data[x][y], 0);
    if (x + 1 < BOARD_WIDTH) set(data[x + 1][y], 0);
    if (x - 1 >= 0) set(data[x - 1][y], 0);
    if (y + 1 < BOARD_LENGTH) set(data[x][y + 1], 0);
    if (y - 1 >= 0) set(data[x][y - 1], 0);
}
void Game::recoverLastStep() {
    // NUMBER, BOMB, AND, OR, XOR, BLACKHOLE, LG2, BARRIER
    steps--;
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/save/file.json");
    QString dataDir = QDir(exeDir).filePath("data/save");
    QDir().mkpath(dataDir);
    QFile file(filePath);
    if (!file.exists()) {                                   // 检查文件是否存在
        file.open(QIODevice::WriteOnly | QIODevice::Text);  // 不存在则创建
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in reading the file.json.";
        return;
    }
    QByteArray d = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(d);
    QJsonArray allSteps = doc.array();
    QJsonArray arr = allSteps[steps].toArray();
    score = arr[0].toObject()["score"].toInt();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            int idx = i * BOARD_WIDTH + j + 1;
            data[i][j].isLocked = arr[idx].toObject()["isLocked"].toBool();
            data[i][j].val = arr[idx].toObject()["val"].toInt();
            QString s = arr[idx].toObject()["type"].toString();
            if (s == "NUMBER")
                data[i][j].type = NUMBER;
            else if (s == "LG2")
                data[i][j].type = LG2;
            else if (s == "BOMB")
                data[i][j].type = BOMB;
            else if (s == "AND")
                data[i][j].type = AND;
            else if (s == "OR")
                data[i][j].type = OR;
            else if (s == "BLACKHOLE")
                data[i][j].type = BLACKHOLE;
            else if (s == "XOR")
                data[i][j].type = XOR;
            else if (s == "BARRIER")
                data[i][j].type = BARRIER;
            else {
                qDebug() << "Error in type reading!";
                return;
            }
        }
    }
    allSteps.removeLast();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in writing back the file.json.";
        return;
    }
    QJsonDocument doc2(allSteps);
    file.write(doc2.toJson());
    file.close();
}
void Game::saveFile() {
    QString exeDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(exeDir).filePath("data/save/file.json");
    QString dataDir = QDir(exeDir).filePath("data/save");
    QDir().mkpath(dataDir);
    QFile file(filePath);
    if (!file.exists()) {                                   // 检查文件是否存在
        file.open(QIODevice::WriteOnly | QIODevice::Text);  // 不存在则创建
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "1. Error in saving the file.json.";
        return;
    }
    QByteArray d = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(d);
    QJsonArray allSteps = doc.array();
    QJsonArray arr;
    QJsonObject t;
    t["score"] = score;
    arr.append(t);
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            QJsonObject obj;
            obj["val"] = data[i][j].val;
            obj["isLocked"] = data[i][j].isLocked;
            QString s;
            switch (data[i][j].type) {
                case NUMBER:
                    s = "NUMBER";
                    break;
                case BOMB:
                    s = "BOMB";
                    break;
                case LG2:
                    s = "LG2";
                    break;
                case AND:
                    s = "AND";
                    break;
                case OR:
                    s = "OR";
                    break;
                case XOR:
                    s = "XOR";
                    break;
                case BLACKHOLE:
                    s = "BLACKHOLE";
                    break;
                case BARRIER:
                    s = "BARRIER";
                    break;
                default:
                    qDebug() << "Error in recognising the type.";
                    break;
            }
            obj["type"] = s;
            arr.append(obj);
        }
    }
    allSteps.append(arr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error in saving the file.json.";
        return;
    }
    QJsonDocument doc2(allSteps);
    file.write(doc2.toJson());
    file.close();
}
