
#ifndef CUBE_H
#define CUBE_H

#include "Plane.h"

class Cube_{
private:

    Plane* Plane_1;
    Plane* Plane_2;
    Plane* Plane_3;
    Plane* Plane_4;
    Plane* Plane_5;
    Plane* Plane_6;
    int Score;
    void Shift_12();
    void Shift_21();
    void Shift_15();
    void Shift_51();
    void Shift_25();
    void Shift_52();

public:

    Cube_();
    ~Cube_();

    void Print();
    void Set_Score(int Score_);
    int Get_Score();

    Plane* Get_Plane_1();
    Plane* Get_Plane_2();
    Plane* Get_Plane_3();
    Plane* Get_Plane_4();
    Plane* Get_Plane_5();
    Plane* Get_Plane_6();

    void Rand_Set_Value();

    void Shift(int From, int To);

    bool Lose();
    bool Win();
};

#endif

/*

Получение значения клетки плоскости № n с координатами y, x

Cube_->Get_Plane_n()->Get_Cell(y, x)->Get_Value();

Сдвиг в сторону Direction от плоскости № n

Cube_->Shift_Direction(n);

Создание случайного числа в случайном месте

Cube_->Rand_Set_Value();

Получение значения счета

Cube_->GetScore();

*/
