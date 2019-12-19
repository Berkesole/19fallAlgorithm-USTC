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

void Make_Graph(int start, Graph *G,int indptr[], int indices[])
{
    struct Node  *src = (Node*)malloc(sizeof(Node));
    src->color = White;
    src->distance = 0;
    src->ID = start;
    src->pre = G->nil;
    G->src = src;
//    for(int i = 1; i < V; i++)
//    {
//        Node *NEW_Node = (Node*)malloc(sizeof(Node));
//        NEW_Node->color = White;
//        NEW_Node->distance = infinite;
//        NEW_Node->pre = G->nil;
//    }
//
//    for(int i = 0; i < V; i++)
//    {
//        for(int j = 0; j < indptr[i+1]; j++)
//        {
//            Node *NEW_Node = (Node*)malloc(sizeof(Node));
//
//        }
//    }
    
}

void Print_Path(Graph *G, Node *s, Node *v, int end)
{
    if (v == G->src)
        cout << v->ID << " -> ";
    else if(v->pre == G->nil)
        cout << "No Path." << endl;
    else
    {
        Print_Path(G, s, v->pre, end);
        if (v->ID != end) cout << v->ID << " -> ";
        else cout << v->ID;
    }
}

void BFS(Graph *G, int end, int indptr[], int indices[])
{
    G->src->color = Gray;
    G->src->distance = 0;
    G->src->pre = G->nil;
    
    Node *u = (Node*)malloc(sizeof(Node));
    Queue *Q = (Queue*)malloc(sizeof(Queue));
    Initial_Queue(Q);
    ENQUEUE(Q, G->src);
    while(Q->head != Q->tail)
    {
        u = DEQUEUE(Q);
        
//        cout << u->ID << endl;
//        cout << u << endl;
        for (int i = indptr[u->ID]; i < indptr[u->ID+1]; i++)
        {
            Node *v = (Node*)malloc(sizeof(Node));
            v->ID = indices[i];
            v->color = Gray;
            v->distance++;
            v->pre = u;
            
            //cout << v->ID <<endl;
            ENQUEUE(Q, v);
            if(v->ID == end)
            {
                Print_Path(G, G->src, v, end);
                cout << "" << endl;
            }
        }
        u->color = Black;
    }
}

int main(int argc, const char * argv[]) {
    int indptr[V+1];
    int indices[E]; //value of indices is in [0,4096]
    int a,b = 0;
    int i = 0;
    memset(indptr, 0, sizeof(int)*(V+1));
    memset(indices, 0, sizeof(int)*E);
    ifstream file("/*YOUR PATH*//facebook_combined.txt");
    while (!file.eof())
    {
        file >> a;
        file >> b;
        indices[i] = b;
        i++;
        indptr[a+1] = indptr[a+1] + 1;
    }
    
    for(int i = 0; i < V+1; i++) indptr[i+1] = indptr[i+1] + indptr[i];
    
//    for(int i =0 ; i < 20; i++) cout << indptr[i] << " ";
//    cout << "" << endl;
//    for(int i = 0;i < 20; i++) cout << indices[i] << " ";
//    cout << "" <<endl;
//    cout << "last = " << indices[347] << endl;
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
    Make_Graph(start, G, indptr, indices); //构建图

    BFS(G,end,indptr,indices);
    return 0;
}


