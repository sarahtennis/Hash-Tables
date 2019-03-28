#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the 
  next `LinkedPair` in the list of `LinkedPair` nodes. 
 */
typedef struct LinkedPair
{
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable
{
  int capacity;
  LinkedPair **storage;
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char *u_str = (unsigned char *)str;

  while ((c = *u_str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

// int capacity;
// LinkedPair **storage; --> char *key; char *value; struct LinkedPair *next;

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  // initialize instance of HashTable
  HashTable *ht = malloc(sizeof(HashTable));

  // set capacity to input value (allocated space part of HashTable instance)
  ht->capacity = capacity;

  // allocate space for pair storage (space for pairs created elsewhere)
  ht->storage = (LinkedPair **)calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // hash key
  unsigned int hashIndex = hash(key, ht->capacity);

  // create new pair
  LinkedPair *newPair = create_pair(key, value);

  // if index is empty
  if (!ht->storage[hashIndex])
  {
    ht->storage[hashIndex] = newPair;
  }
  else
  {
    // if not empty, either replace or add to linked list
    // insert B: A->B->C
    LinkedPair *previous = NULL;
    LinkedPair *current = ht->storage[hashIndex];

    do
    {
      // key of current pair is same as parameter key
      if (strcmp(current->key, key) == 0)
      {
        // no previous, first/only in linked list
        if (!previous)
        {
          ht->storage[hashIndex] = newPair;
          newPair->next = current->next;
          destroy_pair(current);
        }
        else
        {
          // not first/only element
          ht->storage[hashIndex] = newPair;
          previous->next = newPair;
          newPair->next = current->next;
          destroy_pair(current);
        }
        break;
      }
      else
      {
        if (current->next)
        {
          previous = current;
          current = current->next;
        }
        else
        {
          current->next = newPair;
          break;
        }
      }

    } while (current);
  }
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  return NULL;
}

// delete all: INDEX 1: A->B->C->NULL

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{
  // loop through all indices in capacity
  for (int x = 0; x < ht->capacity; x++)
  {
    // if not NULL at index
    if (ht->storage[x])
    {
      LinkedPair *temp = ht->storage[x];
      LinkedPair *next = temp->next;
      while (temp)
      {
        if (next)
        {
          free(temp);
          temp = next;
          next = next->next;
        }
        else
        {
          free(temp);
          temp = NULL;
        };
      };
    };
  }

  free(ht->storage);

  // free entire data type
  free(ht);
}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht;

  return new_ht;
}

#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  // int old_capacity = ht->capacity;
  // ht = hash_table_resize(ht);
  // int new_capacity = ht->capacity;

  // printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
