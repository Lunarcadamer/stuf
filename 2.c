#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct paymentNode {
    char method[16];
    double amount;
    struct paymentNode * next;
} P_NODE;

typedef struct locationNode {
    char location[32];
    double amount;
    struct locationNode * next;
} L_NODE;

typedef struct timeNode {
    char time[5];
    double amount;
    struct timeNode * next;
} T_NODE;

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

    if (headPtr == NULL) {
        return newNode;
    }

    if (strcmp(headPtr->method, newNode->method) == 0 ) {
        headPtr->amount += newNode->amount;
        return headPtr;
    }

    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (strcmp(curPtr->method, newNode->method) == 0){           
            curPtr->amount += newNode->amount;
            return headPtr;
        }
        else {
            curPtr = curPtr->next;
            prevPtr = prevPtr->next;
        }
    }

    // Case 4: Append the newNode to the end
    prevPtr->next = newNode;

    /*                        */
    return headPtr;
}

L_NODE * insertLnode(L_NODE * headPtr, char * location, double amount) {
    L_NODE * prevPtr, * curPtr;
    L_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (L_NODE *)malloc(sizeof(L_NODE));
    strcpy(newNode->location, location);
    newNode->amount = amount;
    newNode->next = NULL;

    if (headPtr == NULL) {
        return newNode;
    }

    if (strcmp(headPtr->location, newNode->location) == 0 ) {
        headPtr->amount += newNode->amount;
        return headPtr;
    }

    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (strcmp(curPtr->location, newNode->location) == 0){           
            curPtr->amount += newNode->amount;
            return headPtr;
        }
        else {
            curPtr = curPtr->next;
            prevPtr = prevPtr->next;
        }
    }

    // Case 4: Append the newNode to the end
    prevPtr->next = newNode;

    /*                        */
    return headPtr;
}

T_NODE * insertTnode(T_NODE * headPtr, char * time, double amount) {
    T_NODE * prevPtr, * curPtr;
    T_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (T_NODE *)malloc(sizeof(T_NODE));
    if(time[3]<'3'){
        time[3] = '0';
        time[4] = '0';        
    }
    else {
        time[3] = '3';
        time[4] = '0';
    }
    strcpy(newNode->time, time);
    newNode->amount = amount;
    newNode->next = NULL;

    if (headPtr == NULL) {
        return newNode;
    }

    if (strcmp(headPtr->time, newNode->time) == 0 ) {
        headPtr->amount += newNode->amount;
        return headPtr;
    }

    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (strcmp(curPtr->time, newNode->time) == 0){           
            curPtr->amount += newNode->amount;
            return headPtr;
        }
        else {
            curPtr = curPtr->next;
            prevPtr = prevPtr->next;
        }
    }

    // Case 4: Append the newNode to the end
    prevPtr->next = newNode;

    /*                        */
    return headPtr;
}

