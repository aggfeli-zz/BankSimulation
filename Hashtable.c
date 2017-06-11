#include "Hashtable.h"
#include <stdio.h>
#include <malloc.h>

typedef struct simple_list_node{
    vertex v;        //pointer to graph vertex
    list_node next;
}simple_list_node;

typedef struct hash_table{
    int size;           //size of nodes in bucket
    list_node head;  
}hash_table;

int hash_function(int key , int HashtableEntries)  //A simple Hash Function
{
    int index = key % HashtableEntries;
    return index;
}

HashTable create(int HashtableEntries)              //Create hashtable  
{
    int i;
    HashTable temp = calloc(HashtableEntries, sizeof(hash_table));
    if (temp == NULL) return NULL;  
    for (i = 0; i < HashtableEntries; i++)
    {
        temp[i].head = NULL; temp[i].size = 0;
    }
    return temp;
}

list_node create_simplelist_node(int key)           //Create simple list
{
    list_node temp = (list_node) malloc(sizeof(simple_list_node));
    if ( temp == NULL )  return;   
    temp->next = NULL;       
    temp->v = createnodes(key); //Create graph's vertex
    return temp;
}

void insertToHash(HashTable *table, int key, int HashtableEntries) 
{
    int index = hash_function(key , HashtableEntries);
    list_node temp =  create_simplelist_node(key);
    if ((*table)[index].head == NULL)    // head of list for the bucket with index "hashIndex" 
    {
        (*table)[index].head = temp;
        (*table)[index].size ++;
        return;
    }
    temp->next = (*table)[index].head;          //New node is the head of list
    (*table)[index].head = temp;
    (*table)[index].size++;
    return;
}

vertex  searchInHash(HashTable table, int key, int HashtableEntries, int no_of_case) //Search a vertex with the help of the Hashtable
{
   //int flag = 0;
    int index = hash_function(key , HashtableEntries);      //Find the bucket
    list_node temp, temp1 = table[index].head;
    temp = table[index].head;
    if (!temp) return NULL;
    while (temp != NULL)                
    {
        int id_key = get_id(temp->v);
        if (id_key == key)                      //If you found what we were looking for
        {            
            if (no_of_case == 3 || no_of_case == 1)     //If we need the vertex return it
                return  (temp->v);
            if(no_of_case == 2 && check_neighbours(temp->v) == 0)                         //Else we need to delete the wanted vertex
            {
                if(key == get_id(table[index].head->v))  table[index].head = table[index].head->next;
                else temp1->next = temp->next;                     //Fix prev- next pointer of the list
                delete_from_hash(temp);
                table[index].size--;
                printf("success: delete %d\n", key);
                //flag = 1;
                break;
            } 
            else printf("failure: Node %d has at least one vector\n", key);
        }
        temp1 = temp;                   //store previous list node
        temp = temp->next;
    }
    //if (!flag) printf("Search element unavailable in hash table\n");   
    return NULL;
  }

void delete_from_hash( list_node temp)          //Delete node from Hashtable
{    
    delete_node(temp->v);                       //Delete vertex from graph
    free(temp);
    return;
}

void destructHashTable(HashTable *table, int HashtableEntries) //Destruct whole Hashtable
{
    int i;
    list_node todel,todel2;
    for (i = 0; i < HashtableEntries; i++)
    {
        todel = (*table)[i].head;
	while(todel != NULL)
	{   
            todel2 = todel;
            todel = todel->next;
            delete_node(todel2->v);              //Delete vertex from graph
            free(todel2);
	}
	(*table)[i].head = NULL;
    }
    free(*table);
    (*table)=NULL;
}

