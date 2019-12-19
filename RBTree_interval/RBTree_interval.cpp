#include <iostream>
using namespace std;

#define Black 0
#define Red   1

typedef struct NodeInt{
    int low;
    int high;
}NodeInt;

typedef struct RBTreeNode{
    int color;
    struct RBTreeNode* parent;
    struct RBTreeNode* left;
    struct RBTreeNode* right;
    struct NodeInt Int;
    int max;
}Node;

typedef struct RBTree{
    Node* root;
    Node* nil;
}Tree;


struct RBTreeNode* TREE_MINIMUM(Tree* T,Node* x){
    while(x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}

void Left_Rotate(Tree *T, Node *x)
{
    Node* y = (Node*)malloc(sizeof(Node));
    y = x->right;
    x->right = y->left;
    if(y->left != T->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->nil)
    {
        T->root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    
    /*维护max域*/
    y->max = x->max;
    x->max = max(x->Int.high,max(x->left->max,x->right->max));
}

void Right_Rotate(Tree *T, Node *y)
{
    Node* x = (Node*)malloc(sizeof(Node));
    x = y->left;
    y->left = x->right;
    if(x->right != T->nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == T->nil)
    {
        T->root = x;
    }
    else if(y == y->parent->left)
    {
        y->parent->left = x;
    }
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
    /*维护max域*/
    y->max = x->max;
    x->max = max(x->Int.high,max(x->left->max,x->right->max));
}

void RB_Insert_Fixup(Tree *T, Node *z)
{
    Node *y = (Node*)malloc(sizeof(Node));
    while(z->parent->color == Red)
    {
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == Red)
            {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else
            {
                if( z == z->parent->right)
                {
                    z = z->parent;
                    Left_Rotate(T, z);
                }
                z->parent->color = Black;
                z->parent->parent->color = Red;
                Right_Rotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if(y->color == Red)
            {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else
            {
                if( z == z->parent->left)
                {
                    z = z->parent;
                    Right_Rotate(T, z);
                }
                z->parent->color = Black;
                z->parent->parent->color = Red;
                Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = Black;
}

void RB_Insert(Tree* T, Node *z)
{
    Node *y = (Node*)malloc(sizeof(Node));
    Node *x = (Node*)malloc(sizeof(Node));
    y = T->nil;
    x = T->root;
    while(x != T->nil)
    {
        y = x;
        if(z->Int.low < x->Int.low)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == T->nil)
        T->root = z;
    else if(z->Int.low < y->Int.low)
        y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = Red;
    z->max = max(z->Int.high,max(z->left->max,z->right->max));
    RB_Insert_Fixup(T,z);
    while(z->parent != T->nil)
    {
        z->parent->max = max(z->parent->max,z->max);
        z = z->parent;
    }
}

void RB_Transplant(Tree *T, Node *u, Node *v)
{
    if(u->parent == T->nil)
        T->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void RB_Delete_Fixup(Tree* T, Node* x){
    Node* w = (Node*)malloc(sizeof(Node));
    while(x != T->root && x->color == Black)
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;
            if(w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;
                Left_Rotate(T, x->parent);
                w = x->parent->right;
            }
            if(w->left->color == Black && w->right->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                if(w->right->color == Black)
                {
                    w->left->color = Black;
                    w->color = Red;
                    Right_Rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = Black;
                w->right->color = Black;
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            w = x->parent->left;
            if(w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;
                Right_Rotate(T, x->parent);
                w = x->parent->left;
            }
            if(w->left->color == Black && w->right->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                if(w->left->color == Black)
                {
                    w->right->color = Black;
                    w->color = Red;
                    Left_Rotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = Black;
                w->left->color = Black;
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = Black;
}

int RB_Delete(Tree* T, Node* z){
    Node* y = (Node*)malloc(sizeof(Node));
    Node* x = (Node*)malloc(sizeof(Node));
    
    y = z;

    int y_original_color = y->color;
    if(z->left == T->nil)
    {
        x = z->right;
        RB_Transplant(T,z,z->right);
    }
    else if(z->right == T->nil)
    {
        x = z->left;
        RB_Transplant(T,z,z->left);
    }
    else
    {
        y = TREE_MINIMUM(T, z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else
        {
            RB_Transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_original_color == Black)
    {
        RB_Delete_Fixup(T,x);
    }
    return 0;
}


struct RBTreeNode* Interval_search(Tree *T,int a, int b)
{
    Node *x = (Node*)malloc(sizeof(Node));
    x = T->root;
    while( x!= T->nil && (a > x->Int.high || b < x->Int.low))
    {
        if(x->left != T->nil && x->left->max >= a)
            x = x->left;
        else x = x->right;
    }
    return x;
}


int main(int argc, const char * argv[]) {
    struct RBTree* T = (Tree*)malloc(sizeof(Tree));
    struct RBTreeNode* nil = (Node*)malloc(sizeof(Node));
    nil->color = Black;
    nil->Int.low = NULL;
    nil->Int.high = NULL;
    nil->max = 0;
    T->nil = nil;
    T->root = T->nil;
    T->root->parent = T->nil;
    
    int a[10] = {0,6,150,5,8,16,19,17,26,25};
    int b[10] = {3,10,8,23,9,21,20,19,26,30};
    
    for(int i = 0; i < 10; i++)
    {
        struct RBTreeNode* z = (Node*)malloc(sizeof(Node));
        z->Int.low = a[i];
        z->Int.high = b[i];
        RB_Insert(T, z);
    }
    
    /*删除结点*/
    int start;
    cin >> start;
    int end;
    cin >> end;
    Node *x = Interval_search(T, start, end);
    if (x != T->nil)
    {
        RB_Delete(T, x);
        cout << "[" << x->Int.low << "," << x->Int.high << "] which max is "  << x->max << " is deleted." << endl;
    }
    else
        cout << "Can Not Find The Target Node." << endl;
    return 0;
}
