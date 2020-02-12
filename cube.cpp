#include "cube.h"
#include <window.h>

Cube::Cube(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGL::DoubleBuffer|QGL::DepthBuffer);
    //(+) Double buffer -- двойная буферизация (два буфера: задний и передний): установлена
    //(+) Depth buffer -- буфер глубины: установлен
    setMaximumSize(475,450);
    rotationX = 15;
    rotationY = -15;
    rotationZ = 0;
    rotX = 15;
    check = 0;
    difficult = 1;

    logic = new Cube_();
    logic -> Rand_Set_Value();

    fill_coord();
}

Cube::~Cube()
{
    delete logic;
    makeCurrent ();
    glDeleteTextures (11, textureID);
}

void Cube::show_plane(int n)
{
    switch (n) {
    case 1:
        rotationX = 15;
        rotationY = -15;
        rotationZ = 0;
        updateGL();
        break;
    case 2:
        rotationX = 15;
        rotationY = -105;
        rotationZ = 0;
        updateGL();
        break;
    case 3:
        rotationX = 15;
        rotationY = 165;
        rotationZ = 0;
        updateGL();
        break;
    case 4:
        rotationX = 15;
        rotationY = 75;
        rotationZ = 0;
        updateGL();
        break;
    case 5:
        rotationX = 105;
        rotationY = 0;
        rotationZ = 15;
        updateGL();
        break;
    case 6:
        rotationX = -75;
        rotationY = 0;
        rotationZ = -15;
        updateGL();
        break;
    default:
        break;
    }

}

void Cube::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);// устанавливает режим проверки глубины пикселей
    glEnable(GL_CULL_FACE);//рисовать только внешние поверхности
    glEnable(GL_TEXTURE_2D); // установить режим текстур
    genTextures(); // создать текстуры
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_BLEND);
    // Сглаживание точек
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    // Сглаживание линий
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Cube::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);// текущей матрицей для преобразований станет матрица проекции
    glLoadIdentity();//загружает единичную матрицу в матрицу проекции
    GLfloat x = (GLfloat)w / h;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);// перспективная проекция
    //плоскости отсечения: (левая, правая, верхняя, нижняя, ближняя, дальняя)
    //ортогональная проекция - glOrtho()
    glViewport(0, 0, (GLint)w, (GLint)h); //поле просмотра
}

void Cube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//очищает буферы изображения и глубины

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glPushMatrix();

    glTranslatef(0.0, 0.0, -8.5);//сдвиг

    glRotatef(rotationX, 1.0, 0.0, 0.0);//вращение по осям
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    GLfloat  matMV[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, matMV);

    for(int i =0;i<4;i++)
    {
        for(int j =0;j<4;j++)
        {
            int t =  0;
            if (matMV[j+4*i]>0)
            {
                t = floor( matMV[j+4*i]+0.5);
            }
            if (matMV[j+4*i]<0)
            {
                t = ceil( matMV[j+4*i]-0.5);
            }
            matrix[i][j]= t;
        }
    }

    draw_cube();
    draw_quads();

    draw_field(1.012,1,1);
    draw_field(-1.012,-1,-1);
    draw_field(1,-1.012,-1);
    draw_field(-1,1.012,1);

    draw_field(-1,-1,1.012);
    draw_field(1,1,-1.012);

    glPopMatrix();
}

void Cube::draw_cube()
{
    static const GLfloat coords[6][4][3] = {
        { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 },
          { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 },
          { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } },
        { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 },
          { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } },
        { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 },
          { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 },
          { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } },
        { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 },
          { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }
    };
    for (int i = 0; i < 6; ++i) {
        glLoadName (i);
        glBegin (GL_QUADS);
        qglColor (QColor(255, 255, 153));
        for (int j = 0; j < 4; ++j) {
            glVertex3f (coords[i][j][0], coords[i][j][1], coords[i][j][2]);

        }
        glEnd ();
    }
}

