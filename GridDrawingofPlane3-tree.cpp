#include<bits/stdc++.h>
using namespace std;

int ch[101][3];
int dp[40][40][40][40][20];
int SH = 20;
int n;
int cross(int x1, int y1, int x2, int y2){
    return x1 * y2 - x2 * y1;
}
bool inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
    int ar =  abs(cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1));
    int ar2 = abs(cross(x2 - x1, y2 - y1, x - x1, y - y1))
            + abs(cross(x3 - x1, y3 - y1, x - x1, y - y1))
            + abs(cross(x3 - x2, y3 - y2, x - x2, y - y2));
    return ar == ar2 and cross(x1 - x, y1 - y, x2 - x, y2 - y) != 0
        and cross(x2 - x, y2 - y, x3 - x, y3 - y) != 0
        and cross(x3 - x, y3 - y, x1 - x, y1 - y) != 0 ;
}
int pos[20][2];
bool recursion(int x1, int y1, int x2, int y2, int root)
{
    if(dp[x1 + SH][y1 + SH][x2 + SH][y2 + SH][root] != -1)
        return dp[x1 + SH][y1 + SH][x2 + SH][y2 + SH][root];
    if(root == 0)
    {
        dp[x1 + SH][y1 + SH][x2 + SH][y2 + SH][root] = true;
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << root << endl;
        return true;
    }
    for(int i = -n; i <= n; i++)
    {
        for(int j = -n; j <= n; j++)
        {
            //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << i << " " << j << endl;
            if(inside(0, 0, x1, y1, x2, y2, i, j))
            {

                if(recursion(-i, -j, x1 - i, y1 - j, ch[root][0])
                   and recursion(x1 -i, y1 -j, x2 - i, y2 - j, ch[root][1])
                   and recursion(x2 -i, y2 -j, - i, - j, ch[root][2]))
                   {
                        dp[x1 + SH][y1 + SH][x2 + SH][y2 + SH][root] = true;
                        cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << i << " " << j << " " << root << endl;
                        return true;
                   }
            }
        }
    }
    //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << root << endl;
    dp[x1 + SH][y1 + SH][x2 + SH][y2 + SH][root] = false;
    return false;
}

void build(int x1, int y1, int x2, int y2, int root, int shx, int shy)
{
    if(root == 0)
    {
        return;
    }
    //cout << "hola" << endl;
    for(int i = -n; i <= n; i++)
    {
        for(int j = -n; j <= n; j++)
        {
            //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << i << " " << j << endl;
            if(inside(0, 0, x1, y1, x2, y2, i, j))
            {
                //cout << "hola" << endl;
                if(dp[-i + SH][-j + SH][x1 - i + SH][y1 - j + SH][ch[root][0]] == 1
                   and dp[x1 - i + SH][y1 -j + SH][x2 - i + SH][y2 - j + SH][ch[root][1]] == 1
                   and dp[x2 - i + SH][y2 -j + SH][-i + SH][-j + SH][ch[root][2]] == 1)
                {

                    pos[root][0] = i + shx;
                    pos[root][1] = j + shy;
                    build(-i, -j, x1 - i, y1 - j, ch[root][0], shx + i, shy + j);
                    build(x1 -i, y1 -j, x2 - i, y2 - j, ch[root][1], shx + i, shy + j);
                    build(x2 -i, y2 -j, - i, - j, ch[root][2], shx + i, shy + j);
                    return;
                }
            }
        }
    }

}

int main()
{
    cin >>n;
    for(int i = 1; i <= n; i++)
    {
        cin >> ch[i][0] >> ch[i][1] >> ch[i][2];
    }

    memset(dp, -1, sizeof dp);
    int root = 1;
    int area = 1e9;
    int mx1, my1, mx2, my2;
    for(int x1 = -n; x1 <= n; x1++)
        for(int y1 = -n; y1 <= n; y1++)
            for(int x2 = -n; x2 <= n; x2++)
                for(int y2 = -n; y2 <= n; y2++)
                {
                    int tarea = (max({0, x1, x2}) - min({0, x1, x2})) * (max({0, y1, y2}) - min({0, y1, y2}));
                    int tx1 = x1, tx2 = x2, ty1 = y1, ty2 = y2;
                    if(cross(tx1, ty1, tx2, ty2) < 0)
                    {
                        swap(tx1, tx2);
                        swap(ty1, ty2);
                    }
                    if(recursion(tx1, ty1, tx2, ty2, 1) and tarea < area)
                    {
                        area = tarea;
                        mx1 = tx1, my1 = ty1, mx2 = tx2, my2 = ty2;
                        
                    }

                }
    
    build(mx1, my1, mx2, my2, 1, 0, 0);
    cout << area << endl;
    cout << mx1 << " " << my1 << " " << mx2 << " " << my2 << endl;
    for(int i = 1; i <= n; i++)
        cout << pos[i][0] <<  " " << pos[i][1] << endl;
    return 0;
}
