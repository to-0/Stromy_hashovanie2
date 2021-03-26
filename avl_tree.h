//
// Created by tomas on 26. 3. 2021.
//

#ifndef TEST2_AVL_TREE_H
#define TEST2_AVL_TREE_H

#endif //TEST2_AVL_TREE_H
struct Node
{
    int key;
    int height;
    char app_name[50];
    char name[50];
    char email[150];
    struct Node* left;
    struct Node* right;
};
struct Node* NewNode(int data);
int max(int a,int b);
int height(struct Node* node);
int Balance(struct Node* node);
struct Node* LeftRotate(struct Node* z);
struct Node* RightRotate(struct Node* z);
struct Node* FindMin(struct Node* node);
struct Node* Delete(struct Node* root, int data);
struct Node* Insert(struct Node* root, struct Node *n);

//doimplementoval som
void preorder_avl(struct Node *n);
struct Node *search_avl(int key, struct Node *cur);