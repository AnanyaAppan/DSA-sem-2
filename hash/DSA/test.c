#include <stdio.h>
#include <stdlib.h>

int main(){
	// reading input
	char *strings[200];
	int lengths[200];
	   	
	char *line = NULL;
	size_t len = 0;
	
	FILE *fp = fopen("small_input1", "r");
	if(fp == NULL){
		printf("File does not exist\n");
		return 0;
	}
	
	int n = 0;
	while((lengths[n] = getline(&line, &len, fp)) != -1){
		strings[n] = (char *) malloc(lengths[n] * sizeof(char));
		
		int i;
		for(i = 0; i < lengths[n]-1; i++) strings[n][i] = line[i];
		strings[n][lengths[n]-1] = '\0';
		
		n++;
	}
	
	fclose(fp);
	// finished reading input
	
	// TODO write YOUR code here
	// n is the total number of strings
	// strings[i] is the i'th string
	// lengths[i] is the length of the i'th string

	return 0;
}
