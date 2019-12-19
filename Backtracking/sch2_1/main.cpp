#include <iostream>
#include "stdio.h"
#define inf 9999999
using namespace std;

int n;
int cost[100][100];
int Task_Alloc[100];
int MIN_COST = inf;
int s[100];
//int TMP_COST = 0;
int Greedy_Cost = 0;
int Task_Alloc_Tmp[100];

int OK(int task)
{
    for(int i=0; i<task; i++)
    {
        if(Task_Alloc_Tmp[i] == Task_Alloc_Tmp[task]) return 0;
    }
    return 1;
}

void BackTracking(int Local_MIN, int task)
{
    if(task == n)
    {
        if(Local_MIN < MIN_COST)
        {
            MIN_COST = Local_MIN;
            for(int i=0; i<n; i++) Task_Alloc[i] = Task_Alloc_Tmp[i];
        }
            return;
    }
    
    for(int i=0; i<n; i++)
    {
        if(Local_MIN + cost[task][i] <= Greedy_Cost)
        {
            Local_MIN += cost[task][i];
            Task_Alloc_Tmp[task] = i; //把第task个工作分配给第i个人
            if (OK(task))
            {
                BackTracking(min(Greedy_Cost,Local_MIN), task+1);
            }
            Local_MIN -= cost[task][i];
        }
    }
}

void Greedy()
{
    int min_cost_people = 0;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (cost[i][min_cost_people] > cost[i][j] && s[j] != 0)
            {
                min_cost_people = j;
                s[j] = 1;
            }
        }
        Task_Alloc[i] = min_cost_people;
    }
    for(int i=0; i<n; i++) Greedy_Cost += cost[i][Task_Alloc[i]]; //用一次贪心算出来的最小值，但这个值还不一定是全局最优
}


int main(int argc, const char * argv[])
{
    scanf("%d",&n);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++) scanf("%d",&cost[i][j]);
    }
    for(int i = 0; i<100; i++)
    {
        Task_Alloc[i] = inf;
        s[i] = 0;
    }
    Greedy();
    BackTracking(0, 0);
    cout << MIN_COST << endl;
    for(int i=0; i<n; i++)
    {
        printf("第%d个工作由%d来做\n",i+1,Task_Alloc[i]+1);
    }
    return 0;
}