P_NODE * orderPnode(P_NODE * headPtr, char * method, double amount) {
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

L_NODE * descendingLnode(L_NODE * headPtr, char * location, double amount) {
    L_NODE * prevPtr, * curPtr;
    L_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (L_NODE *)malloc(sizeof(L_NODE));
    strcpy(newNode->location, location);
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

L_NODE * ascendingLnode(L_NODE * headPtr, char * location, double amount) {
    L_NODE * prevPtr, * curPtr;
    L_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (L_NODE *)malloc(sizeof(L_NODE));
    strcpy(newNode->location, location);
    newNode->amount = amount;
    newNode->next = NULL;

    // Case 1
    if (headPtr == NULL) {
        return newNode;
    } 

    // Case 2
    if (headPtr->amount >= newNode->amount) {
        newNode->next = headPtr;
        return newNode;
    }

    // Case 3
    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (curPtr->amount >= newNode->amount){
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

T_NODE * descendingTnode(T_NODE * headPtr, char * time, double amount) {
    T_NODE * prevPtr, * curPtr;
    T_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (T_NODE *)malloc(sizeof(T_NODE));
    strcpy(newNode->time, time);
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

T_NODE * ascendingTnode(T_NODE * headPtr, char * time, double amount) {
    T_NODE * prevPtr, * curPtr;
    T_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (T_NODE *)malloc(sizeof(T_NODE));
    strcpy(newNode->time, time);
    newNode->amount = amount;
    newNode->next = NULL;

    // Case 1
    if (headPtr == NULL) {
        return newNode;
    } 

    // Case 2
    if (headPtr->amount >= newNode->amount) {
        newNode->next = headPtr;
        return newNode;
    }

    // Case 3
    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (curPtr->amount >= newNode->amount){
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

void release_pNode(P_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_pNode(curPtr->next);
    free(curPtr);
    
}

void release_lNode(L_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_lNode(curPtr->next);
    free(curPtr);
    
}

void release_tNode(T_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_tNode(curPtr->next);
    free(curPtr);
    
}

void payment_summary(P_NODE * headPtr) {
    P_NODE * workPtr = headPtr;
    P_NODE * payment = NULL;

    while (workPtr != NULL) {
        payment = orderPnode(payment, workPtr->method, workPtr->amount);

        workPtr = workPtr->next;
    }

    printf("\t==Payment Methods Summary==\n");

    while (payment != NULL) {
        printf("\t%-20s",payment->method);
        printf("$%7.2lf \n",payment->amount);
        payment = payment->next;
    }

    release_pNode(workPtr);
    release_pNode(payment);
}

void location_summary(L_NODE * headPtr) {
    L_NODE * workPtr = headPtr;
    L_NODE * desclocation = NULL;
    L_NODE * asclocation = NULL;

    while (workPtr!= NULL) {
        desclocation = descendingLnode(desclocation, workPtr->location, workPtr->amount);
        asclocation = ascendingLnode(asclocation, workPtr->location, workPtr->amount);


        workPtr = workPtr->next;
    }

    printf("\t==Top Sales Stores Summary==\n");

    for (int i = 0; i < 3; i++) {
        printf("\t%-20s",desclocation->location);
        printf("$%7.2lf \n",desclocation->amount);
        desclocation = desclocation->next;
    }

    printf("\t==Weakest Sales Stores Summary==\n");

    for (int i = 0; i < 3; i++) {
        printf("\t%-20s",asclocation->location);
        printf("$%7.2lf \n",asclocation->amount);
        asclocation = asclocation->next;
    }

    release_lNode(workPtr);
    release_lNode(desclocation);
    release_lNode(asclocation);
}

void time_summary(T_NODE * headPtr) {
    T_NODE * workPtr = headPtr;
    T_NODE * desctimePtr = NULL;
    T_NODE * asctimePtr = NULL;

    while (workPtr != NULL) {
        desctimePtr = descendingTnode(desctimePtr, workPtr->time, workPtr->amount);
        asctimePtr = ascendingTnode(asctimePtr, workPtr->time, workPtr->amount);

        workPtr = workPtr->next;
    }

    printf("\t==Peak Hours Summary==\n");

    for (int i = 0; i < 3; i++) {
        printf("\t%-20s",desctimePtr->time);
        printf("$%7.2lf \n",desctimePtr->amount);
        desctimePtr = desctimePtr->next;
    }

    printf("\t==Quiet Hours Summary==\n");

    for (int i = 0; i < 3; i++) {
        printf("\t%-20s",asctimePtr->time);
        printf("$%7.2lf \n",asctimePtr->amount);
        asctimePtr = asctimePtr->next;
    }

    release_tNode(workPtr);
    release_tNode(desctimePtr);
    release_tNode(asctimePtr);
}

void main() {
    char str[257], date[10], time[5], location[32], item[32], card[32];
    double revenue;
    FILE * fp;
    fp = fopen("purchases.txt", "r");
    P_NODE * paymentPtr = NULL;
    L_NODE * locationPtr = NULL;
    T_NODE * timePtr = NULL;

    if(fp == NULL) {
        printf("Error opening file");
    }


    while(fgets(str, 257, fp) != NULL) {
        sscanf(str, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%lf\t%s", date, time, location, item, &revenue, card);

        paymentPtr = insertPnode(paymentPtr, card, revenue);
        locationPtr = insertLnode(locationPtr, location, revenue);
        timePtr = insertTnode(timePtr, time, revenue);
    }

    fclose(fp);

    payment_summary(paymentPtr);
    location_summary(locationPtr);
    time_summary(timePtr);

    release_pNode(paymentPtr);
    release_lNode(locationPtr);
    release_tNode(timePtr);
}
