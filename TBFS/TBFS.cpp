//
//  main.cpp
//  alg_TBFS
//
//  Created by 芮轲 on 2019/12/7.
//  Copyright © 2019 kerui. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;
#define V 4039
#define E 88234
#define White 0
#define Gray  1
#define Black 2
#define infinite 9999999

typedef struct Node{
    int color;
    struct Node *pre;
    int distance;
    int ID;
}Node;

typedef struct Graph{
    struct Node *src;
    struct Node *tar;
    struct Node *nil;
}Graph;

typedef struct Queue{
    Node *queue[4040];
    int head;
    int tail;
    int length;
}Queue;

void ENQUEUE(Queue *Q,Node *x)
{
    Q->queue[Q->tail] = x;
    if(Q->tail == Q->length)
        Q->tail = 1;
    else Q->tail = Q->tail + 1;
}

Node* DEQUEUE(Queue *Q)
{
    Node *x = Q->queue[Q->head];
    if(Q->head == Q->length)
        Q->head = 1;
    else Q->head = Q->head + 1;
    return x;
}

void Initial_Queue(Queue *Q)
{
    Q->head = 1;
    Q->tail = 1;
    Q->length = 4039;
}

void Make_Graph(int start, int end, Graph *G,int indptr[], int indices[])
{
    struct Node  *src = (Node*)malloc(sizeof(Node));
    struct Node  *tar = (Node*)malloc(sizeof(Node));
    src->color = White;
    src->distance = infinite;
    src->ID = start;
    src->pre = G->nil;
    tar->color = White;
    tar->distance = infinite;
    tar->ID = end;
    tar->pre = G->nil;
    G->src = src;
    G->tar = tar;
}

void Print_Path(Graph *G, Node *v, int end)
{
    if (v == G->src)
        cout << v->ID << " -> ";
    else if(v->pre == G->nil)
        cout << "No Path." << endl;
    else
    {
        Print_Path(G, v->pre, end);
        if (v->ID != end) cout << v->ID << " -> ";
        else cout << v->ID;
    }
}

void Print_Path1(Graph *G, Node *v)
{
    Node *temp = v->pre;
    while(temp != G->nil)
    {
        if (temp->ID != G->tar->ID) cout << temp->ID << " -> ";
        else cout << temp->ID;
        temp = temp->pre;
    }
}

//void BFS(Graph *G, int end, int indptr[], int indices[])
//{
//    G->src->color = Gray;
//    G->src->distance = 0;
//    G->src->pre = G->nil;
//
//    Node *u = (Node*)malloc(sizeof(Node));
//    Queue *Q = (Queue*)malloc(sizeof(Queue));
//    Initial_Queue(Q);
//    ENQUEUE(Q, G->src);
//    while(Q->head != Q->tail)
//    {
//        u = DEQUEUE(Q);
//
//        for (int i = indptr[u->ID]; i < indptr[u->ID+1]; i++)
//        {
//            Node *v = (Node*)malloc(sizeof(Node));
//            v->ID = indices[i];
//            v->color = Gray;
//            v->distance++;
//            v->pre = u;
//
//            //cout << v->ID <<endl;
//            ENQUEUE(Q, v);
//            if(v->ID == end)
//            {
//                Print_Path(G, G->src, v, end);
//                cout << "" << endl;
//            }
//        }
//        u->color = Black;
//    }
//}

void TBFS(Graph *G, int start, int end, int indptr[], int indices[])
{
    G->src->color = Gray;
    G->src->distance = 0;
    G->src->pre = G->nil;
    G->tar->color = Gray;
    G->tar->distance = 0;
    G->tar->pre = G->nil;
    
    Node *u1 = (Node*)malloc(sizeof(Node));
    Node *u2 = (Node*)malloc(sizeof(Node));
    Queue *Q1 = (Queue*)malloc(sizeof(Queue));
    Queue *Q2 = (Queue*)malloc(sizeof(Queue));
    Initial_Queue(Q1);
    Initial_Queue(Q2);
    ENQUEUE(Q1, G->src);
    ENQUEUE(Q2, G->tar);
    while(Q1->head != Q1->tail && Q2->head != Q2->tail)
    {
        u1 = DEQUEUE(Q1);
        u2 = DEQUEUE(Q2);
        
        for (int i = indptr[u1->ID]; i < indptr[u1->ID+1]; i++)
        {
            Node *v = (Node*)malloc(sizeof(Node));
            v->ID = indices[i];
            v->color = Gray;
            v->distance++;
            v->pre = u1;
            ENQUEUE(Q1, v);
        }
        u1->color = Black;
        for (int i = indptr[u2->ID]; i < indptr[u2->ID+1]; i++)
        {
            Node *v = (Node*)malloc(sizeof(Node));
            v->ID = indices[i];
            v->color = Gray;
            v->distance++;
            v->pre = u2;
            ENQUEUE(Q2, v);
            for(int j = Q1->head; j < Q1->tail; j++)
            {
                if(Q1->queue[j]->ID == v->ID)
                {
                    Print_Path(G, Q1->queue[j], v->ID);
                    cout << " -> ";
                    Print_Path1(G, v);
                    cout << "" <<endl;
                }
            }
            u2->color = Black;
        }
    }
    
}

int main(int argc, const char * argv[]) {
    int indptr[V+1];
    int indices[E]; //value of indices is in [0,4096]
    int a,b = 0;
    int i = 0;
    memset(indptr, 0, sizeof(int)*(V+1));
    memset(indices, 0, sizeof(int)*E);
    ifstream file("xxx/facebook_combined.txt");
    while (!file.eof())
    {
        file >> a;
        file >> b;
        indices[i] = b;
        i++;
        indptr[a+1] = indptr[a+1] + 1;
    }
    
    for(int i = 0; i < V+1; i++) indptr[i+1] = indptr[i+1] + indptr[i];
    
    struct Graph *G = (Graph*)malloc(sizeof(Graph));
    struct Node  *NIL = (Node*)malloc(sizeof(Node));
    NIL->color = NULL;
    NIL->pre = NULL;
    NIL->ID = NULL;
    NIL->distance = NULL;
    G->nil = NIL;

    /*initial src*/
    int start = 0;
    int end = 0;
    cin >> start;
    cin >> end;
    Make_Graph(start, end, G, indptr, indices); //构建图
    //BFS(G,end,indptr,indices);
    TBFS(G, start, end, indptr, indices);
    return 0;
}


