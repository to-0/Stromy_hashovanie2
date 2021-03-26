//
// Created by tomas on 26. 3. 2021.
//

#ifndef TEST2_SPLAY_TREE_H
#define TEST2_SPLAY_TREE_H

#endif //TEST2_SPLAY_TREE_H
typedef struct node{
    int key;
    char name[50];
    char app_name[50];
    char email[150];
    struct node *left;
    struct node *right;
    struct node *parent;
}NODE;
NODE *root;
void preorder(NODE *N);
void rotate_right(NODE **n);
void rotate_left(NODE **n);
NODE *splay(NODE **n);
NODE *search(int key, NODE *cur);
void insert(NODE *cur, NODE **n);
NODE *generate();