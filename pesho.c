#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils/graph.h"
#include "utils/linked-list.h"

typedef struct GridBlock{
    int x;
    int y;
    int isPesho;
    int isPolice;
}GridBlock;


void input(int* peshoJump, int* policeJump, char * path){
    printf("\nHow many steps can Pesho jump: ");
    scanf("%d", peshoJump);
    printf("How many steps can the policeman jump: ");
    scanf("%d", policeJump);
    printf("Enter path to map: ");
    scanf("%s", path);
}

Graph* makeGraph(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Could not open the file.\n");
        return NULL;
    }

    Graph* graph = graph_create();

    int x = 0, y = 0;
    char ch;
    ListNode* currentPlatform = NULL;
    int platformOpen = 0;
    while (fscanf(file, "%c", &ch) == 1) {
        if (ch == '#') {
            GridBlock* data = (GridBlock*)malloc(sizeof(GridBlock));
            data->x = x;
            data->y = y;
            data->isPesho = 0;
            data->isPolice = 0;
            list_add_end(&currentPlatform, data);
            platformOpen = 1;
            x++;
        } else if(ch == 'P') { // P - Pesho
            GridBlock* data = (GridBlock*)malloc(sizeof(GridBlock));
            data->x = x;
            data->y = y;
            data->isPesho = 1;
            data->isPolice = 0;
            list_add_end(&currentPlatform, data);
            platformOpen = 1;
            x++;
        } else if(ch == 'p') {  // p - police
            GridBlock* data = (GridBlock*)malloc(sizeof(GridBlock));
            data->x = x;
            data->y = y;
            data->isPesho = 0;
            data->isPolice = 1;
            list_add_end(&currentPlatform, data);
            platformOpen = 1;
            x++;
        } else if (ch == ' ') {
            if (platformOpen && currentPlatform != NULL) {
                graph_add_vertex(graph, currentPlatform);
                currentPlatform = NULL;
                platformOpen = 0;
            }
            x++;
        } else if (ch == '\n') {
            if (platformOpen && currentPlatform != NULL) {
                graph_add_vertex(graph, currentPlatform);
                currentPlatform = NULL;
                platformOpen = 0;
            }
            y++;
            x = 0;
        }
    }

    if (platformOpen && currentPlatform != NULL) {
        graph_add_vertex(graph, currentPlatform);
    }

    fclose(file);
    return graph;
}

double calcMinDistance(ListNode* list1, ListNode* list2) {
    double minDistance = -1.0;

    for (; list1 != NULL; list1 = list1->next) {
        GridBlock* point1 = (GridBlock*)list1->data;
        ListNode* temp2 = list2;

        for (; temp2 != NULL; temp2 = temp2->next) {
            GridBlock* point2 = (GridBlock*)temp2->data;

            double dx = point1->x - point2->x;
            double dy = point1->y - point2->y;
            double dist = sqrt(dx * dx + dy * dy);

            if (minDistance < 0 || dist < minDistance) {
                minDistance = dist;
            }
        }
    }

    return minDistance;
}

void addEdges(Graph* graph, int maxJump) {
    Vertex* current = graph->vertices;

    while (current != NULL) {
        Vertex* current2 = graph->vertices;
        while (current2 != NULL) {
            if (current != current2) {
                ListNode* list1 = (ListNode*)current->data;
                ListNode* list2 = (ListNode*)current2->data;

                double minDistance = calcMinDistance(list1, list2);

                if (minDistance <= (double)maxJump) {
                    graph_add_edge(graph, list1, list2, minDistance);
                }
            }
            current2 = current2->next;
        }
        current = current->next;
    }
}

void free_list(void* data) {
    ListNode* list = (ListNode*)data;

    while (list != NULL) {
        ListNode* next = list->next;

        if (list->data != NULL) {
            free(list->data);  
        }

        free(list);  
        list = next;
    }
}

