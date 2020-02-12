
#include "Plane.h"

#define ThisValue  Cells[y][x].Get_Value()
#define RightValue Cells[y][x + 1].Get_Value()
#define LeftValue  Cells[y][x - 1].Get_Value()
#define UpperValue Cells[y - 1][x].Get_Value()
#define LowerValue Cells[y + 1][x].Get_Value()

#define chance 5

Plane::Plane(){

    for (int i = 0; i < 4; i++){

        for (int k = 0; k < 4; k++){

            Cell Temp(i, k);
            Cells[i][k] = Temp;
        }
    }
}

Plane::~Plane(){}

void Plane::Print(){
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){

            printf("%d ", Cells[y][x].Get_Value());
        }
        printf("\n");
    }

    printf("\n");
}

void Plane::Rand_Set_Value(){
    srand(time(NULL));

    while (1){
        int i = rand() % 4;
        int k = rand() % 4;

        if (Cells[i][k].Get_Value() == 0){

            int Temp = rand() % chance;

            if(Temp < chance - 1)
                Cells[i][k].Set_Value(3);
            else
                Cells[i][k].Set_Value(9);

            break;
        }
    }
}

int* Plane::Shift_Right(int *Column, int &Temp_Score){

    int* Array = new int[4];

    Array[0] = 0;
    Array[1] = 0;
    Array[2] = 0;
    Array[3] = 0;

    for (int y = 0; y < 4; y++){

        int Temp;

        if(Cells[y][3].Get_Value()){			// Оцениваем, нужно ли давать значение в другую плоскость
            Temp = Cells[y][3].Get_Value();

            for(int x = 2; x >= 0; x--){		// Оцениваем, что слева от самой правой в ряду

                if(!Cells[y][x].Get_Value()){	// Ищем непустую клетку
                    if(x)
                    continue;
                }

                if(Cells[y][x].Get_Value() == Temp)	// Если значение непустой клетки совпадает, будем сливать
                    break;

                if(!Column[y]){// Проверка на пустоту первой ячейки соседней плоскости

                    Cells[y][3].Erase();

                    Array[y] = Temp;
                }
            }
        }

        Temp = 0;

        int Max = 3;

        for (int x = 3; x >= 0; x--){			// Начало сдвига со слиянием

            if (x == Max){						// Если мы в самой правой клетке
                Temp = ThisValue;
                continue;
            }

            if (ThisValue == 0)					// Если в этой клетке нет значения
                continue;

            if (ThisValue == RightValue){		// Если значения этой и правой клеток равны
                Cells[y][x].Erase();
                Cells[y][x + 1].Fusion(Temp_Score);

                Max--;							// Чтобы больше не проводилось сравнений с этой клеткой

                Temp = RightValue;

                continue;
            }

            if (RightValue == 0){				// Если справа пусто

                Cells[y][x + 1].Set_Value(ThisValue);
                Cells[y][x].Erase();
                x += 2;

                continue;
            }

            if (RightValue != ThisValue){		// Если справа другое значение
                Temp = ThisValue;

                continue;
            }
        }
    }

    return Array;
}

int* Plane::Shift_Left(int* Column, int &Temp_Score){

    int* Array = new int[4];

    Array[0] = 0;
    Array[1] = 0;
    Array[2] = 0;
    Array[3] = 0;

    for (int y = 0; y < 4; y++){

        int Temp;

        if(Cells[y][0].Get_Value()){			// Оцениваем, нужно ли давать значение в другую плоскость
            Temp = Cells[y][0].Get_Value();

            for(int x = 1; x < 4; x++){		// Оцениваем, что справа от самой левой в ряду

                if(!Cells[y][x].Get_Value()){	// Ищем непустую клетку
                    if(x < 3)
                    continue;
                }

                if(Cells[y][x].Get_Value() == Temp)	// Если значение непустой клетки совпадает, будем сливать
                    break;
                if(!Column[y]){	// Проверка на пустоту первой ячейки соседней плоскости

                    Cells[y][0].Erase();

                    Array[y] = Temp;
                }
            }
        }

        Temp = 0;

        int Min = 0;

        for (int x = 0; x < 4; x++){

            if (x == Min){						// Если мы в самой левой клетке
                Temp = ThisValue;
                continue;
            }

            if (ThisValue == 0)					// Если в этой клетке нет значения
                continue;

            if (ThisValue == LeftValue){		// Если значения этой и левой клеток равны
                Cells[y][x].Erase();
                Cells[y][x - 1].Fusion(Temp_Score);

                Temp = LeftValue;

                Min++;

                continue;
            }

            if (LeftValue == 0){				// Если слева пусто
                Cells[y][x - 1].Set_Value(ThisValue);
                Cells[y][x].Erase();
                x -= 2;

                continue;
            }

            if (LeftValue != ThisValue){		// Если слева другое значение
                Temp = ThisValue;

                continue;
            }
        }
    }

    return Array;
}

