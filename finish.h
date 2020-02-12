#ifndef FINISH_H
#define FINISH_H

#include "window.h"

class Finish : public QWidget
{
    Q_OBJECT
public:
    Finish(Cube *cube, bool wl, int record);

private:
    Cube* cubic;
    QString gif;
    QString text;
    QMovie *v;
    QLabel *l;
    QLabel *l1;
    QLabel *l2;
    QPushButton* new_game;
    QPushButton* exit;

private slots:
    void new_games();
};

#endif // FINISH_H
