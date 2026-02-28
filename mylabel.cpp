#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {
    setAlignment(Qt::AlignCenter);
    setWordWrap(1);
    num = nullptr;
}
void MyLabel::match(Num* n, int i, int j) {
    x = i;
    y = j;
    num = n;
    QString s;
    setColor();
    if (num->type == NUMBER) {
        setText(toBinary(num->val));
    } else {
        setTxt();
    }
}
void MyLabel::setTxt() {
    QString s;
    if (num->type == BOMB)
        s = "Bomb";
    else if (num->type == BLACKHOLE)
        s = "Black\nHole";
    else if (num->type == LG2)
        s = "lg2";
    else {
        if (num->type == AND)
            s = "AND\n";
        else if (num->type == OR)
            s = "OR\n";
        else if (num->type == XOR)
            s = "XOR\n";
        else if (num->type == BARRIER)
            s = "BARRIER!\n";
        s += toBinary(num->val);
    }
    if (num->isLocked)
        s += "\n(Locked)";
    else
        s += "\n(Unlocked)";
    setText(s);
}
void MyLabel::mousePressEvent(QMouseEvent* event) {
    if (num == nullptr) {
        qDebug() << "Error in matching.";
        return;
    }
    if (num->type == NUMBER || num->type == BARRIER) return;
    num->isLocked = !num->isLocked;
    setTxt();
    if (num->isLocked == 0 && num->type == BOMB) emit bomb(x, y);
}
QString MyLabel::toBinary(int val) {
    if (val == 0) return "";
    QString s = "";
    while (val) {
        if (val % 2)
            s = QString::number(1) + s;
        else
            s = QString::number(0) + s;
        val /= 2;
    }
    while (s.length() < 4) s = QString::number(0) + s;
    return s;
}
void MyLabel::setColor() {
    QString rgb;
    if (num->type == NUMBER) switch (num->val) {
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
                rgb = "rgb(27, 204, 97);";
                break;
            case 256:
                rgb = "rgb(237, 204, 197);";
                break;
            case 512:
                rgb = "rgb(57, 154, 197);";
                break;
            case 1024:
                rgb = "rgb(157, 204, 97);";
                break;
            case 2048:
                rgb = "rgb(106, 0, 95);";
                break;
            default:
                break;
        }
    else if (num->type == BLACKHOLE)
        rgb = "rgb(0, 0, 0);";
    else if (num->type == BOMB)
        rgb = "rgb(128, 128, 128);";
    else
        rgb = "rgb(255, 255, 255);";
    QString setting = "background-color: " + rgb;
    if (num->type == BLACKHOLE)
        setting += "color: white;";
    else
        setting += "color: black;";
    // qDebug() << num->val << ": " << setting;
    this->setStyleSheet(setting);
    return;
}
