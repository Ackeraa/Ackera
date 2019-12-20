//
//  main.cpp
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//
#include "Acker.h"
#include <iostream>

#define BLACK 0
#define WHITE 1
#define inf 1e8

using namespace std;

int main()
{
    Acker A(0, 1);
    while(1)
    {
        int x;
        A.Move();
        char y;
        cin>>x>>y;
        A.Move(16 - x, y - 'A' + 1);
    }
    return 0;
}
