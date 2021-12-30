#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Tree{
	char letter;
	int freq;
	struct Tree *next;
	struct Tree *left, *right;
}node;
void PrintLink(struct Tree* head);
void PrintTree(struct Tree* root, int spacing);
void InsertFront(struct Tree** ptr_head, char new_data);
void sortedInsert(struct Tree** ptr_head, struct Tree* new_node);
void insertionSort(struct Tree** ptr_head);
void insertAfter(struct Tree* prev_node, int freq);
int main(){
	
	char str[20];
	int i = 1;
	
	node *head;
	node *tmp;
	
	printf("Enter the text:\t");
	gets(str);
	
	head = (node*)calloc(1,sizeof(node));
	head->next = NULL;
	head->freq = 1;
	head->letter = str[0];

	tmp = head;
	
	while(str[i] != '\0'){
		while( (tmp != NULL) && (tmp->letter != str[i])){
			tmp = tmp->next;	
		}	
		if(tmp == NULL){
			InsertFront(&head,str[i]);
		}else{
			tmp->freq++;
		}
		tmp = head;
		i++;	
	}
	printf("the list:\n");
	PrintLink(head);
	
	//insertion sort
	insertionSort(&head);
	printf("after sort:\n");
	PrintLink(head);
	//tree
	node *root;
	node *t1;
	node *t2;
	node *new_node;
	node *t3;
	node *fake_head;
	fake_head = head;

	while(fake_head->next->next != NULL && fake_head->next != NULL){
	
		t1 = fake_head;
		t2 = fake_head->next;
		fake_head = t2->next;
		t1->next = NULL;
		t2->next = NULL;
		new_node = (node *)malloc(sizeof(node));
		new_node->freq = t1->freq + t2->freq;
		new_node->left = t1;
		new_node->right = t2;
		new_node->letter = '*';
		
		if(new_node->freq < fake_head->freq){
			
			new_node->next = fake_head;
			fake_head = new_node;
		}else{
			t3 = fake_head;
			while(t3->next != NULL && t3->next->freq <= new_node->freq){
				t3 = t3->next;
			}
			new_node->next = t3->next;
			t3->next = new_node;
		}
		
	}
	if(fake_head->next->next == NULL){
		new_node = (node*)malloc(sizeof(node));
		new_node->freq = fake_head->freq + fake_head->next->freq;
		new_node->next = NULL;
		new_node->letter = NULL;
		new_node->left = fake_head;
		new_node->right = fake_head->next;
		root = new_node;
	}
	else{
		root =  fake_head;
	}	

	printf("the huffman tree:\n(sorry it's kind of sideways)\n");
	PrintTree(root, 0);

	return 0;	
	
}
void PrintLink(struct Tree* head){
	node *temp;
	temp = head;
	while (temp != NULL){
		printf("%d-%c\t", temp->freq,temp->letter);
		temp = temp->next;
	}
	printf("\n");
}
void PrintTree(struct Tree* root, int spacing){
	int i;
	if(root == NULL){
		return;
	}else{
		spacing += 5;
		PrintTree(root->right, spacing);
		for (i=5; i<spacing; i++){
			printf(" "); 
		}
		printf("%d-%c\n", root->freq, root->letter);
		PrintTree(root->left, spacing);	
	}
}
void InsertFront(struct Tree** ptr_head, char new_data) { 
	node* new_node = (node*)calloc(1,sizeof(node));
	new_node->letter = new_data; 
	new_node->freq = 1;
	new_node->next = (*ptr_head); 
	(*ptr_head) = new_node;
}
void sortedInsert(struct Tree** ptr_head, struct Tree* new_node){ 
	node* current; 
	/* Special case for the head end */
	if (*ptr_head == NULL || (*ptr_head)->freq >= new_node->freq){ 
		new_node->next = *ptr_head; 
		*ptr_head = new_node; 
	}else{ 
		/* Locate the node before the point of insertion */
		current = *ptr_head; 
		while (current->next!=NULL && current->next->freq < new_node->freq){ 
			current = current->next; 
		} 
		new_node->next = current->next; 
		current->next = new_node; 
	} 
}
void insertionSort(struct Tree **ptr_head){ 
	// Initialize sorted linked list 
	node *sorted = NULL; 
	// Traverse the given linked list and insert every 
	// node to sorted 
	node *current = *ptr_head; 
	while (current != NULL){
		// Store next for next iteration 
		node *next = current->next; 

		// insert current in sorted linked list 
		sortedInsert(&sorted, current); 

		// Update current 
		current = next; 
	} 
	// Update ptr_head to point to sorted linked list 
	*ptr_head = sorted; 
}
void insertAfter(struct Tree* prev_node, int freq){ 
    /*1. check if the given prev_node is NULL */ 
    if (prev_node == NULL)  
    {  
       printf("the given previous node cannot be NULL");        
       return;   
    }   
           
    /* 2. allocate new node */
    node* new_node =(node*) malloc(sizeof(node)); 
   
    /* 3. put in the data  */
    new_node->freq  = freq; 
	new_node->letter  = '*'; 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;  
   
    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node; 
} 

