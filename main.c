/* 
 * File:   main.c
 * Author: Ageliki Felimegka
 * AM: 1115201300192
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include "Graph.h"
#include "Hashtable.h"


int main(int argc, char** argv) 
{
    int i, HashtableEntries, id = 0, len, flag;
    
    char *token = "bla", *temp;
    char buf[100];
    
    if (strcmp(argv[3], "-b") == 0) HashtableEntries = atoi(argv[4]);
    else HashtableEntries = atoi(argv[2]);
    HashTable h_table = create( HashtableEntries);
    int conn_table[100];
    
    if (strcmp(argv[1], "-o") == 0) flag = 2;
    else if(strcmp(argv[3], "-o") == 0)flag = 4;
    else flag = 0;
    FILE *fpb; 
    
    if (flag != 0){                     //If there is a file open it
        
        fpb = fopen (argv[flag],"r");
        if (fpb == NULL) { printf("Cannot open file\n"); flag = 0;}
    }
    while (1)
    {
        i = 0;
        if (flag == 0){                 //If there is no file or the file has been read, continue with stdin
            if (h_table == NULL) h_table = create( HashtableEntries);
            fgets(buf, sizeof(buf), stdin);
        }
        else{                                   //Else there is a file that needs to be read
            fgets(buf, sizeof(buf), fpb);
            //printf("%s", buf);
            if (buf == NULL) flag = 0;
        }
        len = strlen(buf);
        if (buf[len - 1] == '\n') buf[len -1] = '\0';   //Get rid of the new line
        token = strtok(buf, "  ");
        
        if (strcmp(token,"createnodes") == 0) i = 1;
        else if (strcmp(token,"delnodes") == 0) i = 2;
        else if (strcmp(token,"addtran") == 0) i = 3;
        else if (strcmp(token,"deltran") == 0) i = 4;
        else if (strcmp(token,"lookup") == 0) i = 5;
        else if (strcmp(token,"triangle") == 0) i = 6;
        else if (strcmp(token,"conn") == 0) i = 7;
        else if (strcmp(token,"allcycles") == 0) i = 8;
        else if (strcmp(token,"traceflow") == 0) i = 9;
        else if (strcmp(token,"bye") == 0) i = 10;
        else if (strcmp(token,"print") == 0) i = 11;
        else printf("Try again!\n");
        
        switch(i){
            case 1:                   //First case: syntax:createnodes N1 N2 N3 N4... + creation of double list- hashtable 
                len = len - 13;         //Find how many N1 N2 N3 N4... we have
                len = len / 7;
                token = strtok(NULL, " ");
                i = 0;
                while (i < len)                     //For every N1 N2 N3 N4...
                {
                    temp = (char*)malloc(60*strlen(token));
                    strncpy(temp,token,strlen(token));
                    id = atoi(temp);
                    vertex n1 = searchInHash(h_table, id, HashtableEntries, 1);
                    if( n1 == NULL)
                    {
                        insertToHash(&h_table, id, HashtableEntries);  
                        printf("success: created %d\n", id);
                    }
                    else printf("failure: %d already exists\n", id);
                    i++;
                    if (i == len) break;
                    token = strtok(NULL, " ");
                } 
                free(temp);
            break;
            case 2:               //Second case: syntax:delnodes N1 N2 N3 N4...
                len = len - 10;
                len = len / 7;
                token = strtok(NULL, " ");
                i = 0;
                while (i < len)                     //For every N1 N2 N3 N4...
                {
                    temp = (char*)malloc(60*strlen(token));
                    strncpy(temp,token,strlen(token));
                    id = atoi(temp);
                    vertex n1 = searchInHash(h_table, id, HashtableEntries, 2);
                    i++;
                    if (i == len) break;
                    token = strtok(NULL, " ");
                } 
                free(temp);
            break;
            case 3:                 //Third case: syntax addtran N1 N2 amount
                i = 1;
                temp = (char*)malloc(60 * strlen(token));
                int N1, N2;
                double amount;
                while( token != NULL ) 
                {
                   token = strtok(NULL, " ");
                   strncpy(temp, token, strlen(token));
                   if(i == 1) N1 = atoi(temp);
                   if(i == 2) N2 = atoi(temp);
                   if(i == 3) amount = atof(token);
                   i++;
                   if(i == 4) break;                             
                }
                vertex n1 = searchInHash(h_table, N1, HashtableEntries, 3);
                vertex n2 = searchInHash(h_table, N2, HashtableEntries, 3);
                if (n1 != NULL && n2 != NULL)
                {
                    addtran(n1, n2, amount) ;
                    printf("success: added transaction %d %d with %.3f\n", N1, N2, amount);
                }
                else printf("Failure %d or %d doesn't exist\n", N1, N2);
                free(temp);
            break;
            case 4:                     //Fourth case: syntax addtran N1 N2
                temp = (char*)malloc(60 * strlen(token));
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N1 = atoi(temp);
                token = strtok(NULL, " ");
                strncpy(temp, token, strlen(token));
                N2 = atoi(temp);
                n1 = searchInHash(h_table, N1, HashtableEntries, 3);
                n2 = searchInHash(h_table, N2, HashtableEntries, 3);
                if(n1 != NULL && n2 != NULL)
                {
                    deltran(n1, n2);
                    printf("success: deleted transaction %d %d\n", N1, N2);
                }             
                else printf("Failure %d or %d doesn't exist\n", N1, N2);
                free(temp);
            break;
            case 5:                     //Fifth case: syntax [in | out | sum] N
                temp = (char*)malloc(60 * strlen(token));
                char temp1 [10];
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                strcpy(temp1,temp);
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N2 = atoi(temp);
                n2 = searchInHash(h_table, N2, HashtableEntries, 3);
                if (n2 != NULL) lookup(n2, temp1);
                else printf("Failure %d doesn't exist\n", N2);
                free(temp);
            break;
            case 6:                     //Sixth case: syntax triangle N k
                temp = (char*)malloc(60 * strlen(token));
                double k;
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N1 = atoi(temp);
                token = strtok(NULL, " ");
                k = atof(token);
                n1 = searchInHash(h_table, N1, HashtableEntries, 3);
                if (n1 != NULL) triangle(h_table, HashtableEntries, 2, n1, k);
                else printf("Failure %d doesn't exist\n", N1);
                free(temp);
            break;            
            case 7:                     //Sixth case: syntax conn N1 N2
                temp = (char*)malloc(60 * strlen(token));
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N1 = atoi(temp);
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N2 = atoi(temp);
                n1 = searchInHash(h_table, N1, HashtableEntries, 3);
                if (n1 != NULL) 
                {
                    int flag = 0;
                    for (i = 0; i < 100; i++) conn_table[i] = 0;
                    int i  = 0;
                    conn(h_table, HashtableEntries, n1, N2, &flag, conn_table, &i) ;
                    if (flag != 0)
                    {   
                        printf("success: conn(%d,%d) = (%d", N1, N2,N1);
                        for (i = (100 - 1); i >= 0 ; i--)if(conn_table[i] != 0) printf(",%d", conn_table[i]);
                        printf(")\n");
                    }
                    else printf("conn(%d,%d) not found\n", N1, N2);
                }
                else printf("Failure %d doesn't exist\n", N1);
                free(temp);
            break;
            case 8:                         //Sixth case: syntax allcycles N
                temp = (char*)malloc(60 * strlen(token));
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N1 = atoi(temp);
                
            break;  
            case 9:                         //Sixth case: syntax traceflow N l
                temp = (char*)malloc(60 * strlen(token));
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N1 = atoi(temp);
                token = strtok(NULL, " ");
                strncpy(temp,token,strlen(token));
                N2 = atoi(token);
                n1 = searchInHash(h_table, N1, HashtableEntries, 3);
                if (n1 != NULL)
                {
                    for (i = 0; i < 100; i++) conn_table[i] = 0;
                    int i  = 1, l = N2;
                    conn_table[0] = N1;
                    double amount = 0;
                    traceflow(h_table, HashtableEntries, n1, &N2, conn_table, &i, &amount);
                    if (N2 == 0)
                    {
                        printf("success: traceflow(%d,%d) = (", N1, l);                   
                        for (i = 0; i < 100; i++)if(conn_table[i] != 0) printf("%d,", conn_table[i]);
                        printf("%f)\n", amount);
                    }
                    else printf("Failure no traceflow found for depth %d for node %d\n", l, N1);
                }
                else printf("Failure %d doesn't exist\n", N1);
                free(temp);
            break;  
            case 10:
                strcpy(token,"bye");
                destructHashTable(&h_table, HashtableEntries);
                printf("success: cleaned memory\n");
                flag = 0;
            break;
            case 11:                   //Eleventh case: print
                printGraph(h_table, HashtableEntries);
            break;
        }
    }
    return (EXIT_SUCCESS);
}


