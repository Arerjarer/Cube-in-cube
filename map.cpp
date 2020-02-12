#include "map.h"

Map::Map(Cube* cube) :
    QWidget()
{
    setFixedSize(470,90);

    x = 0;
    y = 16;
    log = cube;
    p = new QPushButton* [6];
    QHBoxLayout* layout = new QHBoxLayout;
    for (int k = 0; k < 6; k++)
    {
        p[k] = new QPushButton;
        p[k]  -> setFixedSize(65, 80);
        p[k] -> setFlat(1);
        p[k] -> setStyleSheet("QPushButton:hover{background-color: none; border: none;}");
        connect(p[k],SIGNAL(clicked()),this,SLOT(slot()));
        layout -> addWidget(p[k]);
    }

    setLayout(layout);
    startTimer(0);
}

void Map::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int X = 5;
    for (int k = 1; k <= 6; k++)
    {
        draw(p,k,X);
        X+=75;
    }
}

void Map::timerEvent(QTimerEvent *)
{
    update();
}

void Map::draw(QPainter &p, int num,int X)
{
    Plane* plane = NULL;
    QFont font;
    font.setPointSize(15);
    p.setFont(font);
    QPen pen(Qt::black);
    p.setPen(pen);
    QString name_plane = "Plane ";
    name_plane.push_back(QString::number(num));
    p.drawText(X,15,name_plane);
    p.setBrush(QColor(255, 255, 153));
    p.drawRect(X,y,70,70);
    switch (num){
    case 1:
        plane = log->get()->Get_Plane_1();
        break;
    case 2:
        plane = log->get()->Get_Plane_2();
        break;
    case 3:
        plane = log->get()->Get_Plane_3();
        break;
    case 4:
        plane = log->get()->Get_Plane_4();
        break;
    case 5:
        plane = log->get()->Get_Plane_5();
        break;
    case 6:
        plane = log->get()->Get_Plane_6();
        break;
    }
    x = X;
    int x_ = x;

    QString s;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            s.push_back(":/texture/");
            s.push_back(get_texture(plane->Get_Cell(i,j)->Get_Value()));
            s.push_back(".jpg");
            p.setBrush(QPixmap(s));
            p.drawRect(x,y,16,16);
            QFont f;
            f.setPointSize(10);
            p.setFont(f);
            int n = plane->Get_Cell(i,j)->Get_Value();
            if (n != 0)
            {
                p.drawText(x,y,16,16,Qt::AlignCenter,QString::number(n));
            }
            s.clear();
            x+=18;
        }
        x = x_;
        y += 18;
    }
    y = 16;
}

QString Map::get_texture(int value)
{
    switch (value) {
    case 0:
        return QString::number(0);
        break;
    case 3:
        return QString::number(1);
        break;
    case 9:
        return QString::number(2);
        break;
    case 27:
        return QString::number(3);
        break;
    case 81:
        return QString::number(4);
        break;
    case 243:
        return QString::number(5);
        break;
    case 729:
        return QString::number(6);
        break;
    case 2187:
        return QString::number(7);
        break;
    case 6561:
        return QString::number(8);
        break;
    case 19683:
        return QString::number(9);
        break;
    case 59049:
        return QString::number(10);
        break;
    default:
        break;
    }
    return QString::number(0);
}
void Map::slot()
{
    QPushButton* sen= ((QPushButton*)sender());
    if (sen==p[0])
    {
        log->show_plane(1);
    }
    if (sen==p[1])
    {
        log->show_plane(2);
    }
    if (sen==p[2])
    {
        log->show_plane(3);
    }
    if (sen==p[3])
    {
        log->show_plane(4);
    }
    if (sen==p[4])
    {
        log->show_plane(5);
    }
    if (sen==p[5])
    {
        log->show_plane(6);
    }
}
