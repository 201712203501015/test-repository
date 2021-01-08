#include <bits/stdc++.h>
using namespace std;
const int N = 120;
char ss[N][N];
bool vis[N][N],fg = false;
int n,m,mxstep,a[N][N],b[N][N];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int X1 = -1,Y1 = -1,X2 = -1,Y2 = -1;
void dfs(int x,int y,int step)
{
    if(step > mxstep) return ;//
    if(x == n-1 && y == m-1)//
    {
        if(step < mxstep) mxstep = step,fg = true;
        return ;
    }
    if(a[x][y] != -1 && a[x][y] > step)//
    {
        return ;
    }
    if(a[x][y] == -1) a[x][y] = step;
    else a[x][y] = min(a[x][y],step);
    for(int i=0;i<4;i++)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if(0<=tx && tx<n && 0<=ty&&ty<m
           && ss[tx][ty] != '1')
        {
            if(ss[tx][ty] == 'A'){
                int px = tx,py = ty;
                if(tx == X1) tx = X2,ty = Y2;
                else tx = X1,ty = Y1;
                if(vis[px][py] == false)
                {
                    vis[tx][ty] = true;
                    vis[px][py] = true;
                    dfs(tx,ty,step+1);
                    vis[tx][ty] = false;
                    vis[px][py] = false;
                }
                continue;
            }
            if(vis[tx][ty] == false)
            {
                vis[tx][ty] = true;
                dfs(tx,ty,step+1);
                vis[tx][ty] = false;
            }
        }
        if(step+1 >= mxstep) return ;
    }
}
void ddfs(int x,int y)
{
    b[x][y] = 1;
    for(int i=0;i<4;i++)
    {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if(0<=tx && tx<n && 0<=ty&&ty<m
           && b[tx][ty] == -1)
        {
            ddfs(tx,ty);
        }
    }
}
int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%s",ss[i]);
        for(int j=0;j<m;j++)
        if(ss[i][j] == 'A')
        {
            vis[i][j] = false;
            a[i][j] = -1;
            b[i][j] = -1;
            if(X1 == -1){ X1 = i;Y1 = j; }
            else { X2 = i;Y2 = j; }
        }
    }
    if(ss[0][0] == '1' || ss[n-1][m-1] == '1')
    {
        printf("No Solution.\n");
        return 0;
    }
    ddfs(0,0);
    if(b[n-1][m-1] == -1)
    {
        printf("No Solution.\n");
        return 0;
    }
    mxstep = m*n+1;
    vis[0][0] = true;
    fg = false;
    dfs(0,0,0);
    if(fg == false) printf("No Solution.\n");
    else printf("%d\n",mxstep);

    return 0;
}
