//key value pairs vs arrays
//association between two values i.e. (persons name vs id)
//old style: indexing in array called an offset
//          users[0], users[1]
//keys:     users[id]

//purpose of a hash table: 
//lookup table (search data by a key) (zipcode -> state)
//extremely fast inserts and retrieval
//          data[offset] <-- computer jumps to correct position due to offset (position in memory) 
//                       <-- hashtables can jump to correct position without knowing offset (hash table)
//          location in memory can be calculated from key (hash processing)
//                      efficient process, O(1) constant time

// data = {};
// data[3] = "Alex";
// key % size of array
// 3 % 6(array size) = 3
// data [664] = "Toby";
// 664 % 6 = 4

//collisions: two keys have same hash value
//linked list: original key becomes a node pointing to new node
//operation speed of a linked list: iteration = O[n], slowed (n=size of linked list)

//hash table = array with a hash function
//input mapped to a location in array
//calling hash function on same input should produce same output
//fast lookups
//hash function results should be random

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person{
    char name [MAX_NAME];
    int age;
    // other stuff
    struct person *next;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME); //length of string 1 character and add up asci values of char
    unsigned int hash_value=0;
    for (int i=0; i<length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE; //modulus to fit it in table size
    }
    return hash_value;
}

//string 1-2-3-4 -> actual value (decimal)

bool init_hash_table() {
    for (int i=0; i<TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
    //table is empty
}

void print_table(){
    printf("Start\n");
    for (int i=0; i<TABLE_SIZE; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while (tmp != NULL){
                printf("%s - ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}
// find a person by name, returns null or pointer to person
person *hash_table_lookup (char *name){
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) !=0) {
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) !=0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL) {
        //deleting the head
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}

int main() {
    init_hash_table();
    print_table();

    person alex = {.name="Alex", .age=1};
    person mikey = {.name="Mikey", .age=2};
    person toby = {.name="Toby", .age=3};
    person tiger = {.name="Tiger", .age=4};
    person godzilla = {.name="Godzilla", .age=5};
    person muffin = {.name="Mikey", .age=20};

    hash_table_insert(&alex);
    hash_table_insert(&mikey);
    hash_table_insert(&toby);
    hash_table_insert(&tiger);
    hash_table_insert(&muffin);

    print_table();

    person *tmp = hash_table_lookup("Godzilla");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s, age is %d.\n", tmp->name, tmp->age);
    }
    
    tmp = hash_table_lookup("Alex");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s, age is %d.\n", tmp->name, tmp->age);
    }
    
    hash_table_delete("Alex");

    tmp = hash_table_lookup("Alex");
    if (tmp == NULL) {
        printf("Not found!\n");
    } else {
        printf("Found %s, age is %d.\n", tmp->name, tmp->age);
    }

    
    hash_table_insert(&godzilla);

    print_table();
    
    printf ("Alex => %u\n", hash("Alex"));
    printf ("Mikey => %u\n", hash("Mikey"));
    printf ("Toby => %u\n", hash("Toby"));
    printf ("Tiger => %u\n", hash("Tiger"));
    printf ("Godzilla => %u\n", hash("Godzilla"));
    return 0;
}