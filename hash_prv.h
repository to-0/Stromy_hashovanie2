//
// Created by tomas on 26. 3. 2021.
//

#ifndef TEST2_HASH_PRV_H
#define TEST2_HASH_PRV_H

#endif //TEST2_HASH_PRV_H
#define MAX_HASH 50000
typedef struct HNode{
    int id;
    char email[150];
    char name[50];
    char app_name[50];
    struct HNode* hashNext;  // HASH_NODE pointing next node when there is a crush
}HASH_NODE;
int get_hash_key(char email[]);
void add_hash_data(HASH_NODE** hashTable, HASH_NODE *n);
void del_hash_data(HASH_NODE** hashTable, int id);
HASH_NODE* find_hash_data(HASH_NODE** hashTable, char email[]);
void print_hash_table(HASH_NODE** hashTable);