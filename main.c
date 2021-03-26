//
// Created by tomas on 20. 3. 2021.
//
#include "splay_tree.h"
#include "avl_tree.h"
#include "hashovanie_m.h"
#include "hash_prv.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct testStruct{
    int id;
    char email[150];
}TESTSTRUCT;

TESTSTRUCT  *generate_search_test_array(int *size){ //zoberiem
    FILE *f = fopen("tree2.txt","r");
    if(f==NULL){
        printf("Failed to open dataset\n");
        return NULL;
    }
    int i = *size; //kolko
    //printf("Dobry den\n");
    TESTSTRUCT *test_arr = (TESTSTRUCT *)malloc(i*sizeof(TESTSTRUCT));
    int k;
    for(k=0;k<*size;k++){
        int line_number = (rand() %(99999)) + 1;
        //printf("Dobry cyklus k=%d\n",k);
        int count=0;
        char line[250];
        char temp[150];
        while(count<line_number){
            if(fgets(line,250,f)==NULL){
                printf("Failed to read\n");
                return NULL;
            }
            count++;
        }
        //printf("Idem sekat\n");
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        int key;
        sscanf(temp,"%d",&(test_arr[k].id));

        strncpy(line,line+i+1,length-i); //email je az  na konci cize idem sekat iba tak
        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(line,line+i+1,length-i);
        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(line,line+i+1,length-i);
        char email[150];
        sscanf(line," %s ",email);
        strcpy(test_arr[k].email,email);
        rewind(f);
    }
    return test_arr;
}
struct Node *generate_avl(){
    struct  Node *n;
    FILE *f = fopen("tree2.txt","r");
    if (f==NULL) return NULL;
    char line[250];
    char temp[50];
    int key;
    struct  Node *avl_root = NULL;
    while (fgets(line,250,f)!=NULL){
        n = (struct Node *)malloc(sizeof(struct Node));
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        int key;
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
        n->left = NULL;
        n->right = NULL;
        n->height = 1;
        avl_root = Insert(avl_root,n);
    }
    //fclose(f);
    return avl_root;
}
void generate_trees(NODE **root_splay, struct Node **root_avl){
    *root_splay = NULL;
    *root_avl = NULL;
    printf("\nLet me in\n");;
    FILE *f = fopen("tree2.txt","r");
    printf("oke\n");
    if (f==NULL) return;
    char line[150];
    char temp[50];
    int key;
    struct  Node *avl_root = NULL;
    NODE *n_splay;
    struct Node *n_avl;
    printf("Idem na cyklus\n");
    while (fgets(line,150,f)!=NULL){
        //printf("Pred mallocom\n");
        n_avl = (struct Node *)malloc(sizeof(struct Node));
        n_splay = (NODE*)malloc(sizeof(NODE));
        //printf("Po ma
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        int key;
        sscanf(temp,"%d",&key);
        n_splay->key = key;
        n_avl->key = key;
        char temp_line[50];
        strncpy(temp_line,line+i+1,length-i);
        strncpy(line,line+i+1,length-i); //seknem subor pokracujem iba so zvyskom

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        char app_name[50];
        sscanf(temp,"%s",app_name);
        strcpy(n_splay->app_name,app_name);
        strcpy(n_avl->app_name,app_name);
        strncpy(line,line+i+1,length-i);

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        char name[50];
        sscanf(temp,"%s",name);
        strcpy(n_splay->name,name);
        strcpy(n_avl->name,name);
        strncpy(line,line+i+1,length-i);

        length = strlen(line);
        char email[50];
        sscanf(line,"%s",email);
        strcpy(n_splay->email,email);
        strcpy(n_avl->email,email);
        n_avl->left = NULL;
        n_avl->right = NULL;
        n_avl->height = 1;
        //printf("Idem insertovat\n");
        avl_root = Insert(avl_root,n_avl);
        n_splay->left = NULL;
        n_splay->right = NULL;
        insert(*root_splay,&n_splay);
    }
    //printf("Docital som");
}


//vygenerujem prevzatu tabulku
HASH_NODE **generate_hash_table_prv(){
    FILE *f = fopen("tree2.txt","r");
    //HASH_NODE *n;
    HASH_NODE* hashTable[MAX_HASH];
    for(int i = 0 ; i < MAX_HASH ; i ++){
        hashTable[i] = NULL;
    }
    if (f==NULL) return NULL;
    char line[250];
    char temp[50];
    int pom = 0;
    while (fgets(line,249,f)!=NULL){
        pom++;
        HASH_NODE *n = (HASH_NODE *)malloc(sizeof(HASH_NODE));
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        int key;
        sscanf(temp,"%d",&(n->id));
        //printf("ID:%d\n",n->id);
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
        sscanf(line,"%s",n->email);
        n->hashNext = NULL;
        add_hash_data(hashTable,n);
    }
    return hashTable;
}
void test_stromy(TESTSTRUCT *arr,int size){
    int i;
    root = generate(); //splay root
    clock_t start, end;
    double time;
    start = clock();
    NODE *search_node;
    for(i=0;i<size;i++){
        search_node = search(arr[i].id,root);
        if(search_node != NULL){
            printf("App name:%s  Last name:%s Email:%s  Key%d\n",search_node->app_name,
                   search_node->name, search_node->email,search_node->key);
        }
    }
    end =  clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
    printf("%f\n",time);

    //AVL STROMY TEST
    struct Node *root_avl = generate_avl();
    struct Node *search_node_avl;
    for(i=0;i<size;i++){
        search_node_avl = search_avl(arr[i].id,root_avl);
        if(search_node_avl != NULL){
            printf("App name:%s  Last name:%s Email:%s  Key%d\n",search_node_avl->app_name,
                   search_node_avl->name, search_node_avl->email,search_node_avl->key);
        }
    }
    //preorder_avl(root_avl);
}
void test_tabulky(TESTSTRUCT *arr,int size){
    int m_table_size;
    ELEMENT **e = generate_hash_table(&m_table_size);
    printf("Zijem\n");
    int i;
    ELEMENT *search_node = NULL;
    for(i=0;i<size;i++){
        search_node = h_search(e,arr[i].email,&m_table_size);
        printf("%p %s\n",search_node,arr[i].email);
        if(search_node != NULL){
            printf("App name:%s  Last name:%s Email:%s  Key%d\n",search_node->app_name,
                   search_node->name, search_node->email,search_node->id);
        }
    }
    HASH_NODE **table_prv = generate_hash_table_prv();
    HASH_NODE *search_node_prv;
    for(i=0;i<size;i++){
        search_node_prv = find_hash_data(table_prv,arr[i].email);
        if(search_node_prv != NULL){
            printf("App name:%s  Last name:%s Email:%s  Key%d\n",search_node->app_name,
                   search_node->name, search_node->email,search_node->id);
        }
    }

}


int main() {
    int size = 100;
    printf("Test");
    TESTSTRUCT  *arr = generate_search_test_array(&size);
    struct Node *root_avl;
    //generate_trees(&root,&root_avl);
    //if(search_arr==NULL) return -1;

    // preorder(root);
    printf("\npo prvom testovani\n");
    putchar('\n');
    // ELEMENT **e = create(50);
    //printf("Tu\n");
    //generate_hash_table();
    test_stromy(arr,size);
    test_tabulky(arr,size);
    return 0;
}