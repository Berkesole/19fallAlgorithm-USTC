#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
using namespace std;
#define inf 9999999

double Num_X[100000];//存储平面上所有的点的x坐标
double Num_Y[100000];//存储平面上所有的点的y坐标
int n;
double nearest_point_X[2];
double nearest_point_Y[2];//存储最近的点对
double nearest_distance = inf;//最近点对的距离
double middle_num;//横坐标中位数
double Local_MIN;//局部最小
double middle_X;//中位数坐标
double a_x[100000];
double a_y[100000];

int Enumerate(double Num_X[],double Num_Y[],int start,int end,double Local_MIN)
{
    for(int i=start; i<end; i++)
    {
        for(int j=i+1; j<end; j++)
        {
            if(sqrt(pow(Num_X[j]-Num_X[i],2)+pow(Num_Y[j]-Num_Y[i],2)) < Local_MIN)
            {
                Local_MIN = sqrt(pow(Num_X[j]-Num_X[i],2)+pow(Num_Y[j]-Num_Y[i],2));
                nearest_point_X[0] = Num_X[i];
                nearest_point_X[1] = Num_X[j];
                nearest_point_Y[0] = Num_Y[i];
                nearest_point_Y[1] = Num_Y[j];
            }
        }
    }
    return Local_MIN;
}

void Find_nearest_point()
{
    int tmp = 0;
    for(int i=0; i<n; i++)
    {
        if(middle_num - Local_MIN < Num_X[i] < middle_num + Local_MIN)
        {
            a_x[tmp] = Num_X[i];
            a_y[tmp] = Num_Y[i];
            tmp++;
        }
    }
    Enumerate(a_x,a_y,0, tmp, Local_MIN);
}

int partation(int left, int right)
{
    double key = Num_X[left];
    double tmp = Num_Y[left];
    while(left < right)
    {
        while(left<right && Num_X[right]>=key) right--;
        Num_X[left] = Num_X[right];
        Num_Y[left] = Num_Y[right];
        while(left<right && Num_X[left]<=key) left++;
        Num_X[right] = Num_X[left];
        Num_Y[right] = Num_Y[left];
    }
    Num_X[left] = key;
    Num_Y[left] = tmp;
    return left;
}

int partation_2(int left, int right)
{
    double key = Num_Y[left];
    double tmp = Num_X[left];
    while(left < right)
    {
        while(left<right && Num_Y[right]<=key) right--;
        Num_Y[left] = Num_Y[right];
        Num_X[left] = Num_X[right];
        while(left<right && Num_Y[left]>=key) left++;
        Num_Y[right] = Num_Y[left];
        Num_X[right] = Num_X[left];
    }
    Num_Y[left] = key;
    Num_X[left] = tmp;
    return left;
}

void quicksort(int flag, int p,int r)
{
    int q = 0;
    if(p < r)
    {
        if(flag == 0) q = partation(p, r);
        else q = partation_2(p, r);
        quicksort(flag,p,q-1);
        quicksort(flag,q+1,r);

    }
}

void Middle_Num()
{
    if (n % 2) middle_num = Num_X[(n-1)/2]; // 奇数情况
    else middle_num = (Num_X[n/2-1] + Num_X[n/2]) / 2; //偶数情况
    middle_X = (n-1)/2;
}

int main(int argc, const char * argv[])
{
//    scanf("%d",&n);
//    for(int i=0; i<n; i++) scanf("%lf %lf",&Num_X[i],&Num_Y[i]);
    ifstream file("/**YOUR PATH**/data.txt");
    int i = 0;
    file >> n;
    while(!file.eof()) {
        file >> Num_X[i];
        file >> Num_Y[i];
        i++;
    }
    quicksort(0,0,n-1);
    Middle_Num();
    Local_MIN = min(Enumerate(Num_X,Num_Y,0,middle_X,99999999),Enumerate(Num_X,Num_Y,middle_X,n-1,Local_MIN));
    quicksort(1,0, n-1);//按照y降序排列
    Find_nearest_point();
    cout << "Nearest_Distance = ";
    cout << sqrt(pow(nearest_point_X[0]-nearest_point_X[1],2)+pow(nearest_point_Y[0]-nearest_point_Y[1],2)) << endl;
    cout <<"(";
    cout << nearest_point_X[0];
    cout <<",";
    cout << nearest_point_Y[0];
    cout << ")<<==>>(";
    cout << nearest_point_X[1];
    cout <<",";
    cout << nearest_point_Y[1];
    cout <<")"<<endl;
    return 0;
}
