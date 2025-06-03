#ifndef PESHO_H
#define PESHO_H

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


void input(int* peshoJump, int* policeJump, char * path);

void addEdges(Graph * graph);


#endif