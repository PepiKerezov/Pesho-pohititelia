#include <stdio.h>
#include <stdlib.h>
#include "utils/graph.h"
#include "utils/linked-list.h"
#include "map.txt"
#include "pesho.h"


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

void addEdges(Graph *graph) {
    Vertex *current = graph->vertices;

    while (current != NULL) {
        Vertex *current2 = graph->vertices;
        while (current2 != NULL) {
            if (current != current2) {
                // Find minimum distance between points in current->data and current2->data
                ListNode *list1 = (ListNode *)current->data;
                ListNode *list2 = (ListNode *)current2->data;

                double minDistance = -1.0;
                for(;list1 != NULL;list1 = list1->next) {
                    hashtag *point1 = (hashtag *)list1->data;
                    list2 = (ListNode *)current2->data;  

                    for(;list2 != NULL;list2 = list2->next) {
                        hashtag *point2 = (hashtag *)list2->data;

                        double dx = point1->x - point2->x;
                        double dy = point1->y - point2->y;
                        double dist = sqrt(dx * dx + dy * dy);

                        if (minDistance < 0 || dist < minDistance) {
                            minDistance = dist;
                        }
                    }

                }
                if (minDistance >= 0) {
                    graph_add_edge(graph, current, current2, minDistance);
                }
            }
            current2 = current2->next;
        }
        current = current->next;
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