void Cube::draw_quads()
{
    GLfloat k = 0;
    GLfloat tx = 0;
    GLfloat ty = 0;

    qglColor (Qt::white);
    if (matrix[1][1] > 0)
    {
        tx = 0.0;
        ty = 1.0;
    }
    if (matrix[1][1] < 0)
    {
        tx = 1.0;
        ty = 0.0;
    }

    if (matrix[1][1] == 0)
    {
        {
            if (matrix[1][0]<=0)
            {
                tx = 0.0;
                ty = 1.0;
            }
            if (matrix[1][0]>0)
            {
                tx = 1.0;
                ty = 0.0;
            }
        }
    }

    for (int h = 0; h < 6; ++h)
    {
        Plane* plane = NULL;

        if (fabs(quads_coord[0][0][0][h]) == GLfloat(1.01))
        {
            if (quads_coord[0][0][2][h] > 0)
            {
                plane = logic -> Get_Plane_2 ();
                k = -0.48;
            }
            else
            {
                plane = logic -> Get_Plane_4 ();
                k = 0.48;
            }

            for (int i = 0; i < 4; ++i)
            {
                glLoadName (i);
                for (int j = 0; j < 4; ++j)
                {
                    glBindTexture (GL_TEXTURE_2D,getTexture(plane -> Get_Cell(i,j) -> Get_Value()));
                    glBegin (GL_QUADS);
                    {
                        if (matrix[1][1]==0)
                        {
                            if ((is_nomber()==5)||(is_nomber()==6))
                            {
                                if (plane == logic->Get_Plane_4())
                                {
                                    if ((matrix[2][1] > 0))
                                    {
                                        tx =0.0;
                                        ty =1.0;

                                    }
                                    else
                                    {
                                        tx = 1.0;
                                        ty = 0.0;
                                    }
                                }
                                else
                                {
                                    if ((matrix[2][1] > 0))
                                    {
                                        tx =1.0;
                                        ty =0.0;

                                    }
                                    else
                                    {
                                        tx = 0.0;
                                        ty = 1.0;
                                    }
                                }
                            }

                            glTexCoord2f (tx, tx);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h] + k);
                            glTexCoord2f (ty, tx);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                            glTexCoord2f (ty, ty);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h]);
                            glTexCoord2f (tx, ty);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h] + k);
                        }
                        else
                        {
                            glTexCoord2f (tx, ty);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h] + k);
                            glTexCoord2f (tx, tx);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                            glTexCoord2f (ty, tx);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h]);
                            glTexCoord2f (ty, ty);
                            glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h] + k);
                        }
                    }
                    glEnd ();
                }
            }
        }
        if (fabs(quads_coord[0][0][1][h]) == GLfloat(1.01))
        {
            if (quads_coord[0][0][0][h] > 0)
            {
                plane = logic -> Get_Plane_6 ();
                k = -0.48;
            }
            else
            {
                plane = logic -> Get_Plane_5 ();
                k = 0.48;
            }

            for (int i = 0; i < 4; ++i)
            {
                glLoadName (i);
                for (int j = 0; j < 4; ++j)
                {
                    if (plane == logic->Get_Plane_6())
                    {
                        glBindTexture (GL_TEXTURE_2D,getTexture(plane -> Get_Cell(3-i,3-j) -> Get_Value()));
                    }
                    else
                    {
                        glBindTexture (GL_TEXTURE_2D,getTexture(plane -> Get_Cell(i,j) -> Get_Value()));
                    }
                    glBegin (GL_QUADS);
                    if (matrix[1][1]==0)
                    {
                        if (matrix[2][1]<=0)
                        {
                            tx = 0.0;
                            ty =1.0;
                        }
                        else
                        {
                            tx = 1.0;
                            ty =0.0;
                        }
                    }
                    if ((is_nomber() == 1))
                    {
                        if (plane == logic->Get_Plane_6())
                        {
                            if (matrix [1][1]>0)
                            {
                                tx = 1.0;
                                ty =0.0;
                            }
                            else
                            {
                                tx = 0.0;
                                ty =1.0;
                            }
                        }
                        if (plane == logic->Get_Plane_5())
                        {
                            if (matrix [1][1]>0)
                            {
                                tx = 0.0;
                                ty =1.0;
                            }
                            else
                            {
                                tx = 1.0;
                                ty =0.0;
                            }
                        }
                    }

                    if ((plane == logic->Get_Plane_5())&&(is_nomber() == 3))
                    {
                        if (matrix [1][1]>0)
                        {
                            tx = 1.0;
                            ty =0.0;
                        }
                        else
                        {
                            tx = 0.0;
                            ty =1.0;
                        }
                    }

                    {
                        glTexCoord2f (tx, ty);
                        glVertex3d (quads_coord[i][j][0][h] + k, quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                        glTexCoord2f (tx, tx);
                        glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                        glTexCoord2f (ty, tx);
                        glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h] + 0.48);
                        glTexCoord2f (ty, ty);
                        glVertex3d (quads_coord[i][j][0][h] + k, quads_coord[i][j][1][h], quads_coord[i][j][2][h] + 0.48);
                    }
                    glEnd ();
                }

            }
        }
        if (fabs(quads_coord[0][0][2][h]) == GLfloat(1.01))
        {
            if (quads_coord[0][0][0][h] > 0)
            {
                plane = logic -> Get_Plane_3();
                k = -0.48;
            }
            else
            {
                plane = logic -> Get_Plane_1();
                k=0.48;
            }

            for (int i = 0; i < 4; ++i)
            {
                glLoadName (i);
                for (int j = 0; j < 4; ++j)
                {
                    glBindTexture (GL_TEXTURE_2D,getTexture(plane -> Get_Cell(i,j) -> Get_Value()));
                    glBegin(GL_QUADS);
                    {
                        glTexCoord2f (tx, ty);
                        glVertex3d (quads_coord[i][j][0][h] + k, quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                        glTexCoord2f (tx, tx);
                        glVertex3d (quads_coord[i][j][0][h], quads_coord[i][j][1][h], quads_coord[i][j][2][h]);
                        glTexCoord2f (ty, tx);
                        glVertex3d (quads_coord[i][j][0][h] ,quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h]);
                        glTexCoord2f (ty, ty);
                        glVertex3d (quads_coord[i][j][0][h] + k, quads_coord[i][j][1][h] - 0.48, quads_coord[i][j][2][h]);
                    }
                    glEnd();
                }
            }
        }
    }

}
void Cube::draw_field (GLfloat x,GLfloat y,GLfloat z)
{
    GLfloat k = 0;
    if ((x == GLfloat(1.012)) || (x == GLfloat(-1.012)))
    {
        if (x == GLfloat(1.012))
        {
            k = -1;
        }
        else
        {
            k = 1;
        }

        while (z != k)
        {
            glBegin (GL_LINE_STRIP);
            qglColor (Qt::black);
            glVertex3f (x,y, z);
            glVertex3f (x,-y, z);
            z += k / 2;
            glEnd ();
        }

        while (y != k)
        {
            glBegin (GL_LINE_STRIP);
            qglColor (Qt::black);
            glVertex3f (x,y,-z);
            glVertex3f (x,y, z);
            y += k / 2;
            glEnd ();
        }

    }
    if  ((z==GLfloat(1.012))||(z==GLfloat(-1.012)))
    {

        if (z ==GLfloat(1.012))
        {
            k = 1;
        }
        else
        {
            k = -1;
        }

        while (x != k)
        {
            glBegin (GL_LINE_LOOP);
            qglColor (Qt::black);
            glVertex3f (x,y, z);
            glVertex3f (x, -y, z);

            glEnd ();
            x += k / 2;
        }

        while (y != k)
        {
            glBegin (GL_LINE_LOOP);
            qglColor (Qt::black);
            glVertex3f (x,y,z);
            glVertex3f (-x,y,z);
            y += k / 2;
            glEnd ();
        }

    }
    if  ((y == GLfloat(1.012)) || (y == GLfloat(-1.012)))
    {
        if (y == GLfloat(1.012))
        {
            k = -1;
        }
        else
        {
            k = 1;
        }

        while (x != -k)
        {
            glBegin (GL_LINE_STRIP);
            qglColor (Qt::black);
            glVertex3f (x,y, -z);
            glVertex3f (x, y, z);
            x += ( -k / 2 );
            glEnd ();
        }

        while (z != k)
        {
            glBegin (GL_LINE_STRIP);
            qglColor (Qt::black);
            glVertex3f (x,y,z);
            glVertex3f (-x,y,z);
            z += k / 2;
            glEnd ();
        }

    }
}

