/*
 ============================================================================
 Name        : Sort.c
 Author      : coffee
 Version     : 1.0
 Copyright   : Copyright ©2015 sweet coffee.All right reserved.
 Description : 排序整理
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
/*===========直接插入排序=============*/
void insertSort(int numarray[],int n)
{
    int i,j,tmp;
    for(i=1;i<n;i++) {
        tmp = numarray[i]; //待移位数暂存
        j = i-1; //从待移位的下一位开始比较
        while(numarray[j]>tmp && j>=0) { //从右往左搜索(不等号方向决定排序方向)
            numarray[j+1] = numarray[j];
            j--;
        }//当while退出时找到第一个不小于numarray[i]的数
        numarray[j+1] = tmp;
        //printArray(numarray,9);//打印每趟排序数组
    }
}
/*===========希尔排序=============*/
void shellSort(int numarray[],int n)
{
    int i,j,tmp;
    int k = n/2;//其中k为分组间距
    while(k > 0) {
        for(i=k;i<n;i++) {                      /*==============*/
            tmp = numarray[i];                  /*  该部分可以看作 */
            j = i-k;                            /*  间隔为k的       */
            while(numarray[j]>tmp && j>=0) {    /*  普通插入排序  */
                numarray[j+k] = numarray[j];    /*              */
                j -= k;                         /*              */
            }                                   /*              */
            numarray[j+k] = tmp;                /*              */
            //printArray(numarray,9);           /* 打印每趟排序数组 */
        }                                       /*==============*/
        k = k/2;
    }
}
/*===========选择排序=============*/
void selectSort(int numarray[],int n)
{
    int i,j,flag;
    int min;
    for(i=0;i<n-1;i++){
        min = numarray[i];
        for(j=i+1;j<n;j++){
            if(numarray[j]< min){
                min = numarray[j]; //刷新最小值
                flag = j; //记录位置
            }
        }
        numarray[flag] = numarray[i];
        numarray[i] = min;
        //printArray(numarray,n);
    }
}
/*===========堆排序=============*/
void HeapAdjust(int numarray[], int i, int nums)
{
    int i_lchild = 2*i+1;   //左孩子节点下标
    int i_rchild = 2*i+2;   //右孩子节点下标
    int max=i;  //初始化max=i，max为下标，不是数值
    if(i<=nums/2-1)//如果i为非叶子节点，则
    {
        if(i_lchild<nums && numarray[i_lchild]>numarray[max])   //大顶堆
            max=i_lchild;   //交换下标，不是交换数值
        if(i_rchild<nums && numarray[i_rchild]>numarray[max])   //不越界
            max=i_rchild;
        if(max!=i)  //如果发生了交换
        {
            do_swap(&numarray[i],&numarray[max]);
            HeapAdjust(numarray,max,nums);  //向下递归下标为max的节点
        }
    }

}
void HeapBuild(int numarray[], int nums)
{
    int i;
    for(i=nums/2-1;i>=0;i--)    //(nums/2-1)为最后一个非叶子节点，数组下标从0开始
        HeapAdjust(numarray,i,nums);
}
void HeapSort(int numarray[], int nums)
{
    HeapBuild(numarray,nums);
    printArray(numarray,nums); //打印建立堆后的数组
    //写法1：
    /*int i;
    for(i=nums-1;i>=0;i--)
    {
        do_swap(&numarray[0],&numarray[i]);
        HeapAdjust(numarray,0,i);   //每交换一次堆顶和最后一个元素，递归调整整个堆
        //printArray(numarray,nums); //打印每趟排序
    }*/
    //写法2：
    while(nums>=1)
    {
        do_swap(&numarray[0],&numarray[--nums]);
        HeapAdjust(numarray,0,nums);
    }
}
/*===========冒泡排序=============*/
void bubbleSort(int numarray[],int n)
{
    int i,j;
    /*for(i=0;i<n-1;i++) {//从0开始
        for(j=0;j<n-i-1;j++)
            if(numarray[j] > numarray[j+1])
                do_swap(&numarray[j],&numarray[j+1]);
        //printArray(numarray,n);
    }*/
    /*for(i=1;i<n-1;i++) {//从1开始
        for(j=0;j<n-i;j++)
            if(numarray[j] > numarray[j+1])
                do_swap(&numarray[j],&numarray[j+1]);
        //printArray(numarray,n);
    }*/
    /*int end = n-1;//修改尾部下标
    for(i=0;i!=end;i++) {
    	for(j=0;j!=end;j++)
    		if(numarray[j] > numarray[j+1])
    			do_swap(&numarray[j],&numarray[j+1]);
    	end = j;
    }*/
    int end = n;//修改尾部下标方式2
    while(end != 0) {
    	for(j=0;j!=end;j++)
    		if(numarray[j] > numarray[j+1])
    			do_swap(&numarray[j],&numarray[j+1]);
    	end = j;
    }
}
void bubbleSortPro(int numarray[],int n)
{
    int i,j,pos;
    for(i=0;i<n-1;i++) {//从0开始
        pos = 0;
        for(j=0;j<n-i-1;j++) {
            if(numarray[j] > numarray[j+1]) {
                do_swap(&numarray[j],&numarray[j+1]);
                pos = j; //记录最近依次交换的位置,当最近一次交换位置为0时,说明排序已经结束
            }
        }
        printArray(numarray,n);
        if(pos==0) //pos为0，则说明上一趟过程未发生交换，排序终止
            break;
    }
}
/*===========快速排序=============*/
int partitionsplit(int numarray[],int low,int high)
{
    int privotekey = numarray[low];//初始化privotekey为序列首元素
    while(low < high) {
        while(low<high && numarray[high]>=privotekey) high--;
        do_swap(&numarray[high],&numarray[low]);//从右往左找到第一个大于privotekey的值,并交换
        while(low<high && numarray[low]<=privotekey) low++;
        do_swap(&numarray[low],&numarray[high]);//从左往右找到第一个小于privotekey的值,并交换
    }
    return low;//传回调整完之后privotekey所在位置的下标
}
void QuickSort(int numarray[],int low,int high)
{
    if(low<high) {
        int privotePos = partitionsplit(numarray,low,high);
        QuickSort(numarray,low,privotePos-1);//递归左序列
        QuickSort(numarray,privotePos+1,high);//递归右序列
        //printArray(numarray,9);
    }
}
/*===========归并排序=============*/
void merge(int numarray[],int low,int mid,int high)
{
    int i=low;  int j=mid+1;
    int m=mid;  int n=high; //i,m控制左侧;n,j控制右侧
    int *tmp = (int *)calloc(high-low+1,sizeof(int));//分配临时数组(这样分配慢)
    int k=0; //控制临时数组下标
    while(i<=m && j<=n)
        if(numarray[i]<numarray[j])
            tmp[k++] = numarray[i++];
        else
            tmp[k++] = numarray[j++];
    while(i<=m)//拷贝左侧剩余有序数组
        tmp[k++] = numarray[i++];
    while(j<=n)//拷贝右侧剩余有序数组
        tmp[k++] = numarray[j++];

    for(i=0;i<k;i++)//将有序数组拷贝回原数组
        numarray[low+i] = tmp[i];
    free(tmp);
}
//自顶向下
void mergeSortFromTop(int numarray[],int low,int high)
{
    if(low < high) {
        int mid = (low+high)/2;
        mergeSortFromTop(numarray,low,mid);
        mergeSortFromTop(numarray,mid+1,high);
        merge(numarray,low,(low+high)/2,high);
        //printArray(numarray,9);
    }
}
//自底向上
void mergeSortFromBottom(int numarray[],int n)
{
    int i;
    int particalLen = 1;//初始化分组长度为1
    while(particalLen < n) {
        for(i=0;i<n-2*particalLen;i+=2*particalLen)
            merge(numarray,i,i+particalLen-1,i+2*particalLen-1);
        if(i < n-particalLen) //即,n-i>particalLen,最后两组中,有一组长度不足particalLen
            merge(numarray,i,i+particalLen-1,n-1);
        particalLen *= 2;
        printArray(numarray,n);
    }
}
/*===========基数排序=============*/
int getPosNum(int num,int n) //获取第n位上的数字
{
    int i,tmp = 1;
    for(i=0;i<n-1;i++)
        tmp *= 10;
    return (num/tmp)%10;
}
void radixSort(int numarray[],int n)
{
    int i,j,k,index;
    int *radixArray[10];//指针数组,分别指向收集0-9的序列空间
    for(i=0;i<10;i++){  //初始化
        radixArray[i] = (int *)calloc(n+1,sizeof(int));
        radixArray[i][0] = 0;   //radixArray[i][0]记录该组元素总个数
    }                           //radixArray[i][index]表示i号序列空间的第index个数
    for(i=0;i<31;i++) { //从个位到31位
        for(j=0;j<n;j++) { //分配过程
            int num = getPosNum(numarray[j],i); //获取numarray[j]第i位的数字
            index = ++radixArray[num][0];   //获取对应数字所在序列空间的索引值
            radixArray[num][index] = numarray[j]; //放入序列空间
        }
        for(j=0,k=0;j<10;j++) { //收集过程
            for(index=1;index<=radixArray[j][0];index++) {
                numarray[k++] = radixArray[j][index];
            }
            radixArray[j][0] = 0; //复位
        }
    }
}
/*===========辅助函数=============*/
void printArray(int numarray[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d,",numarray[i]);
    }
    printf("\n");
}
void do_swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void main() {
    int numarray[9] = {3,1,5,7,2,4,9,6,2};
    //QuickSort(numarray,0,8);
    //mergeSortFromTop(numarray,0,8);
    //mergeSortFromBottom(numarray,9);
    radixSort(numarray,9);
    printArray(numarray,9);
}
