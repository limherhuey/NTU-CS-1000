#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    // ____________
    // printf("Enter a key to be inserted:\n");
    // scanf("%d",&key);
    // printhashvalues(key, hashTable);
    // ____________

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}


// ___ any key will be able to visit all hash values once, without repeat __
// void printhashvalues(int key, HashSlot hashTable[]) {
//     int hash, i = 0;

//     while (i < TABLESIZE) {
//         hash = hash1(key + i * hash2(key));
//         i++;

//         printf("%d: %d\n", i, hash);

//         hashTable[hash].key++;
//     }
// }



// _______________ Insertion and Deletion by Double Hashing for Opened Addressing Hash Table ________________

int HashInsert(int key, HashSlot hashTable[])
{
    int i = 0, hash, comp = 0, delete = 0;

    for (i = 0; i < TABLESIZE; i++) {
        // get hash value
        hash = hash1(key + i * hash2(key));

        // empty slot but there was a deleted slot before this
        if (hashTable[hash].indicator == EMPTY && delete)
            break;
        // empty slot: key can be inserted
        else if (hashTable[hash].indicator == EMPTY) {
            hashTable[hash].key = key;
            hashTable[hash].indicator = USED;
            return comp;
        }
        // first encounter of a deleted slot: mark hash value
        else if (hashTable[hash].indicator == DELETED && !delete)
            delete = hash;
        // key already exists
        else if (hashTable[hash].key == key && hashTable[hash].indicator == USED)
            return -1;
        // increment key comparison count
        else if (hashTable[hash].indicator == USED)
            comp++;
    }

    // insert key at first deleted slot, if applicable
    if (delete) {
        hashTable[delete].key = key;
        hashTable[delete].indicator = USED;
    }

    return comp;
}

int HashDelete(int key, HashSlot hashTable[])
{
    int i = 0, hash, comp = 0;

    for (i = 0; i < TABLESIZE; i++) {
        hash = hash1(key + i * hash2(key));

        // delete if key is found
        if (hashTable[hash].indicator == USED && hashTable[hash].key == key) {
            hashTable[hash].indicator = DELETED;
            return ++comp;
        }
        else if (hashTable[hash].indicator == USED)
            comp++;
        else if (hashTable[hash].indicator == EMPTY)
            break;
    }

    return -1;
}