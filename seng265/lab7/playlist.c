#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct list *next;
	int song;
}list;

int main(void){
	int numbers[3] = {1,2,3	};
	int list_size;
	int i;
	list *head = malloc(sizeof(list));
	list *data;
	list *conductor;
	
	for (i=0;i<3;i++){
		data = malloc(sizeof(list));
		data->song = numbers[i];
		data->next = head->next;
		head->next = data;
		list_size++;
	}
	
	conductor = head->next;
	printf("Currently there are %d songs in the list:\n",list_size);
	while (conductor!=NULL){
		printf("%d\n",conductor->song);
		conductor = conductor->next;
	}
	
	
	printf("Adding at element at the end...\n");
	data = malloc(sizeof(list));
	data->song = 4;
	data->next = head->next;
	head->next = data;
	list_size++;
	
	conductor = head->next;
	
	printf("Now there are %d songs in the list:\n",list_size);
	while (conductor!=NULL){
		printf("%d\n",conductor->song);
		conductor = conductor->next;
	}
	return 0;
}

	
