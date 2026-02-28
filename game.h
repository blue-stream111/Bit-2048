#ifndef GAME_H
#define GAME_H
#include <QTimer>
#define BOARD_LENGTH 4
#define BOARD_WIDTH 4
enum gameState { WIN, LOSE, CONTINUE };
enum MyNumType { NUMBER, BOMB, AND, OR, XOR, BLACKHOLE, LG2, BARRIER };

struct Num {
    // val is valid when type is NUMBER, AND, OR, or XOR.
    // and when type is others, val is set -1.
    // blank tail's val eqauls to 0 and type is NUMBER.
    // and the bomb will bomb as soon as it's unlocked.
    MyNumType type;
    bool isLocked;
    int val;
};

class Game : public QObject {
    Q_OBJECT
public:
    Game();
    Game(QString filePath);
    ~Game();
    bool isActive();
    void suspend();
    void start();
    void goOn();
    Num* read(int x, int y);
    int getTime() const;
    int getScore() const;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void emitSignal();
    void generate(double prob1 = 90, double prob2 = 10, double prob4 = 0,
                  double prob8 = 0, double prob16 = 0, double bomb = 0,
                  double and_ = 0, double or_ = 0, double xor_ = 0,
                  double blackhole = 0, double lg2 = 0);
    int getMaxTile() const;
    void debData();
    void Bomb(int x, int y);
    QString getName() const { return name; }
    void setName(QString s) { name = s; }
    int getStep() const { return steps; }
    void recoverLastStep();

private slots:
    void addTime();
signals:
    void lose();
    void win();

private:
    QTimer* timer;
    QString name;
    Num data[BOARD_WIDTH][BOARD_LENGTH];
    int score;
    int time;
    int maxVal;
    bool full;
    gameState check();
    void gen();
    void handleMove(Num& fst, Num& snd);
    void set(Num& num, int n);
    int lg2(int val);
    bool is2Times(int val);
    void saveFile();
    void clearFile();
    int steps;
};

#endif  // GAME_H
