/*Pablo Velazquez
 * This program is my work and not the work of others.
 * This program counts the number of words and optionally finds the longest and 
 * or shortest words in a string input by the user or coming from a file. Using the
 * command line and the usage statement .\countwords.exe [-l] [-s] [filename] if the user
 * doesn't enter a filename then the user will be prompted to enter a string.
 */

/* TO DO: 
	Only first line of file is read, this is because fgets ends when newline is detected,
	could make it get every line until end of file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void printshort(char sentencecopy[]){ //find and print the shortest word
    char line[1000];
    strncpy(line, sentencecopy, 1000); //since strtok modifies the string, use a copy
    char *tokens;
    tokens = strtok (line," ,;.!?-\n\0\t");
    char *shortest = tokens; //initialize shortest with the first token
    
    while(tokens != NULL){
		if(strlen(tokens) < strlen(shortest)){ //compare with shortest and change when true
			shortest = tokens;
		}
		tokens = strtok(NULL," ,;.!?-\n\0\t"); //go to next token
	}
    printf("shortest word: %s\n", shortest);
}


void printlong(char sentencecopy[]){ //find and print the longest word
    char line[1000];
    strncpy(line, sentencecopy, 1000);
    char *tokens;
    tokens = strtok (line," ,;.!?-\n\0\t");
    char *longest = tokens;

    while(tokens != NULL){
		if(strlen(tokens) > strlen(longest)){
			longest = tokens;
		}
		tokens = strtok(NULL," ,;.!?-\n\0\t");
    }
    printf("longest word: %s\n", longest);
}

int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int x; 
	int lflag=0, sflag=0; 
	char filename[100];
	char *tokens;
	char sentence[1000];
	char sentencecopy[1000];
	int count = 0;
	FILE* inputfile;
	static char usage[] = "usage: countwords [-l] [-s] [filename]\n";
	
	while ((x = getopt(argc, argv, "ls")) != -1){
	    switch (x) {
			case 'l':
				lflag = 1;
				break;
			case 's':
				sflag = 1;
				break;
	   }
	}	 	
	if (optind < argc){//get filename if user entered it
	    for (x = 0; optind < argc; optind++){
	    	sscanf(argv[optind], "%s", filename);//store the filename
	    }

	    if(!(inputfile = fopen(filename, "r"))){ //if file can't open, display error and usage statement
			printf("Error, file not found!\n");
			fprintf(stderr, usage, argv[0]);
			exit(1);
	    }

	    fgets(sentence, sizeof sentence, inputfile); //get contents of file and store in sentence
	    
	    fclose(inputfile); //close file
	}
	else { //if user does not enter a filename, get string from stdin
	    printf("Please enter the string you would like to process(press enter when done):\n");
	    fgets(sentence, sizeof sentence, stdin);
	}
		
	strncpy(sentencecopy, sentence, 1000); //since strtok modifies string, make copy to preseve original
	
	tokens = strtok (sentence," ,;.!?-\n\0\t"); //tokenize sentence 
	while(tokens != NULL){//count the total number of words
	    tokens = strtok(NULL," ,;.!?-\n\0\t");
	    count++;
	}

	printf("word count: %i\n", count);//print word count
	if(sflag == 1){
	    printshort(sentencecopy);
	}
	
	if(lflag == 1){
	    printlong(sentencecopy);
	}
	
	exit(0);
}
