#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct salesNode {
    char date[32];
    char time[32];
    char location[64];
    char item[64];
    double revenue;
    char card[32];
    struct salesNode * next;
} S_NODE;

typedef struct paymentNode {
    char method[32];
    double amount;
    struct paymentNode * next;
} P_NODE;

S_NODE * insertNode(S_NODE * headPtr, char * date, char * time, char * location, char * item, double revenue, char * card) {
    S_NODE * prevPtr, * curPtr;
    S_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (S_NODE *)malloc(sizeof(S_NODE));
    strcpy(newNode->date, date);
    strcpy(newNode->time, time);
    strcpy(newNode->location, location);
    strcpy(newNode->item, item);
    newNode->revenue = revenue;
    strcpy(newNode->card, card);

    newNode->next = NULL;

    // Case 1
    if (headPtr == NULL) {
        return newNode;
    }
    // Case 2
    if (strcmp(headPtr->date, newNode->date) >= 0 ) {
        if(strcmp(headPtr->time, newNode->time) >=0 ){
            newNode->next = headPtr;
            return newNode;
        }
    }

    // Case 3
    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (strcmp(curPtr->date, newNode->date) >= 0){
            if(strcmp(curPtr->time, newNode->time) >=0) {
                newNode->next = curPtr;
                prevPtr->next = newNode;
                return headPtr;
            }
        }
        curPtr = curPtr->next;
        prevPtr = prevPtr->next;
    }

    // Case 4: Append the newNode to the end
    prevPtr->next = newNode;

    /*                        */
    return headPtr;
}

P_NODE * insertPnode(P_NODE * headPtr, char * method, double amount) {
    P_NODE * prevPtr, * curPtr;
    P_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (P_NODE *)malloc(sizeof(P_NODE));
    strcpy(newNode->method, method);
    newNode->amount = amount;
    newNode->next = NULL;

    // Case 1
    if (headPtr == NULL) {
        return newNode;
    }
    // Case 2
    if (headPtr->amount <= newNode->amount) {
        newNode->next = headPtr;
        return newNode;
    }

    // Case 3
    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (curPtr->amount <= newNode->amount){
            newNode->next = curPtr;
            prevPtr->next = newNode;
            return headPtr;
        }
        curPtr = curPtr->next;
        prevPtr = prevPtr->next;
    }

    // Case 4: Append the newNode to the end
    prevPtr->next = newNode;

    /*                        */
    return headPtr;
}

void print_words(S_NODE * headPtr) {
    S_NODE * workPtr = headPtr;
    while (workPtr != NULL) {
        printf("%s ",workPtr->date);
        printf("%s ",workPtr->time);
        printf("%-15s ",workPtr->location);
        printf("%-20s ",workPtr->item);
        printf("%7.2lf ",workPtr->revenue);
        printf("%s \n",workPtr->card);
        workPtr = workPtr->next;
    }
}

void release_words(S_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_words(curPtr->next);
    free(curPtr);
    
}

void payment_methods(S_NODE * headPtr) {
    double amount[5];
    char * name[5] = {"Amex", "Cash", "Discover", "MasterCard", "Visa"};
    S_NODE * workPtr = headPtr;
    P_NODE * payment = NULL;
    while (workPtr != NULL) {
        if (strcmp(workPtr->card, "Amex") == 0) {
            amount[0]+=workPtr->revenue;
        }
        if (strcmp(workPtr->card, "Cash") == 0) {
            amount[1]+=workPtr->revenue;
        }
        if (strcmp(workPtr->card, "Discover") == 0) {
            amount[2]+=workPtr->revenue;
        }
        if (strcmp(workPtr->card, "MasterCard") == 0) {
            amount[3]+=workPtr->revenue;
        }
        if (strcmp(workPtr->card, "Visa") == 0) {
            amount[4]+=workPtr->revenue;
        }
        workPtr= workPtr->next;
    }

    for(int i = 0; i <= 4; i++) {
        payment = insertPnode(payment, name[i], amount[i]);
    }

    printf("\t==Payment Methods Summary==\n");

    while (payment != NULL) {
        printf("\t%-20s",payment->method);
        printf("%7.2lf \n",payment->amount);
        payment = payment->next;
    }
}

void main() {
    char str[257], date[10], time[5], location[32], item[32], card[32];
    double revenue;
    FILE * fp;
    fp = fopen("small_purchases.txt", "r");
    S_NODE * rootPtr = NULL;

    while(fgets(str, 257, fp) != NULL) {
        sscanf(str, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%lf\t%s", date, time, location, item, &revenue, card);

        rootPtr=insertNode(rootPtr, date, time, location, item, revenue, card);
    }

    fclose(fp);
    print_words(rootPtr);
    payment_methods(rootPtr);
    release_words(rootPtr);
}
