#ifndef GAME_H
#define GAME_H

#include <QKeyEvent>
#include <QTextStream>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <QPainter>
#include "map.h"
#include "finish.h"

class Game : public QWidget
{
    Q_OBJECT

private:
    Map* p;
    QPushButton* right;
    QPushButton* left;
    QPushButton* up;
    QPushButton* down;
    QPushButton* b;
    QLabel* score_show;
    QLabel* record_show;
    QLabel* number_show;
    Cube* cube;
    QString s,s1;
    QFile* file;
    QString  score_prev;
    void score();
    void check();
    void game_over (bool wl);

public:
    Game (QWidget *parent = 0);
    void keyPressEvent (QKeyEvent *event);
    void timerEvent(QTimerEvent *);
    void set_difficult (int difficult);
    ~Game ();

private slots:
    void move_right ();
    void move_left ();
    void move_up ();
    void move_down ();
};

#endif // GAME_H
