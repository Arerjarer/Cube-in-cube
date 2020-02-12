#ifndef SETTINGS_H
#define SETTINGS_H

#include "window.h"
#include <QComboBox>

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings(QWidget *parent = 0);

private:
    int Height;
    int Wight;
    QPushButton* back;
    QComboBox* set;
    int x;
    int y;
    int difficult;

private slots:
    void close_settings();

};

#endif // SETTINGS_H
