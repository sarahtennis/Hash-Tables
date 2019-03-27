#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
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

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)

  int capacity;
  Pair **storage; --> char *key; char *value;
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  // initialize instance of BasicHashTable
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));

  // set capacity to input value (allocated space part of BasicHashTable instance)
  ht->capacity = capacity;

  // allocate space for pair storage (space for pairs created elsewhere)
  ht->storage = (Pair **)calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // generated hashed key
  unsigned int newKey = hash(key, ht->capacity);

  // create new Pair object
  Pair *newPair = create_pair(key, value);

  // if something already at key value, error msg
  if (ht->storage[newKey])
  {
    fprintf(stderr, "Overwriting value at %d", newKey);
  }

  // write new pair to hashed key
  ht->storage[newKey] = newPair;

  // no return
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // hash key
  unsigned int removeHash = hash(key, ht->capacity);

  // check if key exists in ht
  if (ht->storage[removeHash])
  {
    // free Pair (and strings)
    destroy_pair(ht->storage[removeHash]);

    // point to 0 (consistent with calloc)
    ht->storage[removeHash] = 0;
  }
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  unsigned int checkHash = hash(key, ht->capacity);

  if (ht->storage[checkHash])
  {
    return ht->storage[checkHash]->value;
  }
  else
  {
    return NULL;
  }
}

// BasicHashTable *ht = malloc(sizeof(BasicHashTable));
// ht->capacity = capacity;
// ht->storage = (Pair *)calloc(capacity, sizeof(Pair *));

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  // free each pair
  for (int x = 0; x < ht->capacity; x++)
  {
    if (ht->storage[x])
    {
      free(ht->storage[x]);
    }
  };

  // free the storage
  free(ht->storage);

  // free entire data type
  free(ht);
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL)
  {
    printf("...gone tomorrow. (success)\n");
  }
  else
  {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
