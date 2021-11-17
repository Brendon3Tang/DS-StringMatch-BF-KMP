#include <iostream>
using namespace std;

//方式一：Brute Froce
//S为主字符串，T为子字符串
//https://www.bilibili.com/video/av95949609
int BF(char* S, char* T)
{
	int i, j;
	i = 0;
	j = 0;
	//while结束条件：
	// 1.抵达S字符串末尾（全部比较完成，不论是否匹配，结束程序）
	// 2.抵达T字符串末尾（字符串匹配成功，结束程序）
	while (T[j] != '\0' && S[i] != '\0')//'\0'为终止符，说明到达了字符串的末尾。若既没有到S串末尾，也没有到T串末尾，则循环继续
	{
		if (T[j] == S[i])//若T与S在此处字符相等，则继续比较下一个字符
		{
			j++;
			i++;
		}
		else//若T与S在此处字符不相等，将S字符串的下标回溯到上一轮的起点字符的下一个字符。将T字符串的下标回溯到起点
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if(T[j] == '\0')//若T字符串抵达末尾，说明匹配成功，返回匹配字符段在S中的起点的位置
		return (i - j);
	return -1;
}

/*next数组的值：
找到匹配失败的位置index,假设为i。
那么子字符串中0到i-1的长度中的字符如果最长前缀和后缀的长度为m,
那么next[i] = m;

例子：
字符串 char  S[]:ABCDABEABCDABD;
子字符串char T[]:ABCDABD;
匹配失败的位置为T[6]
那么T字符串0-5的字符中最长前缀与后缀的长度为2（AB为最长前缀与后缀）
那么next[6] = 2;*/
//https://www.bilibili.com/video/av96661990
void getNext(char* T, int* next)
{
	int i = -1, j = 0;
	int lengthT = sizeof(T);
	next[0] = -1;

	while (j < lengthT)
	{
		if (i == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[j] = i;
		}
		else
		{
			i = next[i];
		}
	}
}

//https://www.bilibili.com/video/av96254929
int KMP(char* S, char* T, int* next)
{
	int i = 0, j = 0;
	int lengthS = strlen(S), lengthT = strlen(T);
	//cout << "strlen(S)是：" << lengthS << endl;
	//cout << "strlen(T)是：" << lengthT << endl;
	getNext(T, next);

	//此处不用 S[i]!='\0' && T[j]!='\0' ,因为j存在等于-1的情况，此时T[j]会报错
	while (i != lengthS && j != lengthT)
	{
		//cout << "运行中。。。。" << endl;
		//cout << "S[i]是：" << S[i] << endl;
		//cout << "T[j]是：" << T[j] << endl;
	
		//假设第一个字符（S[0]）就与T[0]不匹配，则j会等于-1。当继续运行时，j=0，而i=1，以便将字符串S从S[1]开始与T比较比较
		if (j == -1 || S[i] == T[j])
		{
			i++;
			j++;
		}
		//若S[i]!=S[j],使j回溯到next[j]，因为next[j]的位置的字符是第一个需要再次比较的字符：
		/*例子：
			  字符串 char  S[]:ABCDABEABCDABD;
			  子字符串char T[]:ABCDABD;
			  匹配失败的位置为T[6]
			  那么T字符串0-5的字符中最长前缀与后缀的长度为2（AB为最长前缀与后缀）
			  那么next[6] = 2; 
		可以直接从T[2]开始与S[6]继续比较，不需要比较T[0],T[1]，因为前缀与后缀是一样的，如果S[4],S[5]等于后缀，那么S[4],S[5]也等于T[0],T[1]*/
		else	
		{
			j = next[j];
		}
	}

	if (j == lengthT)
		return (i - j);
	return -1;
}

int main()
{
	char S[10] = {'a','b','c','d','a','e','f','g','a','\0'};
	char T[6] = { 'c','d','a','e','f','\0'};
	char K[6] = { 'a','c','s','f','q','\0' };
	int next[6] = { 0,0,0,0,0,0 };
	int start = 0;

	cout << "已找到匹配字符！起始位置为：" << BF(S, T) << endl;
	cout << "未找到匹配字符，返回值-1：" << BF(S, K) << endl;

	cout << "已找到匹配字符！起始位置为：" << KMP(S, T, next) << endl;
	cout << "未找到匹配字符，返回值-1：" <<KMP(S, K, next) << endl;
	
}


