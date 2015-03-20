//============================================================================
// Name        : 最长回文字串
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : From July Coding
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int LongestPalindromeSubStr(string &str)
{
    if(str=="")
        return 0;

    int length = str.length();
    int tmp=0,max=0;
    for(int i=0;i<length;i++) {//i为中心元素下标
        //str[i-1]=str[i+1],奇数情况
        for(int offset=0; i-offset>=0 && i+offset<length ;offset++) {//offset为相对于i的偏移量
            if(str[i-offset] != str[i+offset])
                break;
            tmp = offset*2 + 1;
        }
        if(tmp > max)
            max = tmp;
        //str[i]=str[i+1],偶数情况
        for(int offset=0; i-offset>=0 && i+offset+1<length ;offset++) {
            if(str[i-offset] != str[i+offset+1])
                break;
            tmp = offset*2 + 2;
        }
        if(tmp > max)
            max = tmp;
    }
    return max;
}

int main()
{
    string str = "abbaabcba";
    cout << LongestPalindromeSubStr(str) << endl;
    return 0;
}
