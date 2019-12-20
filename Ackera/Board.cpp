//
//  Board.cpp
//  Ackera
//
//  Created by 高善勋 on 2019/3/31.
//  Copyright © 2019 高善勋. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include "Board.h"

using namespace std;

Board::Board()
{
    for (int i=1;i<=15;i++)
    {
        for (int j=1;j<=15;j++)
        {
            a[i][j] = -1;
        }
    }
}

Board::~Board()
{
    memset(a, 0, sizeof(a));
}

void Board::Move(int x, int y, int z)
{
    if (a[x][y] == -1)
    {
        a[x][y] = z;
    }
  //  if (Iswin(x, y, z)) cout<<z<<" win"<<endl;
}

void Board::Unmove(int x, int y, int z)
{
    a[x][y] = -1;
}

bool Board::Iswin(int x, int y, int z)
{
    int xx, yy, cnt;
    xx = x; cnt = 0;
    while (a[xx][y] == a[x][y] && a[xx][y] == z)
    {
        xx++;
        cnt++;
    }
    xx = x - 1;
    while (a[xx][y] == a[x][y] && a[xx][y] == z)
    {
        x--;
        cnt++;
    }
    if (cnt >=5 ) return true;
    yy = y; cnt = 0;
    while (a[x][yy] == a[x][y] && a[x][yy] == z)
    {
        yy++;
        cnt++;
    }
    yy = y - 1;
    while (a[x][yy] == a[x][y] && a[x][yy] == z)
    {
        yy--;
        cnt++;
    }
    if (cnt >= 5) return true;
    xx = x; yy = y; cnt = 0;
    while (a[xx][yy] == a[x][y] && a[xx][yy] == z)
    {
        xx++;
        yy++;
        cnt++;
    }
    xx = x-1; yy = y - 1;
    while (a[xx][yy] == a[x][y] && a[xx][yy] == z)
    {
        xx--;
        yy--;
        cnt++;
    }
    if (cnt >= 5) return true;
    xx = x; yy = y; cnt = 0;
    while (a[xx][yy] == a[x][y] && a[xx][yy] == z)
    {
        xx--;
        yy++;
        cnt++;
    }
    xx = x + 1; yy = y - 1;
    while (a[xx][yy] == a[x][y] && a[xx][yy] == z)
    {
        xx++;
        yy--;
        cnt++;
    }
    if (cnt >= 5) return true;
    return false;
}

