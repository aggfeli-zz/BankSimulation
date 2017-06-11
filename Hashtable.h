/* 
 * File:   Hashtable.h
 * Author: Ageliki Felimegka
 * AM: 1115201300192
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H
#include "Graph.h"

typedef struct hash_table *HashTable;

typedef struct simple_list_node  *list_node;

HashTable create(int no_of_buckets);
void insertToHash(HashTable *table, int key, int no_of_buckets);
void deleteFromHashTable(HashTable *table, int key, int HashtableEntries) ;
vertex  searchInHash(HashTable table, int key, int HashtableEntries, int no_of_case);
void delete_from_hash( list_node temp);
void destructHashTable(HashTable *table, int HashtableEntries);
void triangle(HashTable table, int HashtableEntries, int no_of_case,vertex n1, double amount);
void printGraph(HashTable table, int HashtableEntries);
list_node create_simplelist_node(int key);

void conn(HashTable table, int HashtableEntries, vertex temp, int id, int *flag, int *conn_table, int *j) ;
void traceflow(HashTable table, int HashtableEntries, vertex temp, int *l, int *conn_table, int *j,double *amount);

#endif	/* HASHTABLE_H */

