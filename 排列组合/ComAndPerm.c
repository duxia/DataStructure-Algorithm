//============================================================================
// Name        : ComAndPerm.c
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : 排列组合整理
//============================================================================

#include <stdio.h>
#include <stdlib.h>

typedef char elemType;
void do_swap(elemType *a,elemType *b);//交换函数
void PrintArray(elemType array[],int end);//打印函数

/*===========全排列(递归法)=============*/
void fullPermutation(elemType array[],int begin,int end)
{
    if(begin == end) {
        PrintArray(array,end+1);
        return;
    } else {
        int i;
        for(i=begin;i<=end;i++) {
            do_swap(&array[begin],&array[i]);
            fullPermutation(array,begin+1,end);
            do_swap(&array[begin],&array[i]);
        }
    }
}

/*===========全排列(字典序法)=============*/
int nextPermutition(elemType array[],int n)
{
    int i=n-2,j=n-1;//初始化i放在倒数第2位,j放末位
    //若降序则继续向左搜索,退出时,i和i+1为第一次出现升序位置
    while(i>=0 && array[i]>array[i+1]) i--;
    if(i<0) //未找到出现升序的位置(无下一个字典序)
        return 0;

    //从右往左,即i←j,搜索第一个比array[i]大的数
    while(i<j && array[i]>array[j]) j--;

    //交换i,j对应的数
    do_swap(&array[i],&array[j]);

    //反转i+1之后的所有数
    int a,b;
    for(a=i+1,b=n-1;a<b;a++,b--)
        do_swap(&array[a],&array[b]);
    return 1;
}
void fullPermutation2(elemType array[],int n)
{
    do
        PrintArray(array,n);
    while(nextPermutition(array,n));
}

/*===========组合c(n,m)(递归法)=============*/
void combination(elemType array[],elemType subArray[],int n,int m,int subLen)
{
    if(m == 0) {
        PrintArray(subArray,subLen);
        return;
    } else {
        int i;
        for(i=n;i>=m;i--) {
            subArray[m-1] = array[i-1];
            combination(array,subArray,i-1,m-1,subLen);
        }
    }
}

/*===========组合c(n,m)(非递归)=============*/
void combination2(elemType array[],elemType subArray[],int n,int m)
{
    //定义01数组
    elemType *usedArray = (elemType *)calloc(m,sizeof(elemType));
    //初始化状态数组e.g(1,1,1,0,0)
    int i,j;
    for(i=0;i<m;i++)
        usedArray[i] = 1;
    for(;i<n;i++)
        usedArray[i] = 0;

    int count,flag=1;//count用于统计1的个数,flag表示是否还存在10组合的状态
    while(flag) {
        //根据usedArray状态,构造subArray
        for(i=0,j=0;i<n;i++)
            if(usedArray[i])
                subArray[j++] = array[i];

        //输出
        PrintArray(subArray,m);

        flag=0;//若下面的for循环中找不到10组合则退出while循环
        //从左向右搜索第一个10,若找到则交换,否则程序结束
        for(i=0;i<n-1;i++)
            if(usedArray[i] && !usedArray[i+1]) {//10状态
                usedArray[i] = 0;
                usedArray[i+1] = 1;//交换10

                //统计i之前的1的个数
                for(j=0,count=0;j<i;j++)
                    if(usedArray[j])
                        count++;

                //将i之前所有1移动到左端
                for(j=0;j<count;j++)
                    usedArray[j] = 1;
                for(;j<i;j++)
                    usedArray[j] = 0;

                flag = 1;
                break;
            }
    }
    free(usedArray);
}

/*===========排列组合A(n,m)=============*/
void ComAndPrem(elemType array[],elemType subArray[],int n,int m)
{
    //定义01数组
    elemType *usedArray = (elemType *)calloc(m,sizeof(elemType));
    //初始化状态数组e.g(1,1,1,0,0)
    int i,j;
    for(i=0;i<m;i++)
        usedArray[i] = 1;
    for(;i<n;i++)
        usedArray[i] = 0;

    int count,flag=1;//count用于统计1的个数,flag表示是否还存在10组合的状态
    while(flag) {
        //根据usedArray状态,构造subArray
        for(i=0,j=0;i<n;i++)
            if(usedArray[i])
                subArray[j++] = array[i];

        //输出
        fullPermutation2(subArray,m);

        flag=0;//若下面的for循环中找不到10组合则退出while循环
        //从左向右搜索第一个10,若找到则交换,否则程序结束
        for(i=0;i<n-1;i++)
            if(usedArray[i] && !usedArray[i+1]) {//10状态
                usedArray[i] = 0;
                usedArray[i+1] = 1;//交换10

                //统计i之前的1的个数
                for(j=0,count=0;j<i;j++)
                    if(usedArray[j])
                        count++;

                //将i之前所有1移动到左端
                for(j=0;j<count;j++)
                    usedArray[j] = 1;
                for(;j<i;j++)
                    usedArray[j] = 0;

                flag = 1;
                break;
            }
    }
    free(usedArray);
}

/*===========辅助函数=============*/
void do_swap(elemType *a,elemType *b)
{
    elemType tmp = *a;
    *a = *b;
    *b = tmp;
}
void PrintArray(elemType array[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%c ",array[i]);
    printf("\n");
}

int main(void) {
    elemType array[] = {'A','B','C','D'};
    int n = sizeof(array)/sizeof(elemType);
//    fullPermutation(array,0,n-1);
//    fullPermutation2(array,n);

    int m = 2;
    elemType *subArray = (elemType *)calloc(m,sizeof(elemType));
//    combination(array,subArray,n,m,m);
//    combination2(array,subArray,n,m);
    ComAndPrem(array,subArray,n,m);

    free(subArray);
    return EXIT_SUCCESS;
}
