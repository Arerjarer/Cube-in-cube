
#include "Cube.h"

Cube_::Cube_(){

    Plane_1 = new Plane();
    Plane_2 = new Plane();
    Plane_3 = new Plane();
    Plane_4 = new Plane();
    Plane_5 = new Plane();
    Plane_6 = new Plane();
    Score = 0;
}

Cube_::~Cube_(){
    delete Plane_1;
    delete Plane_2;
    delete Plane_3;
    delete Plane_4;
    delete Plane_5;
    delete Plane_6;
}

void Cube_::Print(){
    Plane_1->Print();
    Plane_2->Print();
    Plane_3->Print();
    Plane_4->Print();
    Plane_5->Print();
    Plane_6->Print();
}

void Cube_::Set_Score(int Score_){
    Score = Score_;
}

int Cube_::Get_Score(){
    return Score;
}

Plane* Cube_::Get_Plane_1(){
    return Plane_1;
}

Plane* Cube_::Get_Plane_2(){
    return Plane_2;
}

Plane* Cube_::Get_Plane_3(){
    return Plane_3;
}

Plane* Cube_::Get_Plane_4(){
    return Plane_4;
}

Plane* Cube_::Get_Plane_5(){
    return Plane_5;
}

Plane* Cube_::Get_Plane_6(){
    return Plane_6;
}

void Cube_::Rand_Set_Value(){

    srand(time(NULL));

    int i = (rand() + 1) % 7;

    switch (i){
    case 1:
        Plane_1->Rand_Set_Value();
        return;
    case 2:
        Plane_2->Rand_Set_Value();
        return;
    case 3:
        Plane_3->Rand_Set_Value();
        return;
    case 4:
        Plane_4->Rand_Set_Value();
        return;
    case 5:
        Plane_5->Rand_Set_Value();
        return;
    case 6:
        Plane_6->Rand_Set_Value();
        return;
    }
}

void Cube_::Shift(int From, int To){

    if(From == 1){
        if(To == 2){
            Shift_12();
        }

        if(To == 5){
            Shift_15();
        }

        if(To == 4){
            Shift_21();
        }

        if(To == 6){
            Shift_51();
        }
    }

    if(From == 2){
        if(To == 3){
            Shift_12();
        }

        if(To == 5){
            Shift_25();
        }

        if(To == 1){
            Shift_21();
        }

        if(To == 6){
            Shift_52();
        }
    }

    if(From == 3){
        if(To == 4){
            Shift_12();
        }

        if(To == 5){
            Shift_51();
        }

        if(To == 2){
            Shift_21();
        }

        if(To == 6){
            Shift_15();
        }
    }

    if(From == 4){
        if(To == 1){
            Shift_12();
        }

        if(To == 5){
            Shift_52();
        }

        if(To == 3){
            Shift_21();
        }

        if(To == 6){
            Shift_25();
        }
    }

    if(From == 5){
        if(To == 1){
            Shift_51();
        }

        if(To == 2){
            Shift_52();
        }

        if(To == 3){
            Shift_15();
        }

        if(To == 4){
            Shift_25();
        }
    }

    if(From == 6){
        if(To == 1){
            Shift_15();
        }

        if(To == 2){
            Shift_25();
        }

        if(To == 3){
            Shift_51();
        }

        if(To == 4){
            Shift_52();
        }
    }

}

