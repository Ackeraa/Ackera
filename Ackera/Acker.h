//
//  Acker.h
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//

#ifndef Acker_h
#define Acker_h
#include "Board.h"

class Acker
{
private:
    int x, y;
    int who, opps;
    const int maxdep = 2;
    int step;
    int cnt = 100;
    Board B;
    struct Cor
    {
        int x, y;
    }cor[30];
    
public:
    Acker(int who = 0, int opps = 1);
    ~Acker();
    void Move(int x, int y);
    void Move();
    void Unmove(int x, int y);
    void Unmove();
    void Print();
    int AlphaBeta(int depth, int alpha, int beta, int player);
    
};
#endif /* Acker_h */
