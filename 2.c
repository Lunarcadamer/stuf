/*
By Aloysius Chia (1547098)

DISM/FT/2A/21

Task 2: Sales Log Report
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct paymentNode {
    char method[16];
    double amount;
    struct paymentNode * next;
} P_NODE; // Defining paymentNode structure

typedef struct locationNode {
    char location[32];
    double amount;
    struct locationNode * next;
} L_NODE; // Defining locationNode structure

typedef struct timeNode {
    char time[5];
    double amount;
    struct timeNode * next;
} T_NODE; // Defining timeNode structure

P_NODE * insertPnode(P_NODE * headPtr, char * method, double amount) {
    // Function to generate linked list for storing payment information. Takes a linked list, payment method and amount.
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
} // Function to generate linked list for storing payment information. Takes a linked list, payment method and amount.

L_NODE * insertLnode(L_NODE * headPtr, char * location, double amount) {
    // Function to generate linked list for storing location information. Takes a linked list, location and revenue.
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
} // Function to generate linked list for storing location information. Takes a linked list, location and revenue.

T_NODE * insertTnode(T_NODE * headPtr, char * time, double amount) {
    // Function to generate linked list for storing sales hours information. Takes a linked list, time and revenue.
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
} // Function to generate linked list for storing sales hours information. Takes a linked list, time and revenue.

P_NODE * orderPnode(P_NODE * headPtr, char * method, double amount) {
    // Function to order payment method linked list in desecnding order
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
}   // Function to order payment method linked list in desecnding order

L_NODE * descendingLnode(L_NODE * headPtr, char * location, double amount) {
    // Function to order location linked list in desecnding order
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
} // Function to order location linked list in desecnding order

L_NODE * ascendingLnode(L_NODE * headPtr, char * location, double amount) {
    // Function to order location linked list in asecnding order
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
}   // Function to order location linked list in asecnding order

T_NODE * descendingTnode(T_NODE * headPtr, char * time, double amount) {
    // Function to order sales hours linked list in desecnding order
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
}   // Function to order sales hours linked list in desecnding order

T_NODE * ascendingTnode(T_NODE * headPtr, char * time, double amount) {
    // Function to order sales hours linked list in asecnding order
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
}   // Function to order sales hours linked list in asecnding order

void release_pNode(P_NODE * curPtr) {
    // Function to free the payment linked list
    if (curPtr == NULL) {
        return;
    }
    release_pNode(curPtr->next);
    free(curPtr);
    
}   // Function to free the payment linked list

void release_lNode(L_NODE * curPtr) {
    // Function to free the location linked list
    if (curPtr == NULL) {
        return;
    }
    release_lNode(curPtr->next);
    free(curPtr);
    
}   // Function to free the location linked list

void release_tNode(T_NODE * curPtr) {
    // Function to free the sales hour linked list
    if (curPtr == NULL) {
        return;
    }
    release_tNode(curPtr->next);
    free(curPtr);
    
}   // Function to free the sales hour linked list

void payment_summary(P_NODE * headPtr) {
    // Function to print payment methods summary
    P_NODE * workPtr = headPtr;
    P_NODE * payment = NULL;
    setlocale(LC_NUMERIC, "");
    char revenue[32];

    while (workPtr != NULL) {
        payment = orderPnode(payment, workPtr->method, workPtr->amount);

        workPtr = workPtr->next;
    }

    printf("\t==Payment Methods Summary==\n");

    while (payment != NULL) {
        revenue[0] = '$';
        sprintf(&revenue[1], "%'.2lf", payment->amount);
        printf("%15s : %20s \n",payment->method, revenue);
        payment = payment->next;
    }

    release_pNode(workPtr);
    release_pNode(payment);
}   // Function to print payment methods summary

void location_summary(L_NODE * headPtr) {
    // Function to print locations summary
    L_NODE * workPtr = headPtr;
    L_NODE * desclocation = NULL;
    L_NODE * asclocation = NULL;
    setlocale(LC_NUMERIC, "");
    char revenue[32];

    while (workPtr!= NULL) {
        desclocation = descendingLnode(desclocation, workPtr->location, workPtr->amount);
        asclocation = ascendingLnode(asclocation, workPtr->location, workPtr->amount);


        workPtr = workPtr->next;
    }

    printf("\t==Top Sales Stores Summary==\n");

    for (int i = 0; i < 3; i++) {
        revenue[0] = '$';
        sprintf(&revenue[1], "%'.2lf", desclocation->amount);
        printf("%15s : %20s \n", desclocation->location, revenue);
        desclocation = desclocation->next;
    }

    printf("\t==Weakest Sales Stores Summary==\n");

    for (int i = 0; i < 3; i++) {
        revenue[0] = '$';
        sprintf(&revenue[1], "%'.2lf", asclocation->amount);
        printf("%15s : %20s \n",asclocation->location, revenue);
        asclocation = asclocation->next;
    }

    release_lNode(workPtr);
    release_lNode(desclocation);
    release_lNode(asclocation);
} // Function to print locations summary

void time_summary(T_NODE * headPtr) {
    // Function to print sales hours summary
    T_NODE * workPtr = headPtr;
    T_NODE * desctimePtr = NULL;
    T_NODE * asctimePtr = NULL;
    setlocale(LC_NUMERIC, "");
    char revenue[32];

    while (workPtr != NULL) {
        desctimePtr = descendingTnode(desctimePtr, workPtr->time, workPtr->amount);
        asctimePtr = ascendingTnode(asctimePtr, workPtr->time, workPtr->amount);

        workPtr = workPtr->next;
    }

    printf("\t==Peak Hours Summary==\n");

    for (int i = 0; i < 3; i++) {
        revenue[0] = '$';
        sprintf(&revenue[1], "%'.2lf", desctimePtr->amount);
        printf("%15s : %20s \n",desctimePtr->time, revenue);
        desctimePtr = desctimePtr->next;
    }

    printf("\t==Quiet Hours Summary==\n");

    for (int i = 0; i < 3; i++) {
        revenue[0] = '$';
        sprintf(&revenue[1], "%'.2lf", asctimePtr->amount);
        printf("%15s : %20s \n",asctimePtr->time, revenue);
        asctimePtr = asctimePtr->next;
    }

    release_tNode(workPtr);
    release_tNode(desctimePtr);
    release_tNode(asctimePtr);
}   // Function to print sales hours summary

void main() {
    char str[257], date[10], time[5], location[32], item[32], card[32];
    double revenue;
    FILE * fp;
    fp = fopen("purchases.txt", "r");
    P_NODE * paymentPtr = NULL;
    L_NODE * locationPtr = NULL;
    T_NODE * timePtr = NULL;


    // Inserting File Data into linked lists
    while(fgets(str, 257, fp) != NULL) {
        sscanf(str, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%lf\t%s", date, time, location, item, &revenue, card);

        paymentPtr = insertPnode(paymentPtr, card, revenue);
        locationPtr = insertLnode(locationPtr, location, revenue);
        timePtr = insertTnode(timePtr, time, revenue);
    }

    fclose(fp);

    // Printing Summaries
    payment_summary(paymentPtr);
    location_summary(locationPtr);
    time_summary(timePtr);

    // Freeing the linked list after use
    release_pNode(paymentPtr);
    release_lNode(locationPtr);
    release_tNode(timePtr);
}   // Main
