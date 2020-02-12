#include "finish.h"

Finish::Finish(Cube* cube, bool wl, int record) :
    QWidget()
{
    setFixedSize (320,400);

    if (wl)
    {
        text = "You Win";
    }
    else
    {
        text = "You Lose";
    }

    cubic = cube;
    cubic->setMaximumSize(320,250);

    l1 = new QLabel (text);
    l1->setMaximumSize(320,30);
    l1 -> setFont(QFont("System",35, QFont::Normal));
    l1->setAlignment(Qt::AlignCenter);
    QColor color = QColor ("#0A817B");
    l1->setStyleSheet(QString("color: %1").arg(color.name()));

    new_game = new QPushButton("New Game");
    connect(new_game,SIGNAL(clicked()),this,SLOT(new_games()));
    new_game->setFixedSize(300, 30);
    new_game->setFont(QFont("System",16, QFont::Normal));
    new_game->setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                            "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");

    exit = new QPushButton("Exit");
    connect(exit ,SIGNAL(clicked()),this,SLOT(close()));
    exit->setFixedSize(300, 30);
    exit->setFont(QFont("System",16, QFont::Normal));
    exit->setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                        "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");

    QPalette palette (this -> palette());
    palette.setBrush(QPalette::Background, QImage(":/texture/Background.png"));
    this->setPalette(palette);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(l1);

    if (record != 0)
    {
        QString rec = "New Record - ";
        rec.push_back(QString::number(record));
        rec.push_back("!!!");
        QLabel* r = new QLabel (rec);
        r->setAlignment(Qt::AlignCenter);
        r->setMaximumSize(320,30);
        r->setFont(QFont("System",20,QFont::Normal));
        QColor c = QColor ("#0A517B");
        r->setStyleSheet(QString("color: %1").arg(c.name()));
        layout->addWidget(r);
    }

    layout->addWidget(new_game);
    layout->addWidget(exit);
    layout->addWidget(cubic);

    setLayout(layout);
}

void Finish::new_games()
{
    Window* window = new Window;
    this -> close();
    window -> show();
}
