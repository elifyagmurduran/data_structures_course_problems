#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define DIF ('a'-'A')
int main(){
	struct timeval stop, start;
	gettimeofday(&start, NULL);	
	
	int i, j, k, l, n, x;
	char selection;
	
	int found = 0;
	int foundindex[20];
	
	char filename[25];
	
	char text[350];
	
	char pattern[50]; 
	char replacement[50];
	
	int difference;
	
	int bmv[30];
	char bml[30]; 
	
	FILE *fptr;
	
	//get file name and open file
	printf("enter the file to be read:\t");
	scanf("%s", &filename);
	fptr = fopen(filename,"r");
	if(fptr == NULL){
		printf("error open file");
		exit(1);
	}
	fgets(text,350,fptr);
	fclose(fptr);
	//get pattern &  replacement
	printf("\nenter the pattern to be searched:");
	gets(pattern);
	gets(pattern);
	printf("\nenter the replacement:");
	gets(replacement);
	//checking case sensitivity
	printf("\nwill it be case sensitive? [y/n]\t");
	selection = getchar();
	while( (selection != 'y') && (selection != 'n') ){
		printf("wrong selection, please choose [y/n]:\t");
		selection = getchar();
		printf("\n");
	}
	printf("the text:\n");
	puts(text);
	if(selection == 'y'){
		
		n = strlen(pattern);
		
		bml[0] = '*';
		bmv[0] = n;
		x = 1;
		
		for(i=0;i<n;i++){
			j = 0;
			while( (bml[j] != pattern[i]) && (j < x)){
				j++;
			}
			if( j < x ){
				bml[j] = pattern[i];
			}else{
				x++;
				bml[j] = pattern[i];
			}
			k = n - i - 1;
			if(k>1){
				bmv[j] = k;
			}else{
				bmv[j] = 1;
			}
		}
		
	}
	if(selection == 'n'){
		n = strlen(pattern);
		
		bml[0] = '*';
		bmv[0] = n;
		x = 1;
		
		for(i=0;i<n;i++){
			j = 0;
			while( bml[j] != pattern[i]  &&  (j < x) ){
				j++;
			}
			if( j < x ){
				bml[j] = pattern[i];
			}else{
				x++;
				bml[j] = pattern[i];
			}
			k = n - i - 1;
			if(k>1){
				bmv[j] = k;
			}else{
				bmv[j] = 1;
			}
		}
		
		for(i=0;i<x-1;i++){
			for(j=0;j<x;j++){
				if((bml[i] == bml[j] + DIF) || (bml[j] == bml[i] + DIF)){
					if(i>j){
						bmv[j] = bmv[i];
					}else{
						bmv[i] = bmv[j];
					}
				}
			}
		}
	}
	printf("the badmatch table:\n");
	for(i=0;i<x;i++){
		printf("%c,%d\n", bml[i],bmv[i]);
	}
	printf("x is length of badmatch table %d n is length of pattern %d\n",x,n);
	//finding
	j = n - 1;
	i = n - 1;
	l = 0;
	while(i < strlen(text)){
		while(j >= 0){
			if(text[i] == pattern[j]){
				j--;
				i--;
			}else{
				j = n - 1;
				k = 1;
				while( (text[i] != bml[k]) && (k < x) ){
					k++;
				}
				if(k == x){
					i = i + bmv[0];
				}else{
					i = i + bmv[k];
				}
			}
		}
		if(j < 0){
			found++;
			foundindex[l] = i + 1;
			l++;
			j = n - 1;
			i = i + bmv[0];
		}
	}
	//replacing
	difference = strlen(pattern) - strlen(replacement);
	if(difference == 0){
		for(l=0;l<found;l++){
			k = foundindex[l];
			for(i=0;i<strlen(replacement);i++){
				text[k] = replacement[i];
				k++;
			}
		}
	}
	if(difference < 0){
		for(l=0;l<found;l++){
			difference = strlen(pattern) - strlen(replacement);
			k = foundindex[l];
			j = strlen(text) - 1;
			while(j>k){
				text[j] = text[j + difference];
				j--;
			}
			for(i=0;i<strlen(replacement);i++){
				text[k] = replacement[i];
				k++;
			}
		}
	}
	if(difference > 0){
		for(l=0;l<found;l++){
			difference = strlen(pattern) - strlen(replacement);
			k = foundindex[l];
			for(i=0;i<strlen(replacement);i++){
				text[k] = replacement[i];
				k++;
			}
			k++;
			while(k<strlen(text)){
				text[k+difference] = text[k];
			}
			
		}
	}
	printf("new text\n");
	puts(text);
	printf("found and replaced %d.\n",found);
	fptr = fopen(filename,"w");
	fputs(text,fptr);
	fclose(fptr);
	printf("new text added to file. end of program.\n");
	gettimeofday(&stop, NULL);
	printf("run time: %f milliseconds.\n", 1000*((double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec)));
	return 0;
}
