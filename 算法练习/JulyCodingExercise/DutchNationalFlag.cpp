//============================================================================
// Name        : 荷兰国旗问题
// Author      : coffee
// Version     :
// Copyright   : Your copyright notice
// Description : From July Coding
//============================================================================
/*
 * 问题描述:
 * 现有n个红白蓝三种不同颜色的小球，乱序排列在一起，
 * 请通过两两交换任意两个球，使得从左至右，依次是一些红球、一些白球、一些蓝球。
 */

#include <iostream>
#include <cstring>
using namespace std;

void DutchNationalFlag(int flag[],int n)
{
    int *current = flag;
    int *begin = flag;
    int *end = flag+n-1;
    while(current <= end) {
        if(*current == 0) {
            swap(*current,*begin);
            current++;
            begin++;
        }
        else if(*current == 1) {
            current++;
        }
        else {
            swap(*current,*end);
            end--;
        }
    }
}

int main()
{
    int flag[] = {0,1,2,1,1,2,0,2,1,0};
    int n = sizeof(flag)/sizeof(int);
    DutchNationalFlag(flag,n);
    for(int i=0;i<n;i++)
        cout << flag[i];
    cout << endl;
    return 0;
}
