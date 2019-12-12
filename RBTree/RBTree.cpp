//
//  main.cpp
//  alg_4_RBtree
//
//  Created by 芮轲 on 2019/11/29.
//  Copyright © 2019 kerui. All rights reserved.
//

#include <iostream>
using namespace std;

#define Black 0
#define Red   1

int cnt = 0;

typedef struct RBTreeNode{
    int color;
    struct RBTreeNode* parent;
    struct RBTreeNode* left;
    struct RBTreeNode* right;
    int key;
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
    //cout << z->key << endl;
    while(x != T->nil)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == T->nil)
        T->root = z;
    else if(z->key < y->key)
        y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = Red;
    RB_Insert_Fixup(T,z);
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

void RB_Delete(Tree* T, Node* z){
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
}

void preOrderTraversel(Tree *T,Node *x)
{
    if(x != T->nil)
    {
        //b[i] = x->key;
        //cout << x->key << " ";
        preOrderTraversel(T, x->left);
        cout << x->key << "," << x->key << "<-" << x->left->key << "," << x->key << "->" << x->right->key <<endl;
        //cout << "# ";
        preOrderTraversel(T, x->right);
        //cout << "# ";
    }
}

void SearchNNodeAndDelete(Tree *T,Node *tmp,Node *x,int n)
{
    if(tmp != T->nil)
    {
        SearchNNodeAndDelete(T,tmp->left,x,n);
        cnt++;
        if(cnt == n)
        {
            cout << "The Node which key is " << tmp->key << " is deleted." << endl;
            x = tmp;
            RB_Delete(T, x);
        }
        SearchNNodeAndDelete(T,tmp->right,x,n);
    }
}

int main(int argc, const char * argv[]) {
    struct RBTree* T = (Tree*)malloc(sizeof(Tree));
    struct RBTreeNode* nil = (Node*)malloc(sizeof(Node));
    
//    nil->color = Black;
//    nil->left = T->root;
    nil->right = T->root;
    nil->key = NULL;
    T->nil = nil;
    T->root = T->nil;
    T->root->parent = T->nil;
    
    int a[20] = {26,17,410,14,21,30,47,10,16,19,23,28,38,7,12,15,20,35,39,3};
    //int a[10] = {0,6,15,5,8,16,19,17,26,25};
//    for(int i = 0 ; i<20; i++) cout<<a[i]<<endl;
    for(int i=0; i<20; i++)
    {
        struct RBTreeNode* z = (Node*)malloc(sizeof(Node));
        z->key = a[i];
        RB_Insert(T, z);
//        preOrderTraversel(T, T->root);
//        cout << T->root->key << endl;
//        cout << "****Insert over****" <<endl;
    }
//    int b[20] = {0};
    preOrderTraversel(T,T->root);
//    cout<<endl;
    
//    int n = 0;
//    cin >> n;
//    struct RBTreeNode *x = (Node*)malloc(sizeof(Node));
//    SearchNNodeAndDelete(T,T->root,x,n);
    return 0;
}
