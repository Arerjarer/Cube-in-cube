
#include "Cell.h"

Cell::Cell(){
    Value = 0;
    X_Pos = NULL;
    Y_Pos = NULL;
}

Cell::Cell(int y, int x){
    Value = 0;
    X_Pos = x;
    Y_Pos = y;
}

Cell::~Cell(){
    Value = 0;
    X_Pos = NULL;
    Y_Pos = NULL;
}

void Cell::Fusion(int &Temp_Score){
    Temp_Score += Value;
    Value *= 3;
}

void Cell::Erase(){
    Value = 0;
}

void Cell::Set_Value(int iVal){
    Value = iVal;
}

int Cell::Get_Value(){
    return Value;
}