bool Board::kmpPiece(int x, string s, int kd, int player)
{
    string t = "";
    int j = 15;
    if (kd == 1)
    {
        for (int i=1;i<=15;i++)
        {
            if (a[x][i] == player)
            {
                t += "o";
            }
            else if (a[x][i] == -1)
            {
                t += "*";
            }
            else
            {
                t += '#';
            }
        }
    }
    else if (kd == 2)
    {
        for (int i=1;i<=15;i++)
        {
            if (a[i][x] == player)
            {
                t += "o";
            }
            else if (a[i][x] == -1)
            {
                t += "*";
            }
            else
            {
                t += '#';
            }
        }
    }
    else if (kd == 3) // \ //
    {
        if (x >= 0)
        {
            for (int i=x;i<=15;i++)
            {
                if (a[i][i - x + 1] == player)
                {
                    t += "o";
                }
                else if (a[i][i - x + 1] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
            }
        }
        else
        {
            x = -x;
            for (int i=1;i<=15 - x + 1;i++)
            {
                if (a[i][x + i - 1] == player)
                {
                    t += "o";
                }
                else if (a[i][x + i - 1] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
                j--;
            }
        }
    }
    else // /
    {
        if (x <= 15)
        {
            for (int i=1;i<=x;i++)
            {
                if (a[i][x - i + 1] == player)
                {
                    t += "o";
                }
                else if (a[i][x -i + 1] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
            }
        }
        else
        {
            x -= 15;
            for (int i=x+1;i<=15;i++)
            {
                if (a[i][j] == player)
                {
                    t += "o";
                }
                else if (a[i][j] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
                j--;
            }
        }
    }
    int lt = (int)t.length();
    int ls = (int)s.length();
    for (int i=0;i<lt;i++)
    {
        int j = 0;
        for (;j<ls;j++)
        {
            if (t[i + j] != s[j]) break;
        }
        if (j == ls) return true;
    }
    return false;
}
bool Board::cmp (Cor x, Cor y) 
{
    return x.val > y.val;
}

void Board::EvaluatePiece(int player)
{
    cnt = 0;
    for (int i=1;i<=300;i++)
    {
        cor[player][i].val = 0;
    }
    for (int i=1;i<=15;i++)
    {
        for (int j=1;j<=15;j++)
        {
            if (a[i][j] != -1) continue;
            ++cnt;
            cor[player][cnt].x = i;
            cor[player][cnt].y = j;
            Move(i, j, player);
            //row
            for (int k = 0;k<16;k++)
            {
                if (kmpPiece(i, kind[k], 1, player))
                {
                    cor[player][cnt].val += score[k];
                    break;
                }
            }
            //col
            for (int k=0;k<16;k++)
            {
                if (kmpPiece(j, kind[k], 2, player))
                {
                    cor[player][cnt].val += score[k];
                    break;
                }
            }
            //dia
            for (int k=0;k<16;k++)
            {
                int x;
                if (i >= j) x = i - j + 1;
                else x = i - j - 1;
                if (kmpPiece(i - j + 1, kind[k], 3, player))
                {
                    cor[player][cnt].val += score[k];
                    break;
                }
            }
            //bdia
            for (int k=0;k<16;k++)
            {
                if (kmpPiece(i + j - 1, kind[k], 4, player))
                {
                    cor[player][cnt].val += score[k];
                    break;
                }
            }
            
            Unmove(i, j, player);
        }
    }
    sort(cor[player] + 1, cor[player] + cnt + 1, cmp);
}
bool Board::kmpChess(int x, string s, int kd, int player)
{
    string t = "";
    int j = 15;
    if (kd == 1)
    {
        for (int i=1;i<=15;i++)
        {
            if (a[x][i] == player)
            {
                t += "o";
            }
            else if (a[x][i] == -1)
            {
                t += "*";
            }
            else
            {
                t += '#';
            }
        }
    }
    else if (kd == 2)
    {
        for (int i=1;i<=15;i++)
        {
            if (a[i][x] == player)
            {
                t += "o";
            }
            else if (a[i][x] == -1)
            {
                t += "*";
            }
            else
            {
                t += '#';
            }
        }
    }
    else if (kd == 3) //.
    {
        if (x <= 15)
        {
            for (int i=1;i<=x;i++)
            {
                if (a[i + 15 - x][i] == player)
                {
                    t += "o";
                }
                else if (a[i + 15 - x][i] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
            }
        }
        else
        {
            x -= 15;
            for (int i=1;i<=15 - x;i++)
            {
                if (a[i][x + i] == player)
                {
                    t += "o";
                }
                else if (a[i][x + i] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
                j--;
            }
        }
    }
    else // /
    {
        if (x <= 15)
        {
            for (int i=1;i<=x;i++)
            {
                if (a[i][x - i + 1] == player)
                {
                    t += "o";
                }
                else if (a[i][x -i + 1] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
            }
        }
        else
        {
            x -= 15;
            for (int i=x+1;i<=15;i++)
            {
                if (a[i][j] == player)
                {
                    t += "o";
                }
                else if (a[i][j] == -1)
                {
                    t += "*";
                }
                else
                {
                    t += '#';
                }
                j--;
            }
            // cout<<t<<endl;
        }
    }
    int lt = (int)t.length();
    int ls = (int)s.length();
    for (int i=0;i<lt;i++)
    {
        int j = 0;
        for (;j<ls;j++)
        {
            if (t[i + j] != s[j]) break;
        }
        if (j == ls) return true;
    }
    return false;
}

int Board::EvaluateChess(int player)
{
    for (int i=1;i<=30;i++)
    {
        row[i] = 0;
        col[i] = 0;
        dia[i] = 0;
        bdia[i] = 0;
    }
    for (int i=1;i<=15;i++)
    {
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i, kind[k], 1, player))
            {
                row[i] += score[k];
                break;
            }
        }
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i, kind[k], 2, player))
            {
                col[i] += score[k];
                break;
            }
        }
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i, kind[k], 3, player))
            {
                dia[i] += score[k];
                break;
            }
        }
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i + 15, kind[k], 3, player))
            {
                dia[i + 15] += score[k];
                break;
            }
        }
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i, kind[k], 4, player))
            {
                bdia[i] += score[k];
                break;
            }
        }
        for (int k=0;k<16;k++)
        {
            if (kmpChess(i + 15, kind[k], 4, player))
            {
                bdia[i + 15] += score[k];
                break;
            }
        }
    }
    
    int sum = 0;
    for (int i=1;i<=30;i++)
    {
        sum += row[i] + col[i] + dia[i] + bdia[i];
    }
    return sum;
}

void Board::Prc(char c, int n)
{
    for (int i=1;i<=n;i++)
    {
        cout<<c;
    }
}

void Board::Prc(int n)
{
    for (int i=1;i<=n;i++)
    {
        cout<<endl;
    }
}

void Board::Prc(char c)
{
    cout<<c;
}

void Board::Prcq(int x)
{
    if (x == 0) cout<<"*";
    else if (x == 1) cout<<"o";
    else if (x == 2) cout << "X";
    else if (x == 3) cout << "O";
    else cout <<" ";
}

void Board::Print(int x, int y)
{
    Prc(10);
    Prc(' ', 16);for (int i=1;i<=15;i++) printf("  %c   ", i + 64);cout<<endl;
    Prc(' ', 15); Prc('_',91); Prc(1);
    for (int j=1;j<=15;j++)
    {
        Prc(' ', 15); for (int i=1;i<=15;i++) static_cast<void>(Prc('|')), Prc(' ',5); Prc('|'); Prc(1);
        Prc(' ', 12); cout<<15-j + 1<<' '; if (j > 6) cout<<' ';
        for (int i=1;i<=15;i++)
        {
            static_cast<void>(Prc('|'));
            static_cast<void>(Prc(' ', 2));
            if (j == x && i == y)
            {
                static_cast<void>(Prcq(a[j][i] + 2));
            }
            else
            {
                static_cast<void>(Prcq(a[j][i]));
            }
            Prc(' ',2);
        }
        Prc('|');Prc(1);
        Prc(' ', 15); for (int i=1;i<=15;i++) static_cast<void>(Prc('|')), Prc('_',5); Prc('|'); Prc(1);
    }
    
}
