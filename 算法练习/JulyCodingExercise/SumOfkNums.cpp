//============================================================================
// Name        : 寻找和为定值的k个数
// Author      : coffee
// Version     : version1.0
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : 递归求解,暂未想出状态方程表达式
//============================================================================
/*
 * 题目描述:输入两个整数n和sum，从数列1，2，3.......n 中随意取几个数，使其和等于sum，要求将其中所有的可能组合列出来。
 * 如果取第n个数，那么问题就转化为“取前n-1个数使得它们的和为sum-n”，对应的代码语句就是sumOfkNumber(sum - n, n - 1);
 * 如果不取第n个数，那么问题就转化为“取前n-1个数使得他们的和为sum”，对应的代码语句为sumOfkNumber(sum, n - 1);
 */
#include <iostream>
#include <list>
#include <time.h>
#include <stdlib.h>
using namespace std;
//july源码
void SumOfkNums(list<int> resultList,int sum,int n)
{
    //递归出口
        if(sum <= 0 || n <= 0)
            return;
    //输出
    if(sum == n) {//注意此处的判断条件!(上一轮的sum+当前的n刚好为定值sum)
        resultList.reverse();
        for(list<int>::iterator iter=resultList.begin();iter!=resultList.end();iter++)
            cout << *iter << "+";
        cout << n << endl;
        resultList.reverse();
    }


    resultList.push_front(n);
    SumOfkNums(resultList,sum-n,n-1);
    resultList.pop_front();
    SumOfkNums(resultList,sum,n-1);
}
//加入自己理解
void SumOfkNums2(list<int> resultList,int sum,int n)
{
    //输出
    if(sum == 0) {//注意此处的判断条件!(上一轮的sum+当前的n刚好为定值sum)
//        resultList.reverse();
        for(list<int>::iterator iter=resultList.begin();iter!=resultList.end();iter++)
            cout << *iter << "+";
        cout <<endl;
//        resultList.reverse();
    }
    //递归出口
    if(sum <= 0 || n <= 0)
        return;

    resultList.push_front(n);
    SumOfkNums2(resultList,sum-n,n-1);
    resultList.pop_front();
    SumOfkNums2(resultList,sum,n-1);
}

int main()
{
    list<int> resultList;
    int sum = 15;
    int n = 15;
    SumOfkNums2(resultList,sum,n);
    return 0;
}
