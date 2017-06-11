/* 
 * File:   Graph.h
 * Author: Ageliki Felimegka
 * AM: 1115201300192
 */

#ifndef GRAPH_H
#define	GRAPH_H

typedef struct Vertex *vertex;

typedef struct Edge *edge;

vertex createnodes(int temp);
void addtran(vertex n1, vertex n2, double amount);
void deltran(vertex n1, vertex n2);
void lookup(vertex temp, char *index);
void delete_node(vertex temp);
edge get_neighbour(vertex temp);
edge get_neighbour_edge(edge temp);
double get_weight(edge temp);
int get_id_edge(edge temp);
int get_id(vertex temp);
void print_all_influx(vertex temp, int num);
void set_visited(vertex temp, int num);
void set_visited_edge(edge temp, int num);
int get_visited(vertex temp);
int get_visited_edge(edge temp);

#endif	/* GRAPH_H */

