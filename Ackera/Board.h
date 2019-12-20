//
//  Board.h
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include<string>

using namespace std;
const int N(20);

class Board
{
private:
    string kind[16] = {"ooooo", "*oooo*", "*ooo**", "**ooo*",
                       "*oo*o*", "*o*oo*", "oooo*", "*oooo",
                       "oo*oo", "o*ooo", "ooo*o", "**oo**",
                       "**o*o*", "*o*o**", "***o**", "**o***"};
    
    const int score[16] = {50000, 4320, 720, 720, 720, 720, 720, 720,
                            720, 720, 720, 120, 120, 120, 20, 20};
    int row[N << 1], col[N << 1], dia[N << 1], bdia[N << 1];
public:
    int a[N][N];
    struct Cor
    {
        int x, y, val;
    }cor[2][N * N];
    int cnt = 0;
    Board();
    ~Board();
    void Prc(char c, int n);
    void Prc(int n);
    void Prc(char c);
    void Prcq(int x);
    void Print(int x, int y);
    void Move(int x, int y, int z);
    void Unmove(int x, int y, int z);
    void Findzone(int &lx, int &ly, int &rx, int & ry);
    bool kmpPiece(int x, string s, int kd, int player);
    bool kmpChess(int x, string s, int kd, int player);
    static bool cmp(Cor x, Cor y);
    void EvaluatePiece(int player);
    int EvaluateChess(int player);
    bool Iswin(int x, int y, int z);
    
};


#endif /* Board_h */