void Cube::genTextures()
{
    QString name;

    for (int i = 0; i < 11; i++)
    {
        name.push_back (":/texture/");
        name.push_back (QString::number(i));
        name.push_back (".jpg");

        textureID[i] = bindTexture (QPixmap(name), GL_TEXTURE_2D);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        name.clear ();
    }
}

GLuint Cube::getTexture(int value)
{
    switch (value) {
    case 0:
        return textureID[0];
        break;
    case 3:
        return textureID[1];
        break;
    case 9:
        return textureID[2];
        break;
    case 27:
        return textureID[3];
        break;
    case 81:
        return textureID[4];
        break;
    case 243:
        return textureID[5];
        break;
    case 729:
        return textureID[6];
        break;
    case 2187:
        return textureID[7];
        break;
    case 6561:
        return textureID[8];
        break;
    case 19683:
        return textureID[9];
        break;
    case 59049:
        return textureID[10];
        break;
    default:
        break;
    }
    return textureID[0];
}

void Cube::mousePressEvent(QMouseEvent *event)
{

    last = event -> pos();
}

void Cube::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat kx = GLfloat (event -> x() - last.x()) / height();//наклон к y
    GLfloat ky = GLfloat (event -> y() - last.y()) / width();//наклон к x

    if (event -> buttons() & Qt::LeftButton)
    {
        if (check == 0)
        {
            if (fabs(fabs(rotationX) -fabs(rotX)) < 120)
            {
                rotate (kx,ky);
                /*rotationY += 180 * kx;
                rotationX += 180 * ky;
                rotationZ = 0;*/
                updateGL();

            }
            else
            {
                rotate (-kx,ky);
                /* rotationY += 180 * -kx;
                rotationX += 180 * ky;
                rotationZ = 0;*/
                updateGL();
                if (fabs(fabs(rotationX) -fabs(rotX)) > 300)// && (fabs(rotationX - rotX) < 290))
                {
                    rotX = rotationX;
                    check = 1;

                }
            }
        }
        if ((check==1)&&(fabs(rotX) > fabs(rotationX)))
        {
            check = 2;
        }
        if ((check==2)&&(fabs(rotX) < fabs(rotationX)))
        {
            check = 1;
        }
        /* if (rotationX<-55)
            {check = 1;
            }*/
        if (check == 1){

            if (fabs(fabs(rotationX) -fabs(rotX)) < 180)
            {
                rotate (kx,ky);

                /*rotationY += 180 * kx;
                    rotationX += 180 * ky;
                    rotationZ = 0;*/
                updateGL();

            }
            else
            {
                rotate (-kx,ky);
                /*rotationY += 180 * -kx;
                    rotationX += 180 * ky;
                    rotationZ = 0;*/
                updateGL();

                if (((fabs(fabs(rotationX) -fabs(rotX)) > 360)/* && (fabs(rotationX - rotX) < 380)*/))
                {
                    rotX = rotationX;
                }

            }
        }
        if (check == 2)
        {
            if (fabs(fabs(rotationX) -fabs(rotX)) < 180)
            {

                rotate (-kx,ky);
                /*rotationY += 180 * ( - kx);
                    rotationX += 180 * ky;
                    rotationZ = 0;*/
                updateGL();

            }
            else
            {
                rotate (kx,ky);
                /*rotationY += 180 * kx;
                    rotationX += 180 * ky;
                    rotationZ = 0;*/
                updateGL();

                if ((fabs(fabs(rotationX) -fabs(rotX)) > 360))//|| )/*&& (fabs(rotationX - rotX) < 380)*/
                {
                    rotX = rotationX;
                }
            }

        }
    }
    last = event -> pos();
}

