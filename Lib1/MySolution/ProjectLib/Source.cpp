#include "Header.h"

//--------------------------------
//Умножение;
//--------------------------------
tppoint umnpoint(tppoint* ptr1) {

    tppoint new_p;
    new_p.x = ptr1->x * ptr1->y;
    new_p.y = ptr1->x * ptr1->y;
    return new_p;
}
//--------------------------------
//Поиск площади данной квартиры;
//--------------------------------
poi ciklpoint(poi* pp1) {
    poi new_p;
    for (int j = 0; j < pp1->x; j++)
    {
        if (j == (pp1->y - 1)) { new_p.g = pp1->z[j]; }
    } 
    return new_p;
}