int isInList(ListNode* list, Vertex* v) {
    ListNode * temp = list;
    while (temp != NULL) {
        if (temp->data == v) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void bfs(Vertex* start, double maxJump, ListNode** visited) {
     ListNode* queue = NULL;
    list_add_end(&queue, start);
    list_add_end(visited, start);

    while (queue != NULL) {
        Vertex* current = (Vertex*)queue->data;

        ListNode* nextQueue = queue->next;
        free(queue);
        queue = nextQueue;

        Edge* edge = current->edges;
        while (edge != NULL) {
            Vertex* dest = edge->destination;
            
            if (!isInList(*visited, dest) && edge->weight <= (double)maxJump) {
                list_add_end(&queue, dest);
                list_add_end(visited, dest);
            }

            edge = edge->next;
        }
    }
}

double heuristic(Vertex* v, Vertex* goal) {
    ListNode* list1 = (ListNode*)v->data;
    ListNode* list2 = (ListNode*)goal->data;

    return calcMinDistance(list1, list2);
}

void printPath(Vertex* target) {
    Vertex* path[1000];  // Макс дължина на пътя
    int pathLen = 0;

    Vertex* current = target;
    while (current != NULL) {
        path[pathLen++] = current;
        current = current->parent;
    }

    printf("Pesho's path to safe platform:\n");
    for (int i = pathLen - 1; i >= 0; i--) {
        ListNode* list = (ListNode*)path[i]->data;
        printf("Platform: ");
        while (list != NULL) {
            GridBlock* block = (GridBlock*)list->data;
            printf("(%d, %d) ", block->x, block->y);
            list = list->next;
        }
        printf("\n");
    }
}

Vertex* findPeshoStart(Graph* graph) {
    Vertex* current = graph->vertices;
    while (current != NULL) {
        ListNode* list = (ListNode*)current->data;
        while (list != NULL) {
            GridBlock* block = (GridBlock*)list->data;
            if (block->isPesho == 1) {
                return current;
            }
            list = list->next;
        }
        current = current->next;
    }
    return NULL;
}

ListNode* findPoliceStarts(Graph* graph) {
    ListNode* policeStarts = NULL;

    Vertex* current = graph->vertices;
    while (current != NULL) {
        ListNode* list = (ListNode*)current->data;
        while (list != NULL) {
            GridBlock* block = (GridBlock*)list->data;
            if (block->isPolice == 1) {
                list_add_end(&policeStarts, current);
                break;  
            }
            list = list->next;
        }
        current = current->next;
    }

    return policeStarts;
}

Vertex* findPathToSavety(Graph* graph, Vertex* start, Vertex* goal) {

    ListNode* openList = NULL;
    ListNode* closedList = NULL;

    list_add_end(&openList, start);

    typedef struct ScoreEntry {
        Vertex* vertex;
        double g_score;
    } ScoreEntry;

    ScoreEntry* scores = (ScoreEntry*)malloc(sizeof(ScoreEntry) * graph->vertex_count);
    int scoresCount = 0;
    scores[scoresCount++] = (ScoreEntry){start, 0.0};

    // Optimization: use arrays to avoid isInList() linear scans
    int* inOpenList = (int*)calloc(graph->vertex_count, sizeof(int));
    int* inClosedList = (int*)calloc(graph->vertex_count, sizeof(int));

    // Assuming vertex->id is [0 .. vertex_count-1]
    inOpenList[start->id] = 1;

    while (openList != NULL) {
        // Find node with lowest f_score
        ListNode* temp = openList;
        Vertex* current = (Vertex*)temp->data;
        double current_g = 0.0;

        for (int i = 0; i < scoresCount; i++) {
            if (scores[i].vertex == current) {
                current_g = scores[i].g_score;
                break;
            }
        }

        double current_f = current_g + heuristic(current, goal);
        ListNode* bestNode = temp;
        temp = temp->next;

        while (temp != NULL) {
            Vertex* vtx = (Vertex*)temp->data;
            double g_vtx = 0.0;
            for (int i = 0; i < scoresCount; i++) {
                if (scores[i].vertex == vtx) {
                    g_vtx = scores[i].g_score;
                    break;
                }
            }

            double f_vtx = g_vtx + heuristic(vtx, goal);
            if (f_vtx < current_f) {
                bestNode = temp;
                current = vtx;
                current_g = g_vtx;
                current_f = f_vtx;
            }

            temp = temp->next;
        }

        // If goal found
        if (current == goal) {
            printf("Path found:\n");
            printPath(goal);
            free_list(openList);
            free_list(closedList);
            free(scores);
            free(inOpenList);
            free(inClosedList);
            return goal;
        }

        // Move current to closedList
        list_add_end(&closedList, current);
        inClosedList[current->id] = 1;

        // Remove current from openList (single pass)
        ListNode* prev = NULL;
        temp = openList;
        while (temp != NULL) {
            if (temp->data == current) {
                if (prev == NULL) {
                    openList = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        inOpenList[current->id] = 0;

        // For each neighbor
        Edge* edge = current->edges;
        while (edge != NULL) {
            Vertex* neighbor = edge->destination;
            double tentative_g_score = current_g + edge->weight;

            if (inClosedList[neighbor->id]) {
                edge = edge->next;
                continue;
            }

            double neighbor_g_score = -1.0;
            for (int i = 0; i < scoresCount; i++) {
                if (scores[i].vertex == neighbor) {
                    neighbor_g_score = scores[i].g_score;
                    break;
                }
            }

            // If neighbor not in openList → add it
            if (!inOpenList[neighbor->id]) {
                list_add_end(&openList, neighbor);
                inOpenList[neighbor->id] = 1;
            }

            // If better path to neighbor
            if (neighbor_g_score < 0.0 || tentative_g_score < neighbor_g_score) {
                neighbor->parent = current;
                int found = 0;
                for (int i = 0; i < scoresCount; i++) {
                    if (scores[i].vertex == neighbor) {
                        scores[i].g_score = tentative_g_score;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    scores[scoresCount++] = (ScoreEntry){neighbor, tentative_g_score};
                }
            }

            edge = edge->next;
        }
    }

    // No path found
    printf("No path found to safe platform!\n");
    free_list(openList);
    free_list(closedList);
    free(scores);
    free(inOpenList);
    free(inClosedList);
    return NULL;
}


void findSafeSpot(Graph* graph, int peshoJump, int policeJump) {
    // Step 1: bfs for Pesho
    Vertex* peshoStart = findPeshoStart(graph);
    if (peshoStart == NULL) {
        printf("No starting position for Pesho!\n");
        return;
    }

    ListNode* peshoReachable = NULL;
    bfs(peshoStart, peshoJump, &peshoReachable);

    // Step 2: bfs for police
    ListNode* policeStarts = findPoliceStarts(graph);
    ListNode* policeReachable = NULL; 
    ListNode* temp = policeStarts;
    while (temp != NULL) {
        Vertex* policeStart = (Vertex*)temp->data;

        // If this policeStart is already visited → skip
        if (!isInList(policeReachable, policeStart)) {
            bfs(policeStart, policeJump, &policeReachable);
        }

        temp = temp->next;
    }

    // Step 3: find safe spot
    ListNode * tempPesho = peshoReachable;
    int foundSafe = 0;

    while (tempPesho != NULL) {
        Vertex* vertex = (Vertex*)tempPesho->data;

        // Check if police can reach
        int isSafe = 1;
        ListNode* tempPolice2 = policeReachable;
        while (tempPolice2 != NULL) {
            if (tempPolice2->data == vertex) {
                isSafe = 0;
                break;
            }
            tempPolice2 = tempPolice2->next;
        }

        if (isSafe) {
            // Found safe spot
            printf("Found save spot \n");
            findPathToSavety(graph, peshoStart, vertex);
            foundSafe = 1;
        }

        tempPesho = tempPesho->next;
    }

    if (!foundSafe) {
        printf("No safe spot found for Pesho!\n");
    }

    // Cleanup
    free_list(peshoReachable);
    free_list(policeReachable);
    free_list(policeStarts);
}



int main() {
    char path[256];
    int peshoJump, policeJump;

    input(&peshoJump, &policeJump, path);

    Graph* g = makeGraph(path);
    if (g == NULL) {
        return 1;
    }

    printf("Graph created \n");
    //So they can jump the right number of spaces 
    peshoJump++;
    policeJump++;

    addEdges(g, (peshoJump > policeJump) ? peshoJump : policeJump); 
    printf("Edges added.\n");

    findSafeSpot(g, peshoJump, policeJump);

    graph_free(g, free_list);

    printf("All memory freed. Exiting.\n");

    return 0;
}