void triangle(HashTable table, int HashtableEntries, int no_of_case, vertex n1, double amount) //Resembles DFS
{
    edge temp = get_neighbour(n1);
    vertex n2, n3;
    int flag = 0;
    while (temp != NULL)            //While there are edges 
    {
        if (get_weight(temp) >= amount)     
        {
            n2 = searchInHash(table, get_id_edge(temp), HashtableEntries, 3);
            edge temp2 = get_neighbour(n2);
            while (temp2 != NULL)
            {
                if (get_weight(temp2) >= amount)
                {
                    n3 = searchInHash(table, get_id_edge(temp2), HashtableEntries, 3);
                    edge temp3 = get_neighbour(n3);
                    while(temp3 != NULL)
                    {
                        if (get_id_edge(temp3) == get_id(n1) && get_weight(temp3) >= amount)
                        {
                            if (flag == 0){printf ("success: triangle(%d,%f) =\n",get_id(n1), amount); flag++;}
                            printf("(%d, %d, %d)\n", get_id(n1), get_id(n2), get_id(n3));
                            break;
                        }
                        else temp3 = get_neighbour_edge(temp3);
                    }
                }                
                temp2 = get_neighbour_edge(temp2);
            }         
        }
        temp = get_neighbour_edge(temp);
    }
}

void printGraph(HashTable table, int HashtableEntries) //Print whole Graph with the help of Hashtable
{
    int i ,j;
    list_node temp;
    for (i = 0; i < HashtableEntries; i++)
    {
        temp = table[i].head;
        for (j = 0; j < table[i].size ; j++)
        {
            printf ("vertex(%d) =", get_id(temp->v));
            print_all_influx(temp->v, 0);
            temp = temp->next;
        }
    }
}


void conn(HashTable table, int HashtableEntries, vertex temp, int id, int *flag, int *conn_table, int *j) 
{
    int i = 0, z;
    if (temp != NULL && get_visited(temp) == 0) set_visited(temp, 1); //If we haven't visited this vertex continue
    else return;                                       //Else return
    edge tmp_edge = get_neighbour(temp);
    if(tmp_edge != NULL && get_visited_edge(tmp_edge) == 0) set_visited_edge(tmp_edge, 1);
    while (tmp_edge != NULL)
    {
        if(get_id_edge(tmp_edge) != id )     //If we haven't found the wanted id continue with dfs
            conn(table, HashtableEntries,searchInHash(table, get_id_edge(tmp_edge), HashtableEntries, 3), id, flag, conn_table, j);
        if (get_id_edge(tmp_edge) == id)        //Id has been found
        {
            set_visited(temp, 0);               //Set vertex un-visited
            i = *j;
            conn_table[i] = get_id_edge(tmp_edge); //Add it in array
            set_visited_edge(tmp_edge, 0);          //Set edge un-visited
            ++*j; ++*flag ;             
            return;
        }
        else if (*flag != 0)                    //If id has been found-add vertex in path
        {   
            i = *j;
            conn_table[i] = get_id_edge(tmp_edge);
            set_visited_edge(tmp_edge, 0);
            ++*j;
            break;
        }
        else tmp_edge = get_neighbour_edge(tmp_edge);
    }   
    set_visited(temp, 0);
    i = 0;
    return ;
}

void traceflow(HashTable table, int HashtableEntries, vertex temp, int *l, int *conn_table, int *j, double *amount)
{
    int i = 0, z, flag = 0;
    if (get_visited(temp) == 0) set_visited(temp, 1); //If we haven't visited this vertex continue
    else return;
    edge tmp_edge = get_neighbour(temp);
    if(tmp_edge != NULL && get_visited_edge(tmp_edge) == 0) set_visited_edge(tmp_edge, 1);
    while (tmp_edge != NULL)
    {
        for (z = 0; z < 100, conn_table[z]!= 0; z++)   //If id exists already in array go to next edge
            if (conn_table[z] == get_id_edge(tmp_edge)) flag = 1;
        if (flag != 1 && get_id_edge(tmp_edge) != 0){
        i = *j;
        conn_table[i] = get_id_edge(tmp_edge);
        *amount += get_weight(tmp_edge); 
        ++*j;--*l;
        if (*l != 0 )                           //If we haven't reached wanted depth
            traceflow(table, HashtableEntries,searchInHash(table, get_id_edge(tmp_edge), HashtableEntries, 3), l, conn_table, j, amount);
        set_visited(temp, 0);
        set_visited_edge(tmp_edge, 0);  
        }
        flag = 0 ;
        if (*l != 0) tmp_edge = get_neighbour_edge(tmp_edge);
        else break;
    }
    return ;
}