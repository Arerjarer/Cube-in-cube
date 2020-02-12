
#ifndef PLANE_H
#define PLANE_H

#include "Cell.h"

class Plane{
private:

    Cell Cells[4][4];

public:

    Plane();
    ~Plane();

    void Print();

    Cell* Get_Cell(int y, int x);

    void Rand_Set_Value();
    int* Shift_Up(int *Column, int &Temp_Score);
    int* Shift_Down(int *Column, int &Temp_Score);
    int* Shift_Right(int *Column, int &Temp_Score);
    int* Shift_Left(int *Column, int &Temp_Score);

    int Full();
};

#endif
