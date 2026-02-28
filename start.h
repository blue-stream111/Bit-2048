#ifndef START_H
#define START_H

#include <QPainter>
#include <QWidget>

namespace Ui {
class start;
}

class start : public QWidget {
    Q_OBJECT

public:
    explicit start(QWidget* parent = nullptr);
    ~start();
    void paintEvent(QPaintEvent*) override;

public slots:
    void on_pushStart_clicked();

    void on_pushHelp_clicked();

    void on_pushLeave_clicked();

    void getBack();

signals:

    void startGame(QString name = "");
    void getSavings();

private slots:
    void on_pushSave_clicked();

private:
    Ui::start* ui;
    QPixmap scaledBg;
};

#endif  // START_H
