//============================================================================
// Name        : 寻找最小的K个数
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : From July Coding
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//遍历K次,O(n*k)
void TopK(int numarray[],int n,int k)
{
    int min;
    int flag=0;
    for(int i=0;i<k;i++) {
        min = numarray[i];//刷新最小值
        for(int j=i;j<n;j++)
            if(numarray[j] < min) {
                min = numarray[j];
                flag = j;
            }
        swap(numarray[i],numarray[flag]);
    }

}
//大顶堆,O(k*log(n))
void HeapAdjust(int numarray[],int n,int i)
{
    int i_lchild = 2*i + 1; //左孩子节点下标
    int i_rchild = 2*i + 2; //右孩子节点下标
    int max = i; //初始化最大值节点下标
    if(i<=n/2-1) { //如果i是非叶子节点则继续递归
        //如果左孩子大于父节点数值,且不越界,交换下标
        if(numarray[i_lchild]>numarray[max] && i_lchild<n)
            max = i_lchild;
        if(numarray[i_rchild]>numarray[max] && i_rchild<n)
            max = i_rchild;
        if(max != i) { //如果发生了交换
            swap(numarray[max],numarray[i]);//交换
            HeapAdjust(numarray,n,max);//向下递归
        }
    }
}
void HeapBuild(int numarray[],int n)
{
    for(int i=n/2-1;i>=0;i--) //从最后一个非叶子节点开始调整
        HeapAdjust(numarray,n,i);
}
int* TopK2(int numarray[],int n,int k)
{
    int *BigTopHeap = new int[k];//用于构建大顶堆
    for(int i=0;i<k;i++)
        BigTopHeap[i] = numarray[i];//初始化大顶堆
    //建堆
    HeapBuild(BigTopHeap,k);
    //遍历原始序列,依次和堆顶比较,若小于堆顶则调整
    for(int i=k;i<n;i++)
        if(numarray[i] < BigTopHeap[0]) {
            BigTopHeap[0] = numarray[i];
            HeapAdjust(BigTopHeap,k,0);
        }

    //将大顶堆排序(可有可无)
    for(int i=k-1;i>=0;i--) {
        swap(BigTopHeap[0],BigTopHeap[i]);
        HeapAdjust(BigTopHeap,i,0);
    }
    return BigTopHeap;
}
void printArray(int numarray[],int n)
{
    for(int i=0;i<n;i++)
        cout << numarray[i] << ",";
    cout << endl;
}
int main()
{
    int nums = 100;//定义100个元素的数组
    int k = 10;
    int *numarray = new int[nums];

    srand((unsigned)time(NULL));//设置随机数种子
    for(int i=0;i<nums;i++)
        numarray[i] = rand()%1000;
    //方法1
    TopK(numarray,nums,k);
    printArray(numarray,k);
    //方法2
    printArray(TopK2(numarray,nums,k),k);
    delete numarray;
    return 0;
}
