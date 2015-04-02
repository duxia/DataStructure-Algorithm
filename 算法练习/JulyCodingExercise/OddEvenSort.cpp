//============================================================================
// Name        : 奇偶调序
// Author      : coffee
// Version     : version1.0
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : 输入一个整数数组，调整数组中数字的顺序。
//               使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。要求时间复杂度为O(n)。
//============================================================================
/*
 * 维护两个指针,一个放在数组首部,一个放在数组中间,同时向右移动,交换奇偶下标对应的数
 */
#include <iostream>
using namespace std;
void OddEvenSort(int numarray[],int n)
{
    if(n<=2)
        return;
    int i = (n/2)&1 == 1 ? n/2+1 : n/2; //i为数组后半部分的第一个偶数
    int j = 1;
    for(;i<n;i+=2,j+=2)
        swap(numarray[i],numarray[j]);

    for(i=0;i<n;i++)
        cout << numarray[i] << ",";
    cout << endl;
}
int main()
{
    int numarray[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    OddEvenSort(numarray,sizeof(numarray)/sizeof(int));
    return 0;
}
