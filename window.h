#ifndef WINDOW_H
#define WINDOW_H

#include "game.h"
#include "settings.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void SetDifficult (int dif);

private:
    int Height;
    int Wight;
    int difficult;
    QPushButton* start;
    QPushButton* setting;
    QPushButton* exit;
    int x;
    int y;
    void draw_text(QPainter & p);

private slots:
    void starts();
    void settings_func();
};

#endif // WINDOW_H
