#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
	char name[50];
	char surname[50];
	int birthYear;
	struct person* next;
}Person;

Person* createPerson(const char*, const char*, int);
void addToBeginning(Person**, const char*, const char*, int);
void printList(Person*);
void addToEnd(Person**, const char*, const char*, int);
Person* findBySurname(Person*, const char*);
void deletePerson(Person**, const char*);

int main() {
	Person* list = NULL;																		//initializes an empty linked list 

	addToBeginning(&list, "Ante", "Antic", 1976);												
	addToEnd(&list, "Petra", "Petric", 2000);													

	printList(list);																			//prints the initial list

	char needed[50];
	printf("Which surname do you need to find? \n");											//asking user which person they want to find
	scanf("%s", needed);


	Person* find = findBySurname(list,needed);
	if (find)
		printf("Person found: %s	%s	%d\n", find->name, find->surname, find->birthYear);
	else
		printf("Person not found.\n");


	char remove[50];
	printf("Which person do you need to remove? \n");											//asking user which person they want to remove							
	scanf("%s", remove);

	deletePerson(&list, remove);

	
	printList(list);																			//prints the changed list


	while (list != NULL) {																		//free allocated memory
		Person* temp = list;
		list = list->next;
		free(temp);
	}
}

Person* createPerson(const char* name, const char* surname, int year) {	
	Person* newPerson = (Person*)malloc(sizeof(Person));										//memory allocation
	
	strcpy(newPerson->name, name);																//copies given string into structs name
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = year;
	newPerson->next = NULL;																		//sets next pointer to NULL, last person is not linked to anything else

	return newPerson;
}

void addToBeginning(Person** head, const char* name, const char* surname, int year) {
	Person* newPerson = createPerson(name, surname, year);
	newPerson->next = *head;																	//points new person to current head of the list
	*head = newPerson;																			//new person becomes the first element
}

void addToEnd(Person** head, const char* name, const char* surname, int year) {
	Person* newPerson = createPerson(name,surname,year);

	Person* temp = *head;
	while (temp->next != NULL)
		temp = temp->next;																		//temp moves through the list until it finds the element that points to NULL
	temp->next = newPerson;
}

void printList(Person* head) {
	Person* temp = head;
	while (temp != NULL) {
		printf("% s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
}

Person* findBySurname(Person* head, const char* surname) {
	Person* temp = head;
	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void deletePerson(Person** head, const char* surname) {
	Person* temp = *head;
	Person* before = NULL;

	while (temp != NULL && strcmp(temp->surname, surname) != 0) {
		before = temp;
		temp = temp->next;
	}
	if (before == NULL) {
		*head = temp->next;
	}
	else {
		before->next = temp->next;
	}

}