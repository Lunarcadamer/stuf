/*
By Aloysius Chia (1547098)

DISM/FT/2A/21

Task 1: Password Recovery

Permutations Algorithm adapted from Jules Olléon's answer at http://stackoverflow.com/questions/4764608/generate-all-strings-under-length-n-in-c
*/

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
	// Function to generate linked list for the program. Takes a linked list, a username and a hash.
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
}	// Function to generate linked list for the program. Takes a linked list, a username and a hash.

void release_nodes(S_NODE * curPtr) {
    if (curPtr == NULL) {
        return;
    }
    release_nodes(curPtr->next);
    free(curPtr);
    
}	// To clear the linked list after usage

char * getTime() {
	// Function to get current time, returns a formated time string
	time_t timer;
    struct tm* tm_info;
    static char timeStr[32];

    time(&timer);
    tm_info = localtime(&timer);

    strftime(timeStr, 26, "%Y:%m:%d %H:%M:%S", tm_info);

    return timeStr;

}	// Function to get current time, returns a formated time string

int inc(char *c){
	// Perumutation generating function
    if(c[0]==0) return 0;
    if(c[0]=='9'){
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}	// Perumutation generating function

int duplicateCheck(char * c, int length) {
	// Checking for duplicate characters in generated permutation, takes in a string and its length. Returns a 1 if a duplicate is detected.
    int i, j;
    for(i=0; i<=length; i++){
        for(j=i+1; j<=length; j++){
            if(c[i] == c[j]) {
                return 1;
            }
        }
    }
}	// Checking for duplicate characters in generated permutation, takes in a string and its length. Returns a 1 if a duplicate is detected.

void passwordCracker(S_NODE * rootPtr) {
	// Passwork cracking function, takes in a linked list with username and hash.
	char * result;
	int n = 6; // Max length of generated permutation
	int i, j;
	int len; // Length of generated permutation
	char *c = malloc((n+1)*sizeof(char)); // Generated permutation

	for(i=1;i<=n;i++){
    	for(j=0;j<i;j++) c[j]='0';
    	c[i]=0;
        
        do {
        	len = strlen(c);
        	if(duplicateCheck(c, len) != 1) { // Checking for duplicate characters, if no duplicates detected, use crypt() function
		   		result = crypt(c, rootPtr->hash);
		   		
				if(strcmp(result, rootPtr->hash) == 0) {	//if result == secret, strcmp returns 0
					// Store results into the node
					strcpy(rootPtr->recoveredPassword, c);
					strcpy(rootPtr->timeData, getTime());
					rootPtr = rootPtr->next;	// Move on to the next entry

					// Reseting perumutation loops
					i=1;
					j=0;
				}
			}

			if(rootPtr == NULL) {
				// Exits the loop once no more entries remain
				break;
			}

        } while(inc(c));
    }
}	// Passwork cracking function, takes in a linked list with username and hash.

int main() {
	printf("Program Started: %s \n", getTime());

	// Opening the file
	FILE * fp;
    fp = fopen("shadow.txt", "r");
    char str[150], username[10], hash[128];
    S_NODE * rootPtr = NULL;

    // Creating linked list with username and hashed password
    while(fgets(str, 150, fp) != NULL) {
        strcpy(username, strtok(str, ":"));
        strcpy(hash, strtok(NULL, ":"));
        
        rootPtr=insertNode(rootPtr, username, hash);
    }

    fclose(fp);

    S_NODE * headPtr = rootPtr; // Backup of original pointer
	

	// Password cracking begins
    passwordCracker(rootPtr);

    printf("Program Ended: %s \n\n", getTime());

    // Printing results
    while (headPtr != NULL) {
    	printf("User: %s Password: %6s recovered at [%s]\n", headPtr->username, headPtr->recoveredPassword, headPtr->timeData);
    	headPtr = headPtr->next;
    }

    // Freeing memory
    release_nodes(headPtr);
    release_nodes(rootPtr);

}	// Main
