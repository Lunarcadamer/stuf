#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h> // use -lcrypt option to compile this source
#include <time.h>
#include <stdlib.h>

typedef struct shadowNode {
    char username[32];
    char hash[128];
    struct shadowNode * next;
} S_NODE;

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

void print_words(S_NODE * headPtr) {
    S_NODE * workPtr = headPtr;
    while (workPtr != NULL) {
        printf("%s\n",workPtr->username);
        printf("%s\n",workPtr->hash);
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

void getTime() {
	time_t rawtime;
 	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	printf("%s \n", asctime(timeinfo));
}

int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='9'){
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}

int duplicateCheck(char * c, int length) {
    int i, j;
    for(i=0; i<=length; i++){
        for(j=i+1; j<=length; j++){
            if(c[i] == c[j]) {
                return 0;
            }
        }
    }
}

int main() {
	char * secret = "$6$1zBiKbLu$X6oL2XZX8QBSrz87ZNlZQbRIUK1rsfg49nF7EqBU2thM52LRuTjUeH8rchHO42GJQNbOrv4O4aCHBdrF0voTe/"; // Password Hash
	char * result;
	char * password;
	int n = 6; //Max length of Password
	int i, j; //Loop Integers
	int x = 1; //Number of hashes
	int len; //Length of guess
	char *c = malloc((n+1)*sizeof(char)); //Brute force guess
	
	printf("Program Started: ");
	getTime();

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
	
	for(i=1;i<=n;i++){
    	for(j=0;j<i;j++) c[j]='0';
    	c[i]=0;
        
        do {
        	len = strlen(c);
        	if(duplicateCheck(c, len) != 0) {
	        	//sprintf(password, "%s", c);
		   		result = crypt(c, secret);
		   		
				if(strcmp(result, secret) == 0) {	//if result = secret, strcmp returns 0
					printf("Password Retrieved: %s ", c);
					getTime();
					x++;
				}
			}

			if(x>1) {
				break;
			}

        } while(inc(c));
    }
    
    free(c);

    printf("Program Ended: ");
    getTime();
	/*
	for(i=0; i<999999; i++) {
		sprintf(password, "%d", i);
		result = crypt(password, secret);

		if (strcmp(result, secret)) {	//if result = secret, strcmp returns 0
				printf("%s\n", password);
		} else {
				printf("Password Retrieved: %s ", password);
				getTime();
				break;
		}
	}
	*/
}
