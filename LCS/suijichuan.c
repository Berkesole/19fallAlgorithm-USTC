#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int STR_LEN;

void GenerateStr()
{
    char str[STR_LEN + 1] ;
    int i,flag;
     
    srand(time(NULL));//通过时间函数设置随机数种子，使得每次运行结果随机。
    for(i = 0; i < STR_LEN; i ++)
    {
		flag = rand()%3;
		switch(flag)
		{
		case 0:
			str[i] = rand()%26 + 'a'; 
			break;
		case 1:
			str[i] = rand()%26 + 'A'; 
			break;
		case 2:
			str[i] = rand()%10 + '0'; 
			break;
		}
    }
    for(i = 0; i < STR_LEN; i ++){
        printf("%c", str[i]);//输出生成的随机数。
    }
     
}

int main(){
    scanf ("%d",&STR_LEN);
	GenerateStr();
}
