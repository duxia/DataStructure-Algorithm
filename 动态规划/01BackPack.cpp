//============================================================================
// Name        : 01背包问题
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : 已知:有一个容量为V的背包和N件物品,第i件物品的重量是w[i],收益是p[i]
//               限制:每种物品只有一件,可以选择放或者不放
//               问题:在不超过背包容量的条件下,最多能获得多少价值的收益;
//============================================================================
/*
 * 思路:利用动态规划求解
 * 定义:f[i][v] : 前i件物品放到容量为v的背包中可以获得的最大价值
 * 将问题拆解为子问题:
 * 1.如果不放第i件物品,则问题转化为"求前(i-1)件物品放入容量为v的背包中获得的最大收益",即f[i][v]=f[i-1][v]
 * 2.如果放入第i件物品,则问题转换为"求前(i-1)件物品放入容量为v-w[i],中获得的最大收益,加上当前收益",即f[i][v]=f[i-1][v-w[i]]+p[i]
 * 状态转移方程:f[i][v]=max{f[i-1][v],f[i-1][v-w[i]]+p[i]}
 */


#include <iostream>
using namespace std;

int max(int a,int b)
{
    return a > b ? a : b;
}

int BackPack(int w[],int p[],int n,int v)
{
    int **f = new int *[n+1];
    for(int i=0;i<n+1;i++)
        f[i] = new int [v+1]();//分配状态数组并初始化为0
    //构建状态矩阵
    for(int i=1;i<=n;i++) {//0件物品没有重量和价值,起始为1
        for(int j=0;j<=v;j++) {
            if(j >= w[i]) //未超重
                f[i][j] = max(f[i-1][j],f[i-1][j-w[i]]+p[i]);
            else //若超重
                f[i][j] = f[i-1][j];
        }
    }
    //打印状态矩阵
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=v;j++)
            cout << f[i][j] << ",";
        cout << endl;
    }
    return f[n][v];
}
int main()
{
    int w[] = {0,2,4,6,1,3,6,9}; //物品重量
    int p[] = {0,2,3,4,3,1,5,10};//物品价值
    int v = 15; //背包容量

    cout << BackPack(w,p,7,15) << endl;
    return 0;
}
