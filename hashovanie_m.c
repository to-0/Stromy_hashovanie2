//
// Created by tomas on 20. 3. 2021.
//

#include "hashovanie_m.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
long hash(char* a) {
    int len = strlen(a);
    long h = 0;
    int i;
    for (i = 0; i < len; i++) {
        h = 31*h + (int)a[i];
    }
    return h;
}
long has_f(int key){

}
ELEMENT **create(int n){
    ELEMENT **e = (ELEMENT **)calloc(n*2+1,sizeof(ELEMENT*));
    return e;
}
ELEMENT **resize_htable(ELEMENT *table[],int *size){
    int old_size = *size;
    *size = 2*(*size)+1;
    ELEMENT **new_table = (ELEMENT **)calloc(*size,sizeof(ELEMENT*));
    //table = (ELEMENT**)realloc(table,*size*sizeof(ELEMENT *));
    int i;
    for(i = 0;i<old_size;i++){
        if(table[i]!=NULL){ //nieco tam je idem prehashovat
            h_insert(new_table,table[i],size);
            table[i] = NULL;
        }
    }
    return new_table;
}
int h_insert(ELEMENT *table[],ELEMENT *e,int *size){
    long h = hash(e->email);
    int i  = h % (*size);
    if(i<0) i*=-1;
    if(table[i]==NULL){
        table[i] = e;
        //printf("Index :%d\n",i);
        //show_hash_table(table,*size);
        //putchar('\n');
        return 1;
    }
    int index = i;
    while(table[index]!= NULL){ //prehladavam celu tabulku pokial nenajdem volne miesto
        if(!strcmp(table[i]->email,e->email)){
            break;
        }
        index++;
        if(index>=*size){
            index = 0;
        }
    }
    if(table[index]==NULL){
        table[index]=e;
        //printf("Index :%d\n",index);
        //show_hash_table(table,*size);
        //putchar('\n');
        return 1;
    }
    return 0;
}
ELEMENT *h_search(ELEMENT *table[],char *key,int *size){
    long h = hash(key);
    int i  = h % *size;
    if(i<0) i*=-1;
    if(!strcmp(key,table[i]->email)){
        return table[i];
    }
    int count = 0;
    int index=i;
    while(strcmp(key,table[index]->email)!=0){
        count++;
        index++;
        if(index >= *size){
            index = 0;
        }
        if(count>=*size)
            return NULL;
    }
    if(!strcmp(key,table[index]->email)){
        return table[index];
    }
    return NULL;
}
void show_hash_table(ELEMENT *table[],int size){
    int i;
    for(i=0;i<size;i++){
        if(table[i]!=NULL){
            printf("ID: %d app_name: %s last_name: %s key:%s\n",table[i]->id,
                   table[i]->app_name,table[i]->name,table[i]->email);
        }
    }
}
ELEMENT **generate_hash_table(int *table_size){
    FILE *f = fopen("tree2.txt","r");
    ELEMENT *n;
    int size = 321;
    ELEMENT **table = create(size);
    *table_size = size;
    if (f==NULL) return NULL;
    char line[150];
    char temp[50];
    int key;
    int succ_elements=0;
    while (fgets(line,150,f)!=NULL){
        n = (ELEMENT *)malloc(sizeof(ELEMENT));
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

        length = strlen(line);
        sscanf(line,"%s",n->email);
        if(h_insert(table,n,&size)){
            succ_elements++;
            double percent  = (double)(succ_elements/size)*100;
            if(percent >70)
                table = resize_htable(table,&size);
        }
    }
    printf("Final show table\n");
    //fclose(f);
    *table_size = size;
    //show_hash_table(table,size);
    return table;

}