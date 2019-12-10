//
//  main.cpp
//  alg_3
//
//  Created by 芮轲 on 2019/11/20.
//  Copyright © 2019 kerui. All rights reserved.
/*1.求解两个字符串s1,s2的最长公共子序列。 s1，s2均是随机生成的字符(大、小写字母和数字，共62种不同字符)。
n,m的规模分别为2^6,2^8 */

#include <iostream>
#include <math.h>
#include <fstream>
#define upperleft 0
#define left 1
#define above 2
#define n  2*2*2*2*2*2
#define m  2*2*2*2*2*2*2*2

using namespace std;
//const int n = pow(2,6);

int b[n][m];
int c[n][m];

void LCS_LENGTH(char X[], char Y[], int p, int q)
{
    for (int i = 1; i < n; i++)
    {
        c[i][0] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        c[0][i] = 0;
    }
    
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            if (X[i] == Y[j])
            {
                c[i+1][j+1] = c[i][j] + 1;
                b[i+1][j+1] = upperleft;
            }
            else if (c[i][j+1] >= c[i+1][j])
            {
                c[i+1][j+1] = c[i][j+1];
                b[i+1][j+1] = above;
            }
            else
            {
                c[i+1][j+1] = c[i+1][j];
                b[i+1][j+1] = left;
            }
        }
    }
}

void PRINT_LCS(char X[], int i, int j)
{
    if (i == 0 || j == 0)
    {
        return;
    }
    if (b[i][j] == upperleft)
    {
        PRINT_LCS(X, i - 1, j - 1);
        cout << X[i-1];
    }
    else if (b[i][j] == above) PRINT_LCS(X, i - 1, j);
    else PRINT_LCS(X, i, j - 1);
}

int main(int argc, const char * argv[]){
    char X[n];
    char Y[m];
    int i = 0;
    ifstream file("/Users/ruike/C_project/alg_3/alg_3/XXX.txt");
    while(!file.eof()) {
        file >> X[i];
        i++;
    }
    i = 0;
    ifstream file2("/Users/ruike/C_project/alg_3/alg_3/YYY.txt");
    while(!file2.eof()) {
        file2 >> Y[i];
        i++;
    }
//    cout << strlen(X)<<","<<strlen(Y)<<endl;
    LCS_LENGTH(X, Y, (int)strlen(X),(int)strlen(Y));
//    for (int i=1; i <= strlen(X); i++)
//    {
//        for (int j=1 ;j<=strlen(Y); j++)
//        {
//            cout << b[i][j]<<",";
//        }
//        cout<<""<<endl;
//    }
    PRINT_LCS(X, (int)strlen(X), (int)strlen(Y));
    cout<<""<<endl;
    return 0;
}
