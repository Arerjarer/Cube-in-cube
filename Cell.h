
#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Cell{
private:

    int Value;
    int X_Pos;
    int Y_Pos;

public:

    Cell();
    Cell(int y, int x);
    ~Cell();
    void Fusion(int &Temp_Score);
    void Erase();
    void Set_Value(int iVal);
    int Get_Value();

};

#endif
