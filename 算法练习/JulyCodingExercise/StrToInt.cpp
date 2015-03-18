//============================================================================
// Name        : 字符串转换成整数
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : From July Coding
//============================================================================

#include <iostream>
using namespace std;

int StrToInt(const char *str)
{
	int MAX_INT = (int)((unsigned)~0 >> 1);
	int MIN_INT = -(int)((unsigned)~0 >> 1)-1;
	unsigned int n=0;
	//判断不为空
	if(!str || !(*str)) {
		return 0;
	}
	//判断正负
	int sign = 1;
	if(*str == '+')
		str++;
	if(*str == '-') {
		sign = -1;
		str++;
	}
	//判断空格
	while((*str) == ' ') {
		str++;
	}
	//为数字时循环
	while(*str>='0' && *str<='9') {
		int tmp = *str - '0';
		if(sign>0 && (n>MAX_INT/10 || (n==MAX_INT/10 && tmp>MAX_INT%10 ))) {
			n = MAX_INT; //两种越界情况:①10*n>MAX_INT;②10*n未越界，但10*n+tmp > MAX_INT(越界)
			break;
		}
		if(sign<0 && (n>(unsigned)MIN_INT/10 || (n==(unsigned)MIN_INT/10 && tmp>(unsigned)MIN_INT%10 ))) {
			n = MIN_INT;
			break;
		}
		n = n*10 + tmp;
		str++;
	}
	return sign>0 ? n : -n;
}

int main()
{
	char str[] = "-1234567890123";
	cout << StrToInt(str) << endl;
	return 0;
}
