#include "game.h"

Game::Game(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize (475,700);

    s = " SCORE: 0 ";
    score_show = new QLabel (s);
    score_show -> setMaximumHeight(40);
    score_show -> setAlignment(Qt::AlignRight);
    file = new QFile ("D:/Maftrek/177147_Cube/Ternary_Cubic/texture/score.txt");
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream out(file);
    score_prev = QString(file->readAll());
    file->close();
    s1 = " record : ";
    s1.push_back(score_prev);
    record_show = new QLabel (s1);
    record_show -> setMaximumHeight(30);
    record_show->setAlignment(Qt::AlignRight);

    number_show = new QLabel ();
    number_show -> setMaximumHeight(60);
    number_show -> setMaximumWidth(160);
    number_show -> setAlignment(Qt::AlignLeft);
    number_show -> setStyleSheet("QLabel {"
                                 "border-style: solid;"
                                 "border-width: 1px;"
                                 "border-color: black;"
                                 "}");

    score_show -> setFont(QFont("System",35, QFont::Normal));

    number_show -> setFont(QFont("System",33, QFont::Normal));

    record_show -> setFont(QFont("System",18, QFont::Normal));

    QPalette palette (this -> palette());

    palette.setColor(QPalette::WindowText,QColor (Qt::darkBlue));
    score_show -> setPalette(palette);

    palette.setBrush(QPalette::Background, QImage(":/texture/wood.jpg"));
    this->setPalette(palette);

    cube = new Cube;
    p = new Map (cube);

    right = new QPushButton ("right");
    right -> setFont(QFont("System",16, QFont::Normal));
    right -> setFixedSize(455, 25);
    right -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                           "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(right,SIGNAL(clicked()),this,SLOT(move_right()));

    left = new QPushButton ("left");
    left -> setFont(QFont("System",16, QFont::Normal));
    left -> setFixedSize(455, 25);
    left -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                          "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(left,SIGNAL(clicked()),this,SLOT(move_left()));

    up = new QPushButton ("up");
    up -> setFont(QFont("System",16, QFont::Normal));
    up -> setFixedSize(455, 25);
    up -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                        "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(up,SIGNAL(clicked()),this,SLOT(move_up()));

    down  = new QPushButton ("down");
    down -> setFont(QFont("System",16, QFont::Normal));
    down -> setFixedSize(455, 25);
    down -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                          "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(down,SIGNAL(clicked()),this,SLOT(move_down()));

    QVBoxLayout* vert = new QVBoxLayout();
    vert -> addWidget(score_show);
    vert -> addWidget(record_show);

    QHBoxLayout* horizont = new QHBoxLayout();
    horizont -> addWidget(number_show);
    horizont -> addLayout(vert);

    QVBoxLayout* layout = new QVBoxLayout();
    layout -> addLayout(horizont);
    layout -> addWidget(p);
    layout -> addWidget(cube);
    layout -> addWidget(right);
    layout -> addWidget(left);
    layout -> addWidget(up);
    layout -> addWidget(down);

    setLayout(layout);

    startTimer(0);
}

Game::~Game()
{
    delete cube;
}

void Game::move_right()
{
    cube -> right();
    score();
    check();
}

void Game::move_left()
{
    cube -> left();
    score();
    check();
}

void Game::move_up()
{
    cube -> up();
    score();
    check();
}

void Game::move_down()
{
    cube -> down();
    score();
    check();
}

void Game::score()
{
    s.clear();
    s.push_back(" SCORE: ");
    s.push_back(cube -> score());
    s.push_back(" ");
    score_show -> setText(s);
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream out(file);
    if (score_prev.toInt() != (QString(file->readAll())).toInt())
    {
        s1.clear();
        score_prev = QString(file->readAll());

        s1 = " record : ";
        s1.push_back(score_prev);
        record_show->setText(s1);
    }
    file->close();
    if (score_prev.toInt()<cube->score().toInt())
    {
        file->open(QIODevice::WriteOnly|QIODevice::Text);
        out << cube->score();
        s1.clear();
        s1 = " record : ";
        s1.push_back(cube->score());
        file->close();
        QColor c = QColor ("#DA1520");
        record_show->setStyleSheet(QString("color: %1").arg(c.name()));
        record_show->setText(s1);
    }
}

void Game::check()
{
    if (cube->is_win())
    {
        game_over(1);
    }
    if (cube->is_lose())
    {
        game_over(0);
    }
}

void Game::game_over(bool wl)
{
    this->close();
    int record = 0;
    if (cube->score().toInt() > score_prev.toInt())
    {
        record = cube->score().toInt();
    }
    Finish* f = new Finish (cube,wl,record);
    f->show();
}

void Game::set_difficult(int difficult)
{
    cube -> difficult_game(difficult);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_6)
    {
        cube -> right();
        score();
        score_show -> setText(s);
    }

    if (event->key() == Qt::Key_4)
    {
        cube -> left();
        score();
        score_show -> setText(s);
    }

    if (event->key() == Qt::Key_8)
    {
        cube -> up();
        score();
        score_show -> setText(s);
    }

    if (event->key() == Qt::Key_2)
    {
        cube -> down();
        score();
        score_show -> setText(s);
    }
}

void Game::timerEvent(QTimerEvent *)
{
    QString str = "Plane ";
    str.push_back(QString::number(cube -> is_nomber()));
    number_show -> setText(str);
}
