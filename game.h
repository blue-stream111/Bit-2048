#ifndef GAME_H
#define GAME_H
#include <QTimer>
#define BOARD_LENGTH 4
#define BOARD_WIDTH 4
enum gameState { WIN, LOSE, CONTINUE };

class Game : public QObject {
    Q_OBJECT
public:
    Game();
    ~Game();
    bool isActive();
    void suspend();
    void start();
    void goOn();
    int read(int x, int y);
    int getTime();
    int getScore();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void emitSignal();
    void generate(double prob1 = 90, double prob2 = 10, double prob4 = 0,
                  double prob8 = 0, double prob16 = 0);
    int getMaxTile();

private slots:
    void addTime();
signals:
    void lose();
    void win();

private:
    QTimer* timer;
    int data[BOARD_WIDTH][BOARD_LENGTH];
    int score;
    int time;
    int maxVal;
    bool full;
    gameState check();
    void gen();
    void debData();
};

#endif  // GAME_H
