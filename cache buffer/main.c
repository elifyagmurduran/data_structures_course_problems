#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct LinkedList{  
   char data[20];
   int counter;
   struct LinkedList *next;
   struct LinkedList *prev;  
};
typedef struct LinkedList node;

void InsertFront(node* head, char tmp_str[20]);
void PrintLink(node* head);
void DeleteNode(node *temp);
char zero[1] = {'0'}; 

int main(){
	
	int thr, cap;
	char selection,tmp_str[20],filename[20];
	int el_ctr;
	
	node * head;
	node *tmp;
	
	
	
	printf("would you like to read from file or enter string? [f/s]");
	scanf("%c",&selection);
	while( (selection!='f') && (selection!='s') ){
	printf("wrong selection. try one of these: [f/s]");
	scanf("%c",&selection);
	}
	
	if(selection == 'f'){
		printf("you have chosen: file entering.\n");
		
			printf("enter the file name:\n");
			scanf("%s",filename);
		    FILE *fptr;
		    fptr = fopen(filename, "r"); 
		    
			
		
		
		    if (fptr == NULL){ 
		        printf("file failed to open.");
		    }else{ 
		        printf("file succesfully opened.");
		        
		        //ilk node u elden haz�rlama
		    	head = (node*)malloc(sizeof(node));
				head->next = NULL;
				tmp = head;
				fscanf(fptr,"%s",&tmp_str);
				tmp->prev = NULL;
				tmp->counter = 1;
				strcpy(tmp->data,tmp_str);
				tmp->next = NULL;
		        
		        while(fptr != NULL){
		        	fscanf(fptr,"%s",&tmp_str);
		        	
					//kalan i�lemler i�erde
		        	
		        	while( (tmp->next != NULL) && (strcmp(tmp_str,tmp->data) != 0) ){//dizide hala eleman varken ve al�nan eleman
						tmp = tmp->next;  											//s�radakiyle ayn� de�ilken diziyi gez
					}				
					
					//while bitme sebebine g�re yap�lacaklar
					
					if( strcmp(tmp_str,tmp->data) == 0 ){ //ayn�s� bulundu
						tmp->counter++;
						if(tmp->counter>thr){ //threshold u ge�tiyse silinmeli
							DeleteNode(tmp);
						}
					}else{ //dizide yok ba�a yeni eklenmeli
						InsertFront(head,tmp_str);
						//eklemeden sonra  capacity kontrolu
						el_ctr++;
						if(el_ctr>cap){
							while(tmp->next != NULL){
								tmp=tmp->next;
							}//son node a ilerlemek i�in
							DeleteNode(tmp);
						}
					}		
		        	
				}
		        printf("\ndata successfully read. file now closed.\n");
		        fclose(fptr);
		    } 
			printf("%s",tmp_str);
			      
			PrintLink(head);
		
			
		
		
		
	}else{
		
		printf("you have chosen: string entering.\n");
	
		printf("enter capacity value:\t");
		scanf("%d", &cap);
		printf("\nenter threshold value:\t");
		scanf("%d", &thr);
		
		printf("if you want to exit, please enter 0.\n");
	
		//head node elden haz�rlama
		
		head = (node*)malloc(sizeof(node));
		head->next = NULL;
		tmp = head;
		//ilk giri�
		printf("enter node:\n");
		gets(tmp_str);
		//bilgileri girme
		tmp->prev = NULL;
		tmp->counter = 1;
		strcpy(tmp->data,tmp_str);
		tmp->next = NULL;
	
		
		while( strcmp(tmp_str,zero) != 0 ){ //0 girilmiyorken de�er al�p i�lem yapmaya devam et
			gets(tmp_str);
			if( strcmp(tmp_str,zero) == 0 ){ //0 girildiyse bast�r ve program� bitir
				PrintLink(head);
				printf("end of program");
			}else{
				
				
				while( (tmp->next != NULL) && (strcmp(tmp_str,tmp->data) != 0) ){//dizide hala eleman varken ve al�nan eleman
					tmp = tmp->next;  											//s�radakiyle ayn� de�ilken diziyi gez
				}				
				
				//while bitme sebebine g�re yap�lacaklar
				
				if( strcmp(tmp_str,tmp->data) == 0 ){ //ayn�s� bulundu
					tmp->counter++;
					if(tmp->counter>thr){ //threshold u ge�tiyse silinmeli
						DeleteNode(tmp);
					}
				}else{ //dizide yok ba�a yeni eklenmeli
					InsertFront(head,tmp_str);
					//eklemeden sonra  capacity kontrolu
					el_ctr++;
					if(el_ctr>cap){
						while(tmp->next != NULL){
							tmp=tmp->next;
						}//son node a ilerlemek i�in
						DeleteNode(tmp);
					}
				}
			
			
			}
		}
	
		PrintLink(head);
		
			
		
		
	}
	
	printf("end of program.");

	//free memory

	return 0;
}
void PrintLink(node* head){ //bast�rma fonksiyonu
	node *tmp;
	tmp=head;
	while ((tmp->next!=NULL)){
		printf("%d,",tmp->counter);
		printf("%s\t<->\t",tmp->data);
		tmp = tmp->next;
	}
	printf("END\n");
}
void InsertFront(node* head, char tmp_str[20]){
	
	node* temp;
	node *newnode;
	temp = head;
	newnode = (node*)malloc(sizeof(node));
	temp->prev = newnode; //ba�taki node un onune yeni node aday� atan�r
	newnode->next = temp; //yeni node aday�n�n arkas�na eski ba� atan�r
	newnode->prev = NULL; //yeni node un onu bos yani null
	strcpy(head->data,tmp_str); //data giri�i
	head->counter = 1;
	head = newnode; //newnode art�k yeni head
}
void DeleteNode(node *temp){
	node *ptr;
	ptr = temp -> next;  //silinecek olan ptr 
    temp -> next = ptr -> next;  //ptr �n sonras� art�k temp in sonras�
    ptr -> next -> prev = temp;  // ptr �n sonras�ndaki eleman�n �ncesindeki elemana temp atan�rp
    free(ptr);   //ptr serbest
}
