//
// Created by tomas on 20. 3. 2021.
//

#include "splay_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*typedef struct node{
    int key;
    char name[50];
    char app_name[50];
    char email[50];
    struct node *left;
    struct node *right;
    struct node *parent;
}NODE;*/
NODE *root = NULL;

void preorder(NODE *n){
    if(n!=NULL){
        putchar('(');
    }
    if(n==NULL){
        printf("()");
        return;
    }
    printf("%d",n->key);
    putchar(' ');
    preorder(n->left);
    putchar(',');
    preorder(n->right);
    putchar(')');
}


void rotate_right(NODE **n){ //otacam okolo n
    NODE *left_child = (*n)->left; //zoberiem childa
    NODE *child_right = left_child->right;
    NODE *temp = *n; //ulozim si aj n podla ktoreho idem rotovat
    *n = left_child; //childa posuniem hore
    (*n)->parent = temp->parent;
    (*n)->right  = temp; //parenta doprava
    temp->left =  child_right; //na lavu stranu parenta napojim to co mal child  napravo
    if(child_right != NULL){ //este musim prepojit aj podstrom childa ktory tiez priradim
        child_right->parent = temp;
    }
    if(temp->parent!=NULL){ //ak ten node predtym mal nejakeho rodica, musim este z toho rodica napojit
        if(temp->key < temp->parent->key){
            temp->parent->left = *n;
        }
        else temp->parent->right = *n;
    }
    temp->parent = *n;
}
void rotate_left(NODE **n){ //otacam okolo
    NODE *right_child = (*n)->right; //zoberiem   praveho childa
    NODE *child_left = right_child->left; // ulozim si jeho lavu cast
    NODE *temp = *n; //ulozim si aj n podla ktoreho idem rotovat
    *n = right_child; //childa posuniem hore namiesto n
    (*n)->parent = temp->parent; //nastavim jeho parenta na parenta toho za ktoreho som ho vymenil
    (*n)->left  = temp; //predosle n hodim doprava, to bol ten predosly parent
    temp->right = child_left;
    if(child_left!=NULL){
        child_left->parent = temp;
    }
    if(temp->parent!=NULL){ //ak ten node predtym mal nejakeho rodica, musim este z toho rodica napojit
        if(temp->key < temp->parent->key){
            temp->parent->left = *n;
        }
        else temp->parent->right = *n;
    }
    temp->parent = *n; //nastavim jeho parenta na nove n
}
NODE *splay(NODE **n){
    //printf("Idem splayovat: %d\n",(*n)->key);
    while((*n)->parent!=NULL){
        NODE *parent;
        parent = (*n)->parent;
        if(parent->parent == NULL){ //mam iba jedneho parenta
            //printf("Ma iba jedneho parenta a to:%d\n",(*n)->parent->key);
            if(parent->key > (*n)->key){ //moj node je nalavo od parenta cize tocim doprava
                rotate_right(&parent);
            }
            else rotate_left(&parent);
        }
        else{ //mam parenta aj grandparenta
            NODE *grandparent = parent->parent;
            //printf("Mam parenta:%d aj grandparenta: %d\n",parent->key,grandparent->key);
            if(parent->key > (*n)->key && grandparent->key > parent->key){ // takato ciara /, node n je uplne vlavo
                //printf("2x prava rotacia\n");
                // printf("\n prva rotacia \n");
                rotate_right(&grandparent);
                //preorder(root);
                rotate_right(&parent);
                //printf("\n druha rotacia \n");
                //preorder(root);
            }
            else if(parent->key < (*n)->key && grandparent->key < parent->key)//takato ciara \ , node n je uplne vpravo
            {
                //printf("2x lava rotacia\n");
                //najprv podla grandparenta aby som parenta dostal vyssie a potom az podla parenta tocim
                rotate_left(&grandparent);

                //printf("\n prva rotacia \n");
                //preorder(root);
                rotate_left(&parent);
                //printf("\n druha rotacia \n");
                //preorder(root);
            }
            else if(parent->key > (*n)->key && grandparent->key < parent->key){ //
                // printf("prava lava\n");
                //zacinam parentom lebo potom do druhej strany chcem tocit ako keby a potrebujem ten moj node mat vyssie
                rotate_right(&parent);
                //printf("\n prva rotacia \n");
                //preorder(root);
                rotate_left(&grandparent);
                //printf("\n druha rotacia \n");
                //preorder(root);
            }
            else if (parent->key < (*n)->key && grandparent->key> parent->key){
                // printf("lava prava\n");
                rotate_left(&parent);
                //printf("\n prva rotacia \n");
                //preorder(root);
                rotate_right(&grandparent);
                //printf("\n druha rotacia \n");
                //preorder(root);
            }
        }
    }
    root = *n;
}
NODE *search(int key,NODE *cur){
    if(cur!= NULL && cur->key!=key){
        if(cur->key > key) {
            if (cur->left == NULL) {
                printf("No element with key: %d\n", key);
                splay(&cur);
                return NULL;
            }
            search(key, cur->left);
        }
        else {
            if(cur->right == NULL){
                printf("No element with key: %d\n",key);
                splay(&cur);
                return NULL;
            }
            search(key,cur->right);
        }
    }
    else if(cur != NULL && cur->key==key){
        //printf("App name:%s  Last name:%s Email:%s  Key%d\n",cur->app_name,cur->name, cur->email,cur->key);
        splay(&cur);
        return cur;
    }
}
void insert(NODE *cur,NODE **n){
    if(root==NULL){
        root = *n;
        root->parent = NULL;
        return;
    }
    if(cur->key > (*n)->key){ // node je mensi ako sucasny cize idem smerom dolava
        if(cur->left ==NULL) {
            (*n)->parent = cur;
            cur->left = *n;
            splay(n);
        }
        else
            insert(cur->left,n);
    }
    else if(cur->key < (*n)->key){
        if(cur->right ==NULL){
            (*n)->parent = cur;
            cur->right = *n;
            splay(n);
        }
        else
            insert(cur->right,n);
    }
}

NODE *generate(){
    NODE *n;
    printf("Hello pred otvorenim");
    FILE *f = fopen("tree2.txt","r");
    printf("Hello");
    if (f==NULL) return NULL;
    char line[150];
    char temp[50];
    int key;
    while (fgets(line,150,f)!=NULL){
        n = (NODE *)malloc(sizeof(NODE));
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        sscanf(temp,"%d",&(n->key));
        //printf("KEy:%d\n",n->key);
        char temp_line[50];
        strncpy(temp_line,line+i+1,length-i);
        strncpy(line,line+i+1,length-i); //seknem subor pokracujem iba so zvyskom

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        sscanf(temp,"%s",n->app_name);
        strncpy(line,line+i+1,length-i);

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        sscanf(temp,"%s",n->name);
        strncpy(line,line+i+1,length-i);

        length = strlen(line);
        sscanf(line,"%s",n->email);
        //strncpy(line,line,length);

        n->left = NULL;
        n->right = NULL;
        insert(root,&n);
        //printf("Po insert\n");
        //preorder(root);
        //putchar('\n');
    }
    //preorder(root);
    //fclose(f);
    printf("Bye");
    return root;
}