int Cube::is_nomber()
{
    int result = 1;

    if (matrix[0][2] == 1)
    {
        result = 2;
    }
    if (matrix[0][2] == -1)
    {
        result = 4;
    }
    if (matrix[1][2] == 1)
    {
        result = 5;
    }
    if (matrix[1][2] == -1)
    {
        result = 6;
    }
    if (matrix[2][2] == 1)
    {
        result = 1;
    }
    if (matrix[2][2] == -1)
    {
        result = 3;
    }

    return result;

}

int Cube::is_nomber_up()
{
    int result = 1;
    if (matrix[1][1] != 0)
    {
        if ((is_nomber() == 1)||(is_nomber() == 2)||(is_nomber() == 3)||(is_nomber() == 4))
        {
            if (matrix[1][1] > 0)
            {
                result = 5;
            }
            if (matrix[1][1] < 0)
            {
                result = 6;
            }
        }
    }
    else
    {
        if ((is_nomber() == 5)||(is_nomber() == 2)||(is_nomber() == 6)||(is_nomber() == 4))
        {
            if (matrix[2][1] < 0)
            {
                result = 3;
            }
            else
            {
                result = 1;
            }
        }
    }

    return result;

}

int Cube::is_nomber_down()
{
    int result = 1;
    if (matrix[1][1] != 0)
    {
        if ((is_nomber() == 1)||(is_nomber() == 2)||(is_nomber() == 3)||(is_nomber() == 4))
        {
            if (matrix[1][1] > 0)
            {
                result = 6;
            }
            if (matrix[1][1] < 0)
            {
                result = 5;
            }
        }
    }
    else
    {
        if ((is_nomber() == 5)||(is_nomber() == 2)||(is_nomber() == 6)||(is_nomber() == 4))
        {
            if (matrix[2][1] < 0)
            {
                result = 1;
            }
            else
            {
                result = 3;
            }
        }
    }

    return result;

}

