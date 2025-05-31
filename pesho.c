#include<stdio.h>
#include "utils/graph.h"
#include "linked-list.h"
#include "pesho.txt"

typedef struct hashtag{
    int x;
    int y;
}hashtag;


void input(int* peshoJump, int* policeJump){
    printf("How many steps can Pesho jump: ");
    scanf("%d", peshoJump);
    printf("\n How many steps can the policeman jump: ");
    scanf("%d", policeJump);
}

ListNode* makeLinkedList(FILE *file, ListNode *node, int *tekX, int *tekY){

    char curr;
    fscanf(file, "%c", &curr);

    //imaiki predvid che failut pochva s #       
    while(curr = "#"){
        fscanf(file, "%c", &curr);
        //linked list s hashtag->x = tekX i hashtag->y = tekY

        tekX++;
    }
    return node;  
    
}

int main(){

    int peshoJump = 0, policeJump = 0;
    ListNode *node;
    ListNode *linkedlist[16];
    int j = 0;
    hashtag* currHashtag;
    int x = 1,y = 1;
    input(&peshoJump, &policeJump);

    FILE *file = fopen("pesho.txt", "r");
    if (file == NULL) {
        printf("Couldnt open the file.\n");
        return 1;
    }

    for(int i = 1; i ; j++){
        linkedlist[j] = makeLinkedList(file, node, &x, &y);
    }

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
