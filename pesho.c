#include<stdio.h>
#include "utils/graph.h"
#include "linked-list.h"
#include "pesho.txt"

//graf impl.


void input(){
    printf("pesho");
    scanf("");
    printf("police");
    scanf("");
}

int main(){

    FILE *file = fopen("pesho.txt", "r");

    //fscanf() за четене записвам #(x, y);

    //vsqka platforma = linked list s broi elementi = nroq na #owete

    //vertex s data linked lista. t.e 16 linked list-a, za veski vertex

    //kato procheta # pravq linked list, prikluchva s purviq procheten space.

    //promenliva na koi red i koi simvol sum (x, y), zapisvam go na vseki #

    // smqtam razstoqniqta i gi slagam kato weight na edge-ovete

    input();

    return 0;
}