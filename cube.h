#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <cmath>
#include <QString>
#include "Cube_.h"

using namespace std;

class Cube : public QGLWidget
{
    Q_OBJECT

public:
    Cube(QWidget *parent = 0);
    void initializeGL();
    void paintGL ();
    void resizeGL (int w, int h);
    void mousePressEvent (QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);
    ~Cube();
    void show_plane (int n);
    void left();
    void right();
    void up();
    void down();
    QString score ();
    void difficult_game (int dif);
    int is_nomber ();
    Cube_* get();
    bool is_win ();
    bool is_lose ();

private:
    QPoint last;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLfloat rotX;
    GLfloat rt;
    GLfloat rotZ;
    QColor color[6];//массив цветов
    GLfloat check;
    Cube_* logic;
    GLfloat quads_coord [4][4][3][6];
    GLuint textureID[11];
    int  matrix[4][4];
    int difficult;
    int a[4][4];
    void rotate(GLfloat kx, GLfloat ky);
    void fill_coord ();
    void draw_cube ();
    void draw_quads ();
    void draw_field (GLfloat x, GLfloat y, GLfloat z);
    void genTextures ();
    GLuint getTexture (int value);
    int is_nomber_up ();
    int is_nomber_down ();
    int is_nomber_right ();
    int is_nomber_left ();

};
#endif // WIDGET_H
