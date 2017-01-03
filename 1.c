#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h> // use -lcrypt option to compile this source
#include <time.h>
#include <stdlib.h>

typedef struct shadowNode {
    char username[32];
    char hash[128];
    char recoveredPassword[64];
    char timeData[26];
    struct shadowNode * next;
} S_NODE;	// Defining node structure

S_NODE * insertNode(S_NODE * headPtr, char * new_user, char * new_hash) {
    S_NODE * prevPtr, * curPtr;
    S_NODE * newNode ;
    /*
    1.  The headPtr is initially NULL
    2.  Just append the new Node to the end.
    */
    /* always set up a new Node */
    newNode = (S_NODE *)malloc(sizeof(S_NODE));
    strcpy(newNode->username, new_user);
    strcpy(newNode->hash, new_hash);
    newNode->next = NULL;

    // Case 1
    if (headPtr == NULL) {
        return newNode;
    }
    // Case 2
    if (strcmp(headPtr->username, newNode->username) >= 0 ) {
        newNode->next = headPtr;
        return newNode;
    }

    // Case 3
    prevPtr = headPtr;
    curPtr = headPtr->next;
    while (curPtr != NULL) {
        // test if I should insert the newNode in front of the curPtr node.
        if (strcmp(curPtr->username, newNode->username) >= 0){
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

void release_words(S_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_words(curPtr->next);
    free(curPtr);
    
}	// To clear the linked list after usage

char * getTime() {
	time_t timer;
    struct tm* tm_info;
    static char timeStr[32];

    time(&timer);
    tm_info = localtime(&timer);

    strftime(timeStr, 26, "%Y:%m:%d %H:%M:%S", tm_info);

    return timeStr;

}	// Function to print time

int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='9'){
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}	// Perumutations function

int duplicateCheck(char * c, int length) {
    int i, j;
    for(i=0; i<=length; i++){
        for(j=i+1; j<=length; j++){
            if(c[i] == c[j]) {
                return 0;
            }
        }
    }
}	// Checking for duplicate characters in generated guess

int main() {
	char * result;
	int n = 6; //Max length of Password
	int i, j; //Loop Integers
	int len; //Length of guess
	char *c = malloc((n+1)*sizeof(char)); //Brute force guess

	printf("Program Started: %s \n", getTime());

	FILE * fp;
    fp = fopen("shadow.txt", "r");
    char str[150], username[10], hash[128];
    S_NODE * rootPtr = NULL;

    while(fgets(str, 150, fp) != NULL) {
        strcpy(username, strtok(str, ":"));
        strcpy(hash, strtok(NULL, ":"));
        
        rootPtr=insertNode(rootPtr, username, hash);
    }

    fclose(fp);

    S_NODE * headPtr = rootPtr; // Backup of original pointer
	
	for(i=1;i<=n;i++){
    	for(j=0;j<i;j++) c[j]='0';
    	c[i]=0;
        
        do {
        	len = strlen(c);
        	if(duplicateCheck(c, len) != 0) {
		   		result = crypt(c, rootPtr->hash);
		   		
				if(strcmp(result, rootPtr->hash) == 0) {	//if result = secret, strcmp returns 0
					//printf("User: %s Password: %6s recovered at [%s]\n", rootPtr->username, c, getTime());
					strcpy(rootPtr->recoveredPassword, c);
					strcpy(rootPtr->timeData, getTime());
					rootPtr = rootPtr->next;
					i=1;
					j=0;
				}
			}

			if(rootPtr == NULL) {
				break;
			}

        } while(inc(c));
    }

    printf("Program Ended: %s \n\n", getTime());

    while (headPtr != NULL) {
    	printf("User: %s Password: %6s recovered at [%s]\n", headPtr->username, headPtr->recoveredPassword, headPtr->timeData);
    	headPtr = headPtr->next;
    }

    release_words(headPtr);
    release_words(rootPtr);

}	// Main
