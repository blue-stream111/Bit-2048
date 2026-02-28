#ifndef SAVEFORM_H
#define SAVEFORM_H

#include <QContextMenuEvent>
#include <QListWidgetItem>
#include <QMenu>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class saveForm;
}

class saveForm : public QWidget {
    Q_OBJECT

public:
    explicit saveForm(QWidget* parent = nullptr);
    ~saveForm();
    void paintEvent(QPaintEvent*) override;
public slots:
    void start();
    void record(int time, int step, QString name);
signals:
    void back();
    void startGame(QString fileName);

private slots:
    void on_pushBack_clicked();
    void onSaveItemClicked(QListWidgetItem* item);

    void on_pushClear_clicked();

protected:
    void contextMenuEvent(QContextMenuEvent*) override;

private:
    Ui::saveForm* ui;
    void init();
    QPixmap scaledbg;
    bool deleteSave(QListWidgetItem* item);
    int getIdx(QString filePath);
    int tot;
};

#endif  // SAVEFORM_H
