#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct Edge{
    double weight;
    int id;
    int visited;
    edge next_e;
}Edge;

struct Vertex{
    int id;
    int visited;
    double no_of_influx;
    edge neighbour;    
}Vertex;

vertex createnodes(int temp)
{
    vertex v_temp = malloc(sizeof(Vertex));
    v_temp->id = temp;
    v_temp->neighbour = NULL;
    v_temp->no_of_influx = 0;
    v_temp->visited = 0;
    return v_temp;
}

edge create_edge(int id, double amount)
{
    edge temp = malloc(sizeof(Edge));
    temp->id = id;
    temp->next_e = NULL;
    temp->weight = amount;
    temp->visited = 0;
    return temp;
}

void addtran(vertex n1, vertex n2, double amount)
{
    n2->no_of_influx = n2->no_of_influx + amount;
    if (n1->neighbour == NULL)                      //First edge
    {
        edge temp = create_edge(n2->id, amount);
        n1->neighbour = temp;
        return ;
    }
    edge temp = n1->neighbour;
    while (temp != NULL)
    {
        if (temp->id == (n2)->id)                   //If edge already exists
        {
            temp->weight = (temp)->weight + amount; //Increase amount
            return;
        }            
        else if (temp->next_e != NULL)              //If there is a next edge 
            temp = temp->next_e;                    //Go to the next
        else                                        //else you are at the end of the edge's list
            break;
    }
    edge temp_edge = create_edge(n2->id, amount);   //Create edge node at the end of the list
    temp->next_e = temp_edge;
}

int check_neighbours(vertex temp)
{
    if (temp->no_of_influx == 0 || temp->neighbour == NULL) return 0; //there are no neighbours - edges
    else return 1;  //there are edges
}

void delete_node(vertex temp)
{
    if (temp->neighbour != NULL)            //If there are neighbours delete-free them
    {
        edge temp_edge = temp->neighbour, temp_edge2;
        while (temp_edge != NULL)
        {
            temp_edge2 = temp_edge;
            temp_edge = temp_edge->next_e;
            free(temp_edge2);
        }
    }
    free(temp);      //Free vertex
    temp = NULL;
}

void deltran(vertex n1, vertex n2)
{
    edge temp = n1->neighbour, prev_node;
    if (temp->id == n2->id)                 //First node of the list
    {
        n1->neighbour = temp->next_e;
        free(temp);
       // n1->no_of_influx --;
        return;
    }
    prev_node = temp;
    temp = temp->next_e;
    while (temp != NULL)                
    {
        if (temp->id == n2->id)             //If you found the edge we need to delete
        {
            prev_node->next_e = temp->next_e;       //Fix previous and next pointers
            free(temp);
            return;
        }            
        prev_node = temp;
        temp = temp->next_e;
    } 
}

void lookup(vertex temp, char index[])
{
    if (index[0] == 'i')                //If we need the in amount
    {
        printf("success: in(%d) = %0.3f\n", temp->id, temp->no_of_influx);
        return;
    }       
    if (index[0] == 'o' || index[0] == 's')     //If we need the out or sum amount
    {
        edge temp1 = temp->neighbour;
        double out = 0;
        while(temp1 != NULL)                    //While you aren't at the end of thhe list
        {
            out += temp1->weight;              //Add the out amount
            temp1 = temp1->next_e;
        }
        if (index[0] == 'o') printf("success: out(%d) = %0.3f\n", temp->id, out);
        else printf("success: sum(%d) = %0.3f\n", temp->id, (temp->no_of_influx - out));
    }
}

edge get_neighbour(vertex temp)
{
    return temp->neighbour;
}

edge get_neighbour_edge(edge temp)
{
    return temp->next_e;
}

double get_weight(edge temp)
{
    return temp->weight;
}

int get_id_edge(edge temp)
{
    return temp->id;
}

int get_id(vertex temp)
{
    return temp->id;
}

void print_all_influx(vertex n1, int num) //Print all edges of given vertex
{
    edge temp = n1->neighbour;
    while (temp != NULL)
    {
        if (num == 1) temp->visited = 0;
        else printf(" (%d,%f) ,", temp->id, temp->weight);
        temp = temp->next_e;
    }
    printf("\n");
}

void set_visited(vertex temp, int num)
{
    if (num == 0) temp->visited = 0;
    else temp->visited = 1;
}

void set_visited_edge(edge temp, int num)
{
    if (num == 0) temp->visited = 0;
    else temp->visited = 1;
}

int get_visited(vertex temp)
{
    return temp->visited;
}

int get_visited_edge(edge temp)
{
    return temp->visited;
}