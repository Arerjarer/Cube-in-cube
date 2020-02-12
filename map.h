#ifndef MAP_H
#define MAP_H

#include "cube.h"
#include <QPushButton>
#include <QHBoxLayout>

class Map : public QWidget
{
    Q_OBJECT
public:
    Map( Cube *cube);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    int x;
    int y;
    Cube* log;
    QString get_texture(int value);
    QPushButton** p;
    void draw(QPainter& p, int num, int X);

private slots:
    void slot ();

};

#endif // MAP_H
