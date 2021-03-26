//
//  main.c
//  Chaning Hash Table
//
//  Created by 신동규 on 12/06/2019.
//  Copyright © 2019 Mac circle. All rights reserved.
//https://github.com/donggyushin/chaining-hash-table/blob/master/Chaning%20Hash%20Table/main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_prv.h"


/*typedef struct Node{
    int id;
    struct HASH_NODE* hashNext;  // HASH_NODE pointing next node when there is a crush
}HASH_NODE;

*/
//Function that gets hash key
//POVODNA
/*
int get_hash_key(int value){
    return value % MAX_HASH;
}*/
int get_hash_key(char email[]){
    int len = strlen(email);
    int i;
    int value=0;
    for(i=0;i<len;i++){
        value += email[i]*(i+1);
    }
    if(value<0) value = value*-1;
    return value % MAX_HASH;
}
// Function that adds new node into hashTable

/*
 * void add_hash_data(Node** hashTable, int key){
    int hash_key = get_hash_key(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = key;
    newNode->hashNext = NULL;
    if(hashTable[hash_key] == NULL) {
        hashTable[hash_key] = newNode;
    }else {
        newNode->hashNext = hashTable[hash_key];
        hashTable[hash_key] = newNode;
    }
}
 */
void add_hash_data(HASH_NODE** hashTable, HASH_NODE *n){
    int hash_key = get_hash_key(n->email);
    /*HASH_NODE* newNode = (HASH_NODE*)malloc(sizeof(HASH_NODE));
    newNode->id = key;
    newNode->hashNext = NULL;*/
    if(hashTable[hash_key] == NULL) {
        hashTable[hash_key] = n;
    }else {
        n->hashNext = hashTable[hash_key];
        hashTable[hash_key] = n;
    }
}
/*
void del_hash_data(HASH_NODE** hashTable, int id){
    int hash_key = get_hash_key(id);
    if(hashTable[hash_key] == NULL) return;

    HASH_NODE* del_node = NULL;
    if(hashTable[hash_key]->id == id) {
        del_node = hashTable[hash_key];
        hashTable[hash_key] = hashTable[hash_key]->hashNext;
    }else {
        HASH_NODE* current = hashTable[hash_key];
        HASH_NODE* next = hashTable[hash_key]->hashNext;
        while(next){
            if(next->id == id){
                current->hashNext = next->hashNext;
                del_node = next;
                break;
            }
            current = next;
            next = next->hashNext;
        }
    }
    free(del_node);
}*/

/* POVODNA FIND_HASH_DATA
HASH_NODE* find_hash_data(HASH_NODE** hashTable, int id){
    int hash_key = get_hash_key(id);
    if(hashTable[hash_key] == NULL) return NULL;

    if(hashTable[hash_key]->id == id){
        return hashTable[hash_key];
    }
    HASH_NODE* current = hashTable[hash_key];
    HASH_NODE* next = current->hashNext;
    while(next){
        if(next->id == id){
            return next;
        }
        current = next;
        next = next->hashNext;
    }
    return NULL;
}
*/
//prerobena aby sedela k mojmu zadaniu
HASH_NODE* find_hash_data(HASH_NODE** hashTable, char email[]){
    int hash_key = get_hash_key(email);
    if(hashTable[hash_key] == NULL) return NULL;
    HASH_NODE *temp = hashTable[hash_key];
    printf("%s\n",hashTable[hash_key]->email);
    if(!strcmp(hashTable[hash_key]->email,email)){
        return hashTable[hash_key];
    }
    HASH_NODE* current = hashTable[hash_key];
    HASH_NODE* next = current->hashNext;
    while(next!=NULL){
        if(!strcmp(next->email,email)){
            return next;
        }
        current = next;
        next = next->hashNext;
    }
    return NULL;
}
void print_hash_table(HASH_NODE** hashTable){
    int i;
    for(i = 0 ; i < MAX_HASH ; i ++) {
        if(hashTable[i] != NULL){
            HASH_NODE* current = hashTable[i];
            printf("hashTable[%d]: ", i);
            while(current != NULL){
                printf("node-id: %d, ", current->id);
                current = current->hashNext;
            }
            printf("\n");
        }
    }
}



/*
int main(int argc, const char * argv[]) {
    // insert code here...
    HASH_NODE* hashTable[MAX_HASH];
    for(int i = 0 ; i < MAX_HASH ; i ++){
        hashTable[i] = NULL;
    }
    add_hash_data(hashTable, 21);
    add_hash_data(hashTable, 12);
    add_hash_data(hashTable, 11);
    add_hash_data(hashTable, 1);
    add_hash_data(hashTable, 3);
    add_hash_data(hashTable, 7);
    add_hash_data(hashTable, 8);
    add_hash_data(hashTable, 9);
    add_hash_data(hashTable, 31);
    add_hash_data(hashTable, 28);

    del_hash_data(hashTable, 9);

    print_hash_table(hashTable);
    return 0;
}*/