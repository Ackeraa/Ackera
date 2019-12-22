//
//  Acker.cpp
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//

#include <iostream>

#include "Acker.h"

#define inf 1e8
using namespace std;

Acker::Acker(int who, int opps):who(who), opps(opps)
{
    step = 0;
}

Acker::~Acker()
{
    x = 0;
}

void Acker::Move(int x, int y)
{
    B.Move(x, y, opps);
//    B.Print(x, y);
}

pair<int, int> Acker::Move()
{
    step++;
    if (step == 1)
    {
        B.Move(8, 8, who);
        return make_pair(8, 8);
        //B.Print(8, 8);
    }
    else
    {
        int tmp = AlphaBeta(maxdep, -inf, inf, who);
        B.Move(x, y, who);
        return make_pair(x, y);
       // cout<<tmp<<endl;
       // B.Print(x, y);
    }
    
}

void Acker::Unmove(int x, int y)
{
    B.Unmove(x, y, opps);
}

void Acker::Unmove()
{
    B.Unmove(x, y, who);
}

void Acker::Print()
{
 //   B.Print();
}

int Acker::AlphaBeta(int depth, int alpha, int beta, int player) //待改
{
    if (depth == 0)
    {
        return B.EvaluateChess(who) -  B.EvaluateChess(opps);
    }
    int val;
  /*  for (int i=1;i<=cnt;i++)
    {
        cor[i].x = B.cor[player][i].x;
        cor[i].y = B.cor[player][i].y;
        cor[i + cnt].x = B.cor[!player][i].x;
        cor[i + cnt].y = B.cor[!player][i].y;
    }*/
    if (player == who)
    {
        B.EvaluatePiece(who);
        for (int i=1;i<=cnt * 2;i++)
        {
            int xx = B.cor[player][i].x;
            int yy = B.cor[player][i].y;
            B.Move(xx, yy, player);
        //    B.EvaluateChess(int x, int y, int who);
            val = AlphaBeta(depth - 1, alpha, beta, opps);
            B.Unmove(xx, yy, player);
            if (val > alpha)
            {
                alpha = val;
                x = xx;
                y = yy;
            }
            if (alpha >= beta) return alpha;
        }
        return alpha;
    }
    else
    {
        B.EvaluatePiece(opps);
        for (int i=1;i<=2 * cnt;i++)
        {
            int xx = B.cor[player][i].x;
            int yy = B.cor[player][i].y;
            B.Move(xx, yy, player);
            val = AlphaBeta(depth - 1, alpha, beta, who);
            B.Unmove(xx, yy, player);
            if (val < beta) beta = val;
            if (alpha >= beta) return beta;
        }
        return beta;
    }
}


