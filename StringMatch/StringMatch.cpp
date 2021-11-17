#include <iostream>
using namespace std;

//��ʽһ��Brute Froce
//SΪ���ַ�����TΪ���ַ���
//https://www.bilibili.com/video/av95949609
int BF(char* S, char* T)
{
	int i, j;
	i = 0;
	j = 0;
	//while����������
	// 1.�ִ�S�ַ���ĩβ��ȫ���Ƚ���ɣ������Ƿ�ƥ�䣬��������
	// 2.�ִ�T�ַ���ĩβ���ַ���ƥ��ɹ�����������
	while (T[j] != '\0' && S[i] != '\0')//'\0'Ϊ��ֹ����˵���������ַ�����ĩβ������û�е�S��ĩβ��Ҳû�е�T��ĩβ����ѭ������
	{
		if (T[j] == S[i])//��T��S�ڴ˴��ַ���ȣ�������Ƚ���һ���ַ�
		{
			j++;
			i++;
		}
		else//��T��S�ڴ˴��ַ�����ȣ���S�ַ������±���ݵ���һ�ֵ�����ַ�����һ���ַ�����T�ַ������±���ݵ����
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if(T[j] == '\0')//��T�ַ����ִ�ĩβ��˵��ƥ��ɹ�������ƥ���ַ�����S�е�����λ��
		return (i - j);
	return -1;
}

/*next�����ֵ��
�ҵ�ƥ��ʧ�ܵ�λ��index,����Ϊi��
��ô���ַ�����0��i-1�ĳ����е��ַ�����ǰ׺�ͺ�׺�ĳ���Ϊm,
��ônext[i] = m;

���ӣ�
�ַ��� char  S[]:ABCDABEABCDABD;
���ַ���char T[]:ABCDABD;
ƥ��ʧ�ܵ�λ��ΪT[6]
��ôT�ַ���0-5���ַ����ǰ׺���׺�ĳ���Ϊ2��ABΪ�ǰ׺���׺��
��ônext[6] = 2;*/
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
	//cout << "strlen(S)�ǣ�" << lengthS << endl;
	//cout << "strlen(T)�ǣ�" << lengthT << endl;
	getNext(T, next);

	//�˴����� S[i]!='\0' && T[j]!='\0' ,��Ϊj���ڵ���-1���������ʱT[j]�ᱨ��
	while (i != lengthS && j != lengthT)
	{
		//cout << "�����С�������" << endl;
		//cout << "S[i]�ǣ�" << S[i] << endl;
		//cout << "T[j]�ǣ�" << T[j] << endl;
	
		//�����һ���ַ���S[0]������T[0]��ƥ�䣬��j�����-1������������ʱ��j=0����i=1���Ա㽫�ַ���S��S[1]��ʼ��T�ȽϱȽ�
		if (j == -1 || S[i] == T[j])
		{
			i++;
			j++;
		}
		//��S[i]!=S[j],ʹj���ݵ�next[j]����Ϊnext[j]��λ�õ��ַ��ǵ�һ����Ҫ�ٴαȽϵ��ַ���
		/*���ӣ�
			  �ַ��� char  S[]:ABCDABEABCDABD;
			  ���ַ���char T[]:ABCDABD;
			  ƥ��ʧ�ܵ�λ��ΪT[6]
			  ��ôT�ַ���0-5���ַ����ǰ׺���׺�ĳ���Ϊ2��ABΪ�ǰ׺���׺��
			  ��ônext[6] = 2; 
		����ֱ�Ӵ�T[2]��ʼ��S[6]�����Ƚϣ�����Ҫ�Ƚ�T[0],T[1]����Ϊǰ׺���׺��һ���ģ����S[4],S[5]���ں�׺����ôS[4],S[5]Ҳ����T[0],T[1]*/
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

	cout << "���ҵ�ƥ���ַ�����ʼλ��Ϊ��" << BF(S, T) << endl;
	cout << "δ�ҵ�ƥ���ַ�������ֵ-1��" << BF(S, K) << endl;

	cout << "���ҵ�ƥ���ַ�����ʼλ��Ϊ��" << KMP(S, T, next) << endl;
	cout << "δ�ҵ�ƥ���ַ�������ֵ-1��" <<KMP(S, K, next) << endl;
	
}


