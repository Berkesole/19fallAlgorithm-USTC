//
//  main.cpp
//  alg_sch2_2
//
//  Created by 芮轲 on 2019/11/2.
//  Copyright © 2019 kerui. All rights reserved.
//

#include <iostream>
#include "stdio.h"
#include <fstream>
using namespace std;

int n,k;
int Time[100],Machine_Sum_Time[100];
int Task_allo[100];
int MIN_TIME = 9999999;
int Task_allo_tmp[100];

//int OK(int task)
//{
//    for(int i=0; i<task; i++)
//    {
//        if(Task_allo_tmp[i] == Task_allo_tmp[task]) return 0;
//    }
//    return 1;
//}

void FIND_DFS(int task,int Local_MIN){
   // cout << 1 << endl;
    if(Local_MIN> MIN_TIME) return; //如果加上task就比当前最小的时间大，那么可以直接把这个结点变成死结点（分支限界）
    if(task == n)
    {
        if(Local_MIN < MIN_TIME)
        {
            MIN_TIME = Local_MIN;//如果局部最小比全局最优情况要好，那么更新它
            for(int i=0; i<n; i++)
            {
                Task_allo[i] = Task_allo_tmp[i];
            }
        }
            return;
    }
    for (int i=0; i<k; i++)//枚举每一个机器，为其分配任务
    {
        if(Machine_Sum_Time[i] + Time[task] < MIN_TIME) //如果加上task就比当前最小的时间大，那么可以直接把这个结点变成死结点（分支限界）,跳过
        {
            Machine_Sum_Time[i] += Time[task];
            Task_allo_tmp[task] = i;// 让task入机器i的工作队列
            //cout << Local_MIN << endl;
            FIND_DFS(task+1, max(Machine_Sum_Time[i],Local_MIN));
            //递归继续分配第task+1个任务，此时更新局部最小的时间应该是最后结束的那个机器的时间
            Machine_Sum_Time[i] -= Time[task];
            //Task_allo[i][task] = 0;
        }
    }
}

int main(int argc, const char * argv[])
{
    ifstream file("/Users/ruike/C_project/alg_sch2_2/alg_sch2_2/data.txt");
    int i = 0;
    file >> n;
    file >> k;
    while(!file.eof()) {
        file >> Time[i];
        i++;
    }
    //scanf("%d%d",&n,&k);
    for(int i=0; i < n; i++)
    {
        //scanf("%d",&Time[i]);
        Machine_Sum_Time[i] = 0;
    }
    for(int i=0; i < 100; i++)
    {
        Task_allo[i] = 0;
    }
    FIND_DFS(0,0);
    cout << MIN_TIME << endl;
    for(int i=0; i<n; i++)
    {
        printf("Task %d分配给机器 %d\n",i+1,Task_allo[i]+1);
    }
    return 0;
}