int* Plane::Shift_Up(int* Column, int &Temp_Score){

    int* Array = new int[4];

    Array[0] = 0;
    Array[1] = 0;
    Array[2] = 0;
    Array[3] = 0;

    for (int x = 0; x < 4; x++){

        int Temp;

        if(Cells[0][x].Get_Value()){			// Оцениваем, нужно ли давать значение в другую плоскость
            Temp = Cells[0][x].Get_Value();

            for(int y = 1; y < 4; y++){		// Оцениваем, что снизу от самой верхней в ряду

                if(!Cells[y][x].Get_Value()){	// Ищем непустую клетку
                    if(y < 3)
                    continue;
                }

                if(Cells[y][x].Get_Value() == Temp)	// Если значение непустой клетки совпадает, будем сливать
                    break;

                if(!Column[x]){	// Проверка на пустоту первой ячейки соседней плоскости

                    Cells[0][x].Erase();

                    Array[x] = Temp;
                }
            }
        }

        Temp = 0;

        int Min = 0;

        for (int y = 0; y < 4; y++){

            if (y == Min){						// Если мы в самой верхней клетке
                Temp = ThisValue;
                continue;
            }

            if (ThisValue == 0)					// Если в этой клетке нет значения
                continue;

            if (ThisValue == UpperValue){		// Если значения этой и верхней клеток равны
                Cells[y][x].Erase();
                Cells[y - 1][x].Fusion(Temp_Score);

                Temp = UpperValue;

                Min++;

                continue;
            }

            if (UpperValue == 0){				// Если сверху пусто
                Cells[y - 1][x].Set_Value(ThisValue);
                Cells[y][x].Erase();
                y -= 2;

                continue;
            }

            if (UpperValue != ThisValue){		// Если сверху другое значение
                Temp = ThisValue;

                continue;
            }
        }
    }

    return Array;
}

int* Plane::Shift_Down(int* Column, int &Temp_Score){

    int* Array = new int[4];

    Array[0] = 0;
    Array[1] = 0;
    Array[2] = 0;
    Array[3] = 0;

    for (int x = 0; x < 4; x++){

        int Temp;

        if(Cells[3][x].Get_Value()){			// Оцениваем, нужно ли давать значение в другую плоскость
            Temp = Cells[3][x].Get_Value();

            for(int y = 2; y >= 0; y--){		// Оцениваем, что сверху от самой нижней в ряду

                if(!Cells[y][x].Get_Value()){	// Ищем непустую клетку
                    if(y)
                    continue;
                }

                if(Cells[y][x].Get_Value() == Temp)	// Если значение непустой клетки совпадает, будем сливать
                    break;

                if(!Column[x]){	// Проверка на пустоту первой ячейки соседней плоскости

                    Cells[3][x].Erase();

                    Array[x] = Temp;
                }
            }
        }

        Temp = 0;

        int Max = 3;

        for (int y = 3; y >= 0; y--){

            if (y == Max){						// Если мы в самой нижней клетке
                Temp = ThisValue;
                continue;
            }

            if (ThisValue == 0)					// Если в этой клетке нет значения
                continue;

            if (ThisValue == LowerValue){		// Если значения этой и нижней клеток равны
                Cells[y][x].Erase();
                Cells[y + 1][x].Fusion(Temp_Score);

                Temp = LowerValue;

                Max--;

                continue;
            }

            if (LowerValue == 0){				// Если снизу пусто
                Cells[y + 1][x].Set_Value(ThisValue);
                Cells[y][x].Erase();
                y += 2;

                continue;
            }

            if (LowerValue != ThisValue){		// Если снизу другое значение
                Temp = ThisValue;

                continue;
            }
        }
    }

    return Array;
}

int Plane::Full(){

    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            if(!(this->Get_Cell(y, x)->Get_Value()))
                return 0;
        }
    }

    return 1;
}

Cell* Plane::Get_Cell(int y, int x){
    return &Cells[y][x];
}
