#include <stdio.h>
#include <stdlib.h>
#include "utils/graph.h"
#include "utils/linked-list.h"
#include "map.txt"
#include "pesho.h"

#define COORDINATES if (ch == '\n') {  \
                tekY++; \
                tekX = 0;  \
            } else { \
                tekX++; \
            }


#define ADDNODE     hashtag * data = (hashtag *)malloc(sizeof(hashtag)); \
                    if(data == NULL) {  \
                        printf("Error allocating memory");  \
                    }   \
                    data->x = tekX; \
                    data->y = tekY; \
                    list_add_end(&list, data);  


typedef struct hashtag{
    int x;
    int y;
}hashtag;


void input(int* peshoJump, int* policeJump, char * path){
    printf("How many steps can Pesho jump: ");
    scanf("%d", peshoJump);
    printf("\n How many steps can the policeman jump: ");
    scanf("%d", policeJump);
    printf("Enter path to map");
    scanf("%s", path);
}

Graph* makeGraph(char * path){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Couldnt open the file.\n");
        return 1;
    }
    int tekX,  tekY;
    char ch;
    
    ListNode * list;
    Graph * graph = graph_create();
    while (fscanf(file, "%c", &ch) == 1) {
        if(ch == "!#") {
            COORDINATES
        }
        else {
            ADDNODE
            COORDINATES

            while (fscanf(file, "%c", &ch) == 1) {
                if(ch != "#") {
                    graph_add_vertex(graph, list);
                    list == NULL;
                    COORDINATES
                    break;
                } else {
                    ADDNODE
                    COORDINATES
                }
            }
        }
    }
    fclose(file);
    return graph;
}

void addEdges(Graph * graph) {
    Vertex * current = graph->vertices;
    for (int i = 0; i < graph->vertex_count; i++)
    {
        for (int j = 0; j < graph->vertex_count; j++)
        {
            Vertex * current2 = graph->vertices;
            if(current2 == current)
                continue;
            
        }
        
    }
    
}

int main(){

    int peshoJump = 0, policeJump = 0;
    char * path;
    input(&peshoJump, &policeJump, path);
    Graph * graph = makeGraph(path);

    //inicializiram graf, vseki vertex = linkedlist[j]
    //namiram x, y koordinatite i smqtam razstoqniqta, slagam gi kato weight mejdu vertex-ite(platformite)
    //davam go na petur da se opravq
    
    return 0;
}



    //fscanf() за четене записвам #(x, y);

    //vsqka platforma = linked list s broi elementi = nroq na #owete

    //vertex s data linked lista. t.e 16 linked list-a, za veski vertex

    //kato procheta # pravq linked list, prikluchva s purviq procheten space.

    //promenliva na koi red i koi simvol sum (x, y), zapisvam go na vseki #

    // smqtam razstoqniqta i gi slagam kato weight na edge-ovete
