#include "window.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{    
    setFixedSize(320,400);

    QPalette plt (this -> palette());
    plt.setBrush(QPalette::Background, QImage(":/texture/Background.png"));
    this -> setPalette(plt);

    difficult = 1;
    Height = 30;
    Wight = 296;
    x = 100;
    y = 65;

    start = new QPushButton ("Start");
    start -> setFont(QFont("System",16, QFont::Normal));
    start -> setFixedSize(Wight, Height);
    start -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                         "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(start,SIGNAL(clicked()),this,SLOT(starts()));
    start -> setFlat(1);
    setting = new QPushButton ("Setting");
    setting -> setFont(QFont("System",16, QFont::Normal));
    setting -> setFixedSize(Wight, Height);
    setting -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                           "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(setting,SIGNAL(clicked()),this,SLOT(settings_func()));

    exit = new QPushButton ("Exit");
    exit -> setFont(QFont("System",16, QFont::Normal));
    exit -> setFixedSize(Wight, Height);
    exit -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                        "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout* layout = new QVBoxLayout();
    layout -> addWidget(start);
    layout -> addWidget(setting);
    layout -> addWidget(exit);
    setLayout(layout);
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    draw_text(p);
}

void Window::SetDifficult(int dif)
{
    difficult = dif;
}

void Window::draw_text(QPainter &p)
{
    QString s = "Cube";
    QPen pen(QColor("#0A817B"));
    p.setPen(pen);

    p.setFont(QFont("System",37, QFont::Normal));
    p.drawText(x, y, s);

    p.setFont(QFont("System",27, QFont::Normal));
    p.drawText(x + 120, y - 25, "3");
}

void Window::starts()
{
    Game* game = new Game;
    this -> close();
    game -> set_difficult(difficult);
    game -> show();

}

void Window::settings_func()
{
    Settings* d = new Settings;
    this -> close();
    d -> show();
}
