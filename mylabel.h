#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QMouseEvent>

#include "game.h"
class MyLabel : public QLabel {
    Q_OBJECT
public:
    MyLabel(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent*) override;
    void match(Num* n, int i, int j);

private:
    Num* num;
    int x;
    int y;
    void setColor();
    QString toBinary(int val);
    void setTxt();

signals:
    void bomb(int x, int y);
};

#endif  // MYLABEL_H