int Cube::is_nomber_right()
{
    int result = 1;
    if (matrix[1][1] != 0)
    {
        if (is_nomber() == 1)
        {
            if (matrix[1][1] >= 0)
            {
                result = 2;
            }
            else
            {
                result = 4;
            }
        }

        if (is_nomber() == 2)
        {
            if (matrix[1][1] >= 0)
            {
                result = 3;
            }
            else
            {
                result = 1;
            }
        }

        if (is_nomber() == 3)
        {
            if (matrix[1][1] >= 0)
            {
                result = 4;
            }
            else
            {
                result = 2;
            }
        }
        if (is_nomber() == 4)
        {
            if (matrix[1][1] >= 0)

            {
                result = 1;
            }
            else
            {
                result = 3;
            }
        }
    }
    else
    {
        if (is_nomber() == 2)
        {
            if (matrix[2][1] < 0)
            {
                result = 6;
            }
            else
            {
                result = 5;
            }
        }
        if (is_nomber() == 4)
        {
            if (matrix[2][1] < 0)
            {
                result = 5;
            }
            else
            {
                result = 6;
            }
        }
        if (is_nomber() == 5)
        {
            if (matrix[2][1] < 0)
            {
                result = 2;
            }
            else
            {
                result = 4;
            }
        }
        //4 - 5 cghfdf
        if (is_nomber() == 6)
        {
            if (matrix[2][1] < 0)
            {
                result = 4;
            }
            else
            {
                result = 2;
            }
        }
    }
    return result;

}

int Cube::is_nomber_left()
{
    int result = 1;
    if (matrix[1][1] != 0)
    {
        if (is_nomber() == 1)
        {
            if (matrix[1][1] >= 0)
            {
                result = 4;
            }
            else
            {
                result = 2;
            }
        }

        if (is_nomber() == 2)
        {
            if (matrix[1][1] >= 0)
            {
                result = 1;
            }
            else
            {
                result = 3;
            }

        }

        if (is_nomber() == 3)
        {
            if (matrix[1][1] >= 0)
            {
                result = 2;
            }
            else
            {
                result = 4;
            }
        }

        if (is_nomber() == 4)
        {
            if (matrix[1][1] >= 0)
            {
                result = 3;
            }
            else
            {
                result = 1;
            }
        }
    }
    else
    {
        if (is_nomber() == 2)
        {
            if (matrix[2][1] < 0)
            {
                result = 5;
            }
            else
            {
                result = 6;
            }
        }
        if (is_nomber() == 4)
        {
            if (matrix[2][1] < 0)
            {
                result = 6;
            }
            else
            {
                result = 5;
            }
        }
        if (is_nomber() == 5)
        {
            if (matrix[2][1] < 0)
            {
                result = 4;
            }
            else
            {
                result = 2;
            }
        }

        if (is_nomber() == 6)
        {
            if (matrix[2][1] < 0)
            {
                result = 2;
            }
            else
            {
                result = 4;
            }
        }
    }
    return result;

}


bool Cube::is_win()
{
    int score_win = 59079;
    for (int n = 1; n <= 6; n++)
    {
         Plane* p;
            switch (n)
            {
            case 1:
              p = logic -> Get_Plane_1();
                break;
            case 2:
                p = logic -> Get_Plane_2();
                break;
            case 3:
                p = logic -> Get_Plane_3();
                break;
           case 4:
                p = logic -> Get_Plane_4();
                break;
            case 5:
                p = logic -> Get_Plane_5();
                break;
            case 6:
                p = logic -> Get_Plane_6();
                break;
            default:
               break;
            }
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (p -> Get_Cell(i,j) -> Get_Value() == score_win)
                        {
                            show_plane(n);
                        }
                    }
                }
            }
    return logic -> Win();
}

