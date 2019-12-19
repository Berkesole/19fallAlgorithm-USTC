#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#define d 256
#define PRIME 127

void RABIN_KARP_MATCHER(char *T, char *P, int q)
{
    assert( T && P && q > 0);
    int M = (int)strlen(P);
    int N = (int)strlen(T);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    
    for( i = 0; i < M - 1; i++) h = ( h * d ) % q;
    for( i = 0; i < M; i++ )
    {
        p = ( d * p + P[i] ) % q;
        t = ( d * t + T[i] ) % q;
    }
    for( i = 0; i <= N - M; i++)
    {
        if( p == t)
        {
            for( j = 0; j < M; j++)
                if(T[i+j] != P[j])
                    break;
            if( j == M )
                cout<<"匹配字符串出现的起始位置为"<<i<<endl;
        }
        if( i < N - M )
        {
            t = ( d * ( t - T[i] * h ) + T[i + M] ) % q;
            if( t < 0 ) t += q;
        }
    }
}

int main(int argc, char* argv[])
{
    int n = pow(2,14);
    char T[n];
    char P[40];
    int i = 0;
    ifstream file("/Users/ruike/C_project/alg_3_2/alg_3_2/T.txt");
    while(!file.eof()) {
        file >> T[i];
        i++;
    }
    i = 0;
    ifstream file2("/Users/ruike/C_project/alg_3_2/alg_3_2/P.txt");
    while(!file2.eof()) {
        file2 >> P[i];
        i++;
    }
    RABIN_KARP_MATCHER(T, P, 127);
    return 0;
}
