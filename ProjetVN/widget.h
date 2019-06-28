#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>
#include <QString>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void ChangerTexte();

    void lireBandeSons(int _maScene);
private slots:
    void on_pushButtonTexte_clicked();

    void on_pushButtonPlay_clicked();

private:
    Ui::Widget *ui;
    int texteDeScene;
    int fondDeScene;
    QGraphicsScene maScene;
    QMediaPlayer player;
};

#endif // WIDGET_H