bool Cube::is_lose()
{
     for (int n = 1; n <= 6; n++)
     {
          Plane* p;

             switch (n)
             {
             case 1:
               p = logic -> Get_Plane_1();
                 break;
             case 2:
                 p = logic -> Get_Plane_2();
                 break;
             case 3:
                 p = logic -> Get_Plane_3();
                 break;
            case 4:
                 p = logic -> Get_Plane_4();
                 break;
             case 5:
                 p = logic -> Get_Plane_5();
                 break;
             case 6:
                 p = logic -> Get_Plane_6();
                 break;
             default:
                break;
           }
             if (p -> Full())
             {
                 show_plane(n);
             }
     }
    return logic -> Lose();
}

Cube_ *Cube::get()
{
    return logic;
}

void Cube::rotate(GLfloat kx, GLfloat ky)
{
    if (matrix[1][1] != 0)
    {
        if (rotationZ != 0)
        {

            while(rotationZ != 0)
            {


                if (rotationZ > 0)
                {
                    rotationZ = floor(rotationZ+0.5);
                    rotationZ--;
                }
                if (rotationZ < 0)
                {
                    rotationZ = ceil(rotationZ-0.5);
                    rotationZ++;
                }
            }

        }
        else
        {
            rotationY += 180 * kx;
            rotationX += 180 * ky;
            rotationZ = 0;
        }
    }

    if (matrix[1][1] == 0)
    {
        if (rotationY != 0)
        {

            while(rotationY != 0)
            {
                if (rotationY > 0)
                {
                    rotationY = floor(rotationY+0.5);
                    rotationY--;
                }
                if (rotationY < 0)
                {
                    rotationY = ceil(rotationY-0.5);
                    rotationY++;
                }
            }
        }
        else
        {
            if (rotationX < 0)
            {
                kx = -kx;
            }
            rotationX += 180 * ky;
            rotationZ += 180 * -kx;
            rotationY = 0;
        }
    }

}

QString Cube::score()
{
    return QString::number(logic -> Get_Score());
}

void Cube::difficult_game (int dif)
{
    difficult = dif;
}

void Cube::right()
{
    logic->Shift(is_nomber(),is_nomber_right());

    int k = 0;
    while (k < difficult)
    {
        logic -> Rand_Set_Value();
        k++;
    }

    updateGL();
}

void Cube::left()
{
    logic->Shift(is_nomber(),is_nomber_left());

    int k = 0;
    while (k < difficult)
    {
        logic -> Rand_Set_Value();
        k++;
    }

    updateGL();
}

void Cube::up()
{
    logic->Shift(is_nomber(),is_nomber_up());

    int k = 0;
    while (k < difficult)
    {
        logic -> Rand_Set_Value();
        k++;
    }

    updateGL();
}

void Cube::down()
{
    logic->Shift(is_nomber(),is_nomber_down());

    int k = 0;
    while (k < difficult)
    {
        logic -> Rand_Set_Value();
        k++;
    }

    updateGL();
}

void Cube::fill_coord()
{
    const float cord = 0.979;
    GLfloat a [4][4][3];
    a[0][0][0] = -cord;
    a[0][1][0] = -cord;
    a[0][2][0] = -cord;
    a[0][3][0] = -cord;
    a[0][0][1] = cord;
    a[1][0][1] = cord;
    a[2][0][1] = cord;
    a[3][0][1] = cord;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            a[i][j][2] = 1.01;
            if (j != 0)
            {
                a[i][j][1] = a[i][j - 1][1] - 0.49;
            }
            if (i != 0)
            {
                a[i][j][0]=a[i - 1][j][0] + 0.49;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            quads_coord[i][j][0][0] = a[j][i][0];
            quads_coord[i][j][1][0] = a[j][i][1];
            quads_coord[i][j][2][0] = a[j][i][2];

            quads_coord[i][j][0][1] = -a[j][i][0];
            quads_coord[i][j][1][1] = a[j][i][1];
            quads_coord[i][j][2][1] = -a[j][i][2];

            quads_coord[i][j][0][2] = a[j][i][2];
            quads_coord[i][j][1][2] = a[j][i][1];
            quads_coord[i][j][2][2] = -a[j][i][0];

            quads_coord[i][j][0][3] = -a[j][i][2];
            quads_coord[i][j][1][3] = a[j][i][1];
            quads_coord[i][j][2][3] = a[j][i][0];

            quads_coord[i][j][0][4] = -a[j][i][0];
            quads_coord[i][j][1][4] = -a[j][i][2];
            quads_coord[i][j][2][4] = -a[j][i][1];

            quads_coord[i][j][0][5] = a[j][i][0];
            quads_coord[i][j][1][5] = a[j][i][2];
            quads_coord[i][j][2][5] = -a[j][i][1];

        }
    }

}

