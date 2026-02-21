#include "game.h"

#include <qDebug>
Game::Game() {
    qDebug() << "Now initial game.";
    timer = new QTimer(this);
    score = 0;
    full = 0;
    time = 0;
    maxVal = 1;
    // maxTimes = 1;
    QObject::connect(timer, &QTimer::timeout, this, &Game::addTime);
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_LENGTH; j++) data[i][j] = 0;
    generate();
    generate();
}
Game::~Game() {}
void Game::start() { timer->start(1000); }
void Game::goOn() { timer->start(); }
void Game::suspend() { timer->stop(); }
int Game::read(int x, int y) { return data[x][y]; }
bool Game::isActive() { return timer->isActive(); }
int Game::getScore() { return score; }
int Game::getTime() { return time; }
void Game::addTime() {
    time++;
    timer->start(1000);
}
void Game::moveLeft() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = 0, snd = 0;
        while (fst < BOARD_LENGTH && snd < BOARD_LENGTH) {
            while (fst < BOARD_LENGTH && data[i][fst] == 0) fst++;
            if (fst >= BOARD_LENGTH) break;
            snd = fst + 1;
            while (snd < BOARD_LENGTH && data[i][snd] == 0) snd++;
            if (snd >= BOARD_LENGTH) break;
            if (data[i][fst] == data[i][snd]) {
                data[i][fst] *= 2;
                if (data[i][fst] > maxVal) maxVal = data[i][fst];
                score += data[i][fst];
                data[i][snd] = 0;
            }
            fst = snd;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = 0;
        while (fst < BOARD_LENGTH) {
            while (fst < BOARD_LENGTH && data[i][fst]) fst++;
            if (fst >= BOARD_LENGTH) break;
            int snd = fst + 1;
            while (snd < BOARD_LENGTH && data[i][snd] == 0) snd++;
            if (snd >= BOARD_LENGTH) break;
            data[i][fst] = data[i][snd];
            data[i][snd] = 0;
            fst++;
        }
    }
    emitSignal();
    gen();
}
void Game::moveRight() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = BOARD_LENGTH - 1, snd = BOARD_LENGTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && data[i][fst] == 0) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[i][snd] == 0) snd--;
            if (snd < 0) break;
            if (data[i][fst] == data[i][snd]) {
                data[i][fst] *= 2;
                if (data[i][fst] > maxVal) maxVal = data[i][fst];
                score += data[i][fst];
                data[i][snd] = 0;
            }
            fst = snd;
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int fst = BOARD_LENGTH - 1;
        while (fst >= 0) {
            while (fst >= 0 && data[i][fst]) fst--;
            if (fst < 0) break;
            int snd = fst - 1;
            while (snd >= 0 && data[i][snd] == 0) snd--;
            if (snd < 0) break;
            data[i][fst] = data[i][snd];
            data[i][snd] = 0;
            fst--;
        }
    }
    emitSignal();
    gen();
}
void Game::moveUp() {
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = 0, snd = 0;
        while (fst < BOARD_WIDTH && snd < BOARD_WIDTH) {
            while (fst < BOARD_WIDTH && data[fst][j] == 0) fst++;
            if (fst >= BOARD_WIDTH) break;
            snd = fst + 1;
            while (snd < BOARD_WIDTH && data[snd][j] == 0) snd++;
            if (snd >= BOARD_WIDTH) break;
            if (data[fst][j] == data[snd][j]) {
                data[fst][j] *= 2;
                if (data[fst][j] > maxVal) maxVal = data[fst][j];
                score += data[fst][j];
                data[snd][j] = 0;
            }
            fst = snd;
        }
    }
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = 0, snd = 0;
        while (fst < BOARD_WIDTH && snd < BOARD_WIDTH) {
            while (fst < BOARD_WIDTH && data[fst][j]) fst++;
            if (fst >= BOARD_WIDTH) break;
            snd = fst + 1;
            while (snd < BOARD_WIDTH && data[snd][j] == 0) snd++;
            if (snd >= BOARD_WIDTH) break;
            data[fst][j] = data[snd][j];
            data[snd][j] = 0;
            fst++;
        }
    }
    emitSignal();
    gen();
}
void Game::moveDown() {
    // qDebug() << "Entering down-moving processing...";
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = BOARD_WIDTH - 1, snd = BOARD_WIDTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && data[fst][j] == 0) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[snd][j] == 0) snd--;
            if (snd < 0) break;
            if (data[fst][j] == data[snd][j]) {
                data[fst][j] *= 2;
                if (data[fst][j] > maxVal) maxVal = data[fst][j];
                score += data[fst][j];
                data[snd][j] = 0;
            }
            fst = snd;
        }
    }
    for (int j = 0; j < BOARD_LENGTH; j++) {
        int fst = BOARD_WIDTH - 1, snd = BOARD_WIDTH - 1;
        while (fst >= 0 && snd >= 0) {
            while (fst >= 0 && data[fst][j]) fst--;
            if (fst < 0) break;
            snd = fst - 1;
            while (snd >= 0 && data[snd][j] == 0) snd--;
            if (snd < 0) break;
            data[fst][j] = data[snd][j];
            data[snd][j] = 0;
            fst--;
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
            if (data[i][j] == 0) {
                full = 0;
                return CONTINUE;
            }
            if (data[i][j] == 2048) return WIN;
        }
    }
    full = 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH - 1; j++)
            if (data[i][j] == data[i][j + 1]) return CONTINUE;
    }
    for (int j = 0; j < BOARD_LENGTH; j++)
        for (int i = 0; i < BOARD_WIDTH - 1; i++)
            if (data[i][j] == data[i + 1][j]) return CONTINUE;
    return LOSE;
}
void Game::generate(double prob1, double prob2, double prob4, double prob8,
                    double prob16) {
    if (prob1 + prob2 + prob4 + prob8 + prob16 != 100)
        qDebug() << "Error in generating! ";
    if (full) return;
    int x, y;
    do {
        x = rand() % 4, y = rand() % 4;
    } while (data[x][y] != 0);
    int r = rand() % 100;
    qDebug() << r;
    int val;
    if (r < prob1)
        val = 1;
    else if (r < prob1 + prob2)
        val = 2;
    else if (r < prob1 + prob2 + prob4)
        val = 4;
    else if (r < prob1 + prob2 + prob4 + prob8)
        val = 8;
    else
        val = 16;
    qDebug() << val;
    if (val > maxVal) maxVal = val;
    data[x][y] = val;
}
void Game::gen() {
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
            generate(25, 35, 30, 5, 5);
            break;
    }
}
void Game::debData() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            qDebug() << data[i][j];
        }
        qDebug() << '\n';
    }
}
int Game::getMaxTile() { return maxVal; }
