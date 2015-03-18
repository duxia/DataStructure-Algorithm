//============================================================================
// Name        : 字符串包含
// Author      : coffee
// Version     :
// Copyright   : Copyright ©2015 sweet coffee.All right reserved.
// Description : From July Coding
//============================================================================

#include <iostream>
#include<algorithm>
#include <string>
using namespace std;
// 普通方法
bool StringContain_simple(string &str1,string &str2)
{
	int count=0;
	for(int i=0;i<str2.length();i++)
		for(int j=0;j<str1.length();j++)
			if(str2[i]==str1[j]) {
				count++;
				break;
			}
	if(count==str2.length())
		return true;
	return false;
}
// 排序法
bool StringContain_sort(string &str1,string &str2)
{
	sort(str1.begin(),str1.end());
	sort(str2.begin(),str2.end());
	int i,j;
	for(i=0,j=0;i<str1.length();i++)
		if(str1[i]==str2[j])
			j++;
	if(j<str2.length())
		return false;
	return true;
}
//类hashtable方法
bool StringContain_hash(string &str1,string &str2)
{
	int hash=0;
	for(int i=0;i<str1.length();i++)
		hash |= (1<<(str1[i]-'A'));
	for(int i=0;i<str2.length();i++)
		if((hash & (1<<(str2[i]-'A'))) == 0)
			return false;
	return true;
}
int main() {
	string str1="ABCD";
	string str2="BAE";
	cout << StringContain_hash(str1,str2) << endl;
	return 0;
}
