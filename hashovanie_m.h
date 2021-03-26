//
// Created by tomas on 26. 3. 2021.
//

#ifndef TEST2_HASHOVANIE_M_H
#define TEST2_HASHOVANIE_M_H

#endif //TEST2_HASHOVANIE_M_H
typedef struct element {
    int id;
    char name[50];
    char app_name[50];
    char email[150];
}ELEMENT;
long hash(char *a);
ELEMENT **create(int n);
int h_insert(ELEMENT *table[],ELEMENT *e, int *size);
void show_hash_table(ELEMENT *table[],int size);
ELEMENT **generate_hash_table(int *table_size);
ELEMENT *h_search(ELEMENT *table[],char *key,int *size);