#include "settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(320,400);

    QPalette plt (this -> palette());
    plt.setBrush(QPalette::Background,QImage(":/texture/Background.png"));
    this -> setPalette(plt);

    Height = 30;
    Wight = 296;
    difficult = 1;
    x = 0;
    y =15;

    back = new QPushButton ("Back");
    back -> setFont(QFont("System",16, QFont::Normal));
    back -> setFixedSize(Wight, Height);
    back -> setStyleSheet("QPushButton{border-image: url(:/texture/Button-1.png)}"
                          "QPushButton:hover{border-image: url(:/texture/Button-2.png)}");
    connect(back,SIGNAL(clicked()),this,SLOT(close_settings()));

    set = new QComboBox;
    set -> setFont(QFont("System",16, QFont::Normal));
    set -> addItem("Easy");
    set -> addItem("Normal");
    set -> addItem("Hard");
    set -> setFixedSize(Wight, Height);
    set -> setStyleSheet("QComboBox{border-image: url(:/texture/Button-1.png)}"
                         "QComboBox QAbstractItemView {background-color: #34A988}"
                         "QComboBox:down-arrow {image: url(:/texture/str.png)}");

    QVBoxLayout* layout = new QVBoxLayout();
    layout -> addWidget(back);
    layout -> addWidget(set);
    setLayout(layout);
}



void Settings::close_settings()
{
    if (set->currentText() == "Easy")
    {
        difficult = 1;
    }

    if (set->currentText() == "Normal")
    {
        difficult = 2;
    }

    if (set->currentText() == "Hard")
    {
        difficult = 3;
    }

    Window* menu = new Window;
    menu -> SetDifficult(difficult);
    this -> close();
    menu -> show();
}
