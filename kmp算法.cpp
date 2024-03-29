#include <iostream>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define MAXSTRLEN 255//串的初始长度 

typedef char SString[MAXSTRLEN+1];//0号单元存放串的长度 
typedef int Status;

void get_next(SString T,Status next[]);
Status StrAssign(SString T,char *chars);
void StrPrint(SString T);

int Index_KMP(SString S,SString T,Status pos);//改进版 
void get_nextval(SString T,Status nextval[]);//改进next数组函数版 


int main(int argc, char** argv) 
{
	char s[256],t[256];
	Status pos;
	SString S,T;
	
	printf("请输入字符串S：\n");
	gets(s);
	StrAssign(S,s);
//	printf("输出字符串S：\n");
//	StrPrint(S); 
	
	printf("请输入字符串T：\n"); 
	gets(t);
	StrAssign(T,t);
//	printf("输出字符串T：\n");
//	StrPrint(T);
	
	printf("请输入位置(第pos个字符之后):\n");
	scanf("%d",&pos);
	printf("模式串T在主串S的位置为%d\n",Index_KMP(S,T,pos));
	
/*	printf("请输入串T:\n");
	gets(s);
	StrAssign(T,s);
	
	int next[100];
//	ababaaababaa
	get_nextval(T,next);
	for(int i=1;i<=13;i++){
		printf("%d ",next[i]);
	}*/
	return 0;
}

Status StrAssign(SString T,char *chars)
{
	//生成一个其值等于chars的串T
	Status i;
	if(strlen(T)>MAXSTRLEN)
	{
		return ERROR;
	} 
	else
	{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++)
		{
			T[i]=*(chars+i-1);
		}
		return OK;
	}
} 
void StrPrint(SString T)
{
	//输出字符串T
	Status i;
	printf("%d ",T[0]);
	for(i=1;i<=T[0];i++)
	{
		printf("%c",T[i]);
	} 
	printf("\n");
}

int Index_KMP(SString S,SString T,Status pos)
{
	//利用模式算T的next数组函数求T在主串S中的第pos个字符之后的位置
	int nextval[100];
	int i=pos,j=1;
	get_nextval(T,nextval);
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j])//继续比较后继字符模式串向右移动 
		{
			++i;
			++j;
		}
		else
			j=nextval[j]; 
	} 
	if(j>T[0])
		return i-T[0];
	else
		return ERROR;
} 

void get_nextval(SString T,Status nextval[])//改进next数组函数版 
{
	//求模式串的T的next函数修正值并存入数组nextval中
	Status i=1,j; 
	nextval[1]=0;
	j=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			if(T[i]!=T[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}
		else
			j=nextval[j];
	}
}

