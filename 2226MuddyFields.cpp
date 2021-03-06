#include<iostream>
#include<stdio.h>
#include<map>
#include<string.h>
#define M 2500
using namespace std;
int R,C;
char board[50][60];
int vis[50][50];
int n,m;
int g[2500][2500];
map<int,int> mx;
map<int,int> my;
void getrow(int i,int j)
{
    while(j<C && board[i][j]=='*'){
        vis[i][j]=1;
        mx[i*C+j]=n;
        j++;
    } 
}
void getcol(int i,int j)
{
    while(i<R && board[i][j]=='*'){
        vis[i][j]=1,my[i*C+j]=m,i++;
    }
}
int used[M],m2[M];
bool dfs(int v) {
    for(int i=0;i<m;i++)
        if(!used[i]&&g[v][i]) {
            used[i]=1;  //访问标记,防止死循环
            if(m2[i]==-1||dfs(m2[i])) {//这个递归很妙
                m2[i]=v;
                return 1;
            }
        }
    return 0;
}

int hungary() {
    int cnt=0;
    
    memset(m2,-1,sizeof(m2));
    for(int i=0;i<n;i++) {
        memset(used,0,sizeof(used));
        if(dfs(i)) cnt++;
    }
    return cnt;
}


int main()
{
    scanf("%d%d",&R,&C);
    for(int i=0;i<R;i++)
        scanf("%s",board[i]);
    
    memset(vis,0,sizeof(vis));
    n=m=0;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            if(!vis[i][j] && board[i][j]=='*')
                getrow(i,j),n++;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            if(!vis[i][j] && board[i][j]=='*')
                getcol(i,j),m++;
    
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            if(board[i][j]=='*') g[mx[i*C+j]][my[i*C+j]]=1;
    
    printf("%d\n",hungary());
    
    
    return 0;
}
