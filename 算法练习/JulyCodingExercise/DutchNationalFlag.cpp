//============================================================================
// Name        : ������������
// Author      : coffee
// Version     :
// Copyright   : Your copyright notice
// Description : From July Coding
//============================================================================
/*
 * ��������:
 * ����n����������ֲ�ͬ��ɫ��С������������һ��
 * ��ͨ��������������������ʹ�ô������ң�������һЩ����һЩ����һЩ����
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