void Cube_::Shift_12(){

    int Temp_Score = 0;
    int* Temp1 = new int[4];
    int* Temp2 = new int[4];
    int* Temp3 = new int[4];
    int* Temp4 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись левых столбцов плоскостей

    for(int i = 0; i < 4; i++){
        Temp1[i] = Plane_1->Get_Cell(i, 0)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp2[i] = Plane_2->Get_Cell(i, 0)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp3[i] = Plane_3->Get_Cell(i, 0)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp4[i] = Plane_4->Get_Cell(i, 0)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_1->Shift_Right(Temp2, Temp_Score); // в rTemp1 поместили правый столбец первой плоскости
    rTemp2 = Plane_2->Shift_Right(Temp3, Temp_Score); // в rTemp2 поместили правый столбец второй плоскости

    for(int i = 0; i < 4; i++){				// Запись левого столбца второй плоскости

        if(rTemp1[i])
            Plane_2->Get_Cell(i, 0)->Set_Value(rTemp1[i]);
    }

    rTemp1 = Plane_3->Shift_Right(Temp4, Temp_Score); // в rTemp1 поместили правый столбец третьей плоскости

    for(int i = 0; i < 4; i++){				// Запись левого столбца третьей плоскости

        if(rTemp2[i])
            Plane_3->Get_Cell(i, 0)->Set_Value(rTemp2[i]);
    }

    rTemp2 = Plane_4->Shift_Right(Temp1, Temp_Score); // в rTemp2 поместили правый столбец четвертой плоскости

    for(int i = 0; i < 4; i++){				// Запись левого столбца третьей плоскости

        if(rTemp1[i])
            Plane_4->Get_Cell(i, 0)->Set_Value(rTemp1[i]);
    }

    for(int i = 0; i < 4; i++){				// Запись левого столбца третьей плоскости

        if(rTemp2[i])
            Plane_1->Get_Cell(i, 0)->Set_Value(rTemp2[i]);
    }

    Set_Score(Score + Temp_Score);
}

void Cube_::Shift_21(){

    int Temp_Score = 0;
    int* Temp1 = new int[4];
    int* Temp2 = new int[4];
    int* Temp3 = new int[4];
    int* Temp4 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись правых столбцов плоскостей

    for(int i = 0; i < 4; i++){
        Temp1[i] = Plane_1->Get_Cell(i, 3)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp2[i] = Plane_2->Get_Cell(i, 3)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp3[i] = Plane_3->Get_Cell(i, 3)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp4[i] = Plane_4->Get_Cell(i, 3)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_1->Shift_Left(Temp4, Temp_Score); // в rTemp1 поместили левый столбец первой плоскости
    rTemp2 = Plane_4->Shift_Left(Temp3, Temp_Score); // в rTemp2 поместили левый столбец второй плоскости

    for(int i = 0; i < 4; i++){				// Запись правого столбца четвертой плоскости

        if(rTemp1[i])
            Plane_4->Get_Cell(i, 3)->Set_Value(rTemp1[i]);
    }

    rTemp1 = Plane_3->Shift_Left(Temp2, Temp_Score); // в rTemp1 поместили левый столбец третьей плоскости

    for(int i = 0; i < 4; i++){				// Запись правого столбца третьей плоскости

        if(rTemp2[i])
            Plane_3->Get_Cell(i, 3)->Set_Value(rTemp2[i]);
    }

    rTemp2 = Plane_2->Shift_Left(Temp1, Temp_Score); // в rTemp2 поместили левый столбец четвертой плоскости

    for(int i = 0; i < 4; i++){				// Запись правого столбца третьей плоскости

        if(rTemp1[i])
            Plane_2->Get_Cell(i, 3)->Set_Value(rTemp1[i]);
    }

    for(int i = 0; i < 4; i++){				// Запись правого столбца третьей плоскости

        if(rTemp2[i])
            Plane_1->Get_Cell(i, 3)->Set_Value(rTemp2[i]);
    }
    Set_Score(Score + Temp_Score);
}

void Cube_::Shift_15(){

    int Temp_Score = 0;
    int* Temp1 = new int[4];
    int* Temp5 = new int[4];
    int* Temp3 = new int[4];
    int* Temp6 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись нижние ряды плоскостей

    for(int i = 0; i < 4; i++){
        Temp1[i] = Plane_1->Get_Cell(3, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp5[i] = Plane_5->Get_Cell(3, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp3[i] = Plane_3->Get_Cell(0, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp6[i] = Plane_6->Get_Cell(3, i)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_1->Shift_Up(Temp5, Temp_Score); // в rTemp1 поместили верхний ряд первой плоскости
    rTemp2 = Plane_5->Shift_Up(Temp3, Temp_Score); // в rTemp2 поместили верхний ряд пятой плоскости

    for(int i = 0; i < 4; i++){				// Запись нижнего ряда пятой плоскости

        if(rTemp1[i])
            Plane_5->Get_Cell(3, i)->Set_Value(rTemp1[i]);
    }

    rTemp1 = Plane_3->Shift_Down(Temp6, Temp_Score); // в rTemp1 поместили нижний ряд третьей плоскости

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда третьей плоскости

        if(rTemp2[3 - i])
            Plane_3->Get_Cell(0, i)->Set_Value(rTemp2[3 - i]);
    }

    rTemp2 = Plane_6->Shift_Up(Temp1, Temp_Score); // в rTemp2 поместили верхний ряд шестой плоскости

    for(int i = 0; i < 4; i++){				// Запись нижнего ряда шестой плоскости

        if(rTemp1[3 - i])
            Plane_6->Get_Cell(3, i)->Set_Value(rTemp1[3 - i]);
    }

    for(int i = 0; i < 4; i++){				// Запись нижнего ряда первой плоскости

        if(rTemp2[i])
            Plane_1->Get_Cell(3, i)->Set_Value(rTemp2[i]);
    }
    Set_Score(Score + Temp_Score);
}

void Cube_::Shift_51(){

    int Temp_Score = 0;
    int* Temp1 = new int[4];
    int* Temp5 = new int[4];
    int* Temp3 = new int[4];
    int* Temp6 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись верхних рядов плоскостей

    for(int i = 0; i < 4; i++){
        Temp1[i] = Plane_1->Get_Cell(0, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp5[i] = Plane_5->Get_Cell(0, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp3[i] = Plane_3->Get_Cell(3, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp6[i] = Plane_6->Get_Cell(0, i)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_1->Shift_Down(Temp6, Temp_Score); // в rTemp1 поместили нижний ряд первой плоскости
    rTemp2 = Plane_6->Shift_Down(Temp3, Temp_Score); // в rTemp2 поместили нижний ряд шестой плоскости

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда шестой плоскости

        if(rTemp1[i])
            Plane_6->Get_Cell(0, i)->Set_Value(rTemp1[i]);
    }

    rTemp1 = Plane_3->Shift_Up(Temp5, Temp_Score); // в rTemp1 поместили нижний ряд третьей плоскости

    for(int i = 0; i < 4; i++){				// Запись нижнего ряда третьей плоскости

        if(rTemp2[3 - i])
            Plane_3->Get_Cell(3, i)->Set_Value(rTemp2[3 - i]);
    }

    rTemp2 = Plane_5->Shift_Down(Temp1, Temp_Score); // в rTemp2 поместили нижний ряд пятой плоскости

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда пятой плоскости

        if(rTemp1[3 - i])
            Plane_5->Get_Cell(0, i)->Set_Value(rTemp1[3 - i]);
    }

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда первой плоскости

        if(rTemp2[i])
            Plane_1->Get_Cell(0, i)->Set_Value(rTemp2[i]);
    }
    Set_Score(Score + Temp_Score);
}

void Cube_::Shift_25(){

    int Temp_Score = 0;
    int* Temp2 = new int[4];
    int* Temp5 = new int[4];
    int* Temp4 = new int[4];
    int* Temp6 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись верхних рядов плоскостей

    for(int i = 0; i < 4; i++){
        Temp2[i] = Plane_2->Get_Cell(3, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp5[i] = Plane_5->Get_Cell(i, 3)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp4[i] = Plane_4->Get_Cell(0, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp6[i] = Plane_6->Get_Cell(i, 0)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_2->Shift_Up(Temp5, Temp_Score); // в rTemp1 поместили верхний ряд второй плоскости
    rTemp2 = Plane_5->Shift_Left(Temp4, Temp_Score); // в rTemp2 поместили левый столбец пятой плоскости

    for(int i = 0; i < 4; i++){				// Запись правого столбца пятой плоскости

        if(rTemp1[3 - i])
            Plane_5->Get_Cell(i, 3)->Set_Value(rTemp1[3 - i]);
    }

    rTemp1 = Plane_4->Shift_Down(Temp6, Temp_Score); // в rTemp1 поместили нижний ряд четвертой плоскости

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда четвертой плоскости

        if(rTemp2[i])
            Plane_4->Get_Cell(0, i)->Set_Value(rTemp2[i]);
    }

    rTemp2 = Plane_6->Shift_Right(Temp2, Temp_Score); // в rTemp2 поместили левый столбец шестой плоскости

    for(int i = 0; i < 4; i++){				// Запись левого столбца шестой плоскости

        if(rTemp1[3 - i])
            Plane_6->Get_Cell(i, 0)->Set_Value(rTemp1[3 - i]);
    }

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда первой плоскости

        if(rTemp2[i])
            Plane_2->Get_Cell(3, i)->Set_Value(rTemp2[i]);
    }
    Set_Score(Score + Temp_Score);
}

void Cube_::Shift_52(){

    int Temp_Score = 0;
    int* Temp2 = new int[4];
    int* Temp5 = new int[4];
    int* Temp4 = new int[4];
    int* Temp6 = new int[4];
    int* rTemp1 = new int[4];
    int* rTemp2 = new int[4];

    // Запись верхних рядов плоскостей

    for(int i = 0; i < 4; i++){
        Temp2[i] = Plane_2->Get_Cell(0, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp5[i] = Plane_5->Get_Cell(i, 0)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp4[i] = Plane_4->Get_Cell(3, i)->Get_Value();
    }

    for(int i = 0; i < 4; i++){
        Temp6[i] = Plane_6->Get_Cell(i, 3)->Get_Value();
    }

    // Начнем сдвиги

    rTemp1 = Plane_5->Shift_Right(Temp2, Temp_Score); // в rTemp1 поместили правый столбец пятой плоскости
    rTemp2 = Plane_2->Shift_Down(Temp6, Temp_Score); // в rTemp2 поместили нижний ряд второй плоскости

    for(int i = 0; i < 4; i++){				// Запись верхнего ряда второй плоскости

        if(rTemp1[3 - i])
            Plane_2->Get_Cell(0, i)->Set_Value(rTemp1[3 - i]);
    }

    rTemp1 = Plane_6->Shift_Left(Temp4, Temp_Score); // в rTemp1 поместили левый столбец шестой плоскости

    for(int i = 0; i < 4; i++){				// Запись правого столбца шестой плоскости

        if(rTemp2[i])
            Plane_6->Get_Cell(i, 3)->Set_Value(rTemp2[i]);
    }

    rTemp2 = Plane_4->Shift_Up(Temp2, Temp_Score); // в rTemp2 поместили верхний ряд четвертой плоскости

    for(int i = 0; i < 4; i++){				// Запись нижнего ряда четвертой плоскости

        if(rTemp1[3 - i])
            Plane_4->Get_Cell(3, i)->Set_Value(rTemp1[3 - i]);
    }

    for(int i = 0; i < 4; i++){				// Запись левого столбца пятой плоскости

        if(rTemp2[i])
            Plane_5->Get_Cell(i, 0)->Set_Value(rTemp2[i]);
    }
    Set_Score(Score + Temp_Score);
}

bool Cube_::Lose(){

    if(Plane_1->Full() || Plane_2->Full() || Plane_3->Full() || Plane_4->Full() || Plane_5->Full() || Plane_6->Full())
        return 1;
    else
        return 0;
}

bool Cube_::Win(){
    int score_win = 59079;
         for (int i = 0; i < 4; i++)
         {
             for (int j = 0; j < 4; j++)
             {
                 if  ((Plane_1 -> Get_Cell(i,j) -> Get_Value() >= score_win)||
                      (Plane_2 -> Get_Cell(i,j) -> Get_Value() >= score_win)||
                      (Plane_3 -> Get_Cell(i,j) -> Get_Value() >= score_win)||
                      (Plane_4 -> Get_Cell(i,j) -> Get_Value() >= score_win)||
                      (Plane_5 -> Get_Cell(i,j) -> Get_Value() >= score_win)||
                      (Plane_6 -> Get_Cell(i,j) -> Get_Value() >= score_win))
                     return true;

             }
         }
         return false;
}
