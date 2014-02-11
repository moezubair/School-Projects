#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum status  {fulltime,parttime,unregistered}Status;
typedef	enum degree  {undergrad,masters,phd,nondegree, diploma}Degree;
typedef struct course{
	char name[20];
	int number;
	char department[20];
}Course;
typedef struct student{
	char name[10];
	int number;
	Status status;
	Degree type;
	Course courses[6];
}Student;
typedef struct system{
	Student students[64];
	Course classes[64];
}System;
int addStudent(char name[10], int number, Status status_, Degree type,System* system);
int removeStudent(char name[10], int number,System* system);
int addCourse(char name[20], int number, char department[20],System* system);
int removeCourse(char name[10], int number,System* system);
int AddCourseToStudent(Student student_, Course class);

int main(void){
	int selection;	/*get users selection*/
	char newline;
	char name[10];
	int number;
	Status stat;
	int degree_type;
	System system;
		fprintf(stdout,"Selections:\n1:Add Student\n2:Remove Student\n3:Add Course\n4:Remove Course\n5:Add course to student\n0:Exit\n");
	do{

		scanf("%d",&selection);
		scanf("%c",&newline);
		fprintf(stdout,"You selected: %d\n",selection,newline);
		if (selection==1){
			fprintf(stdout, "Enter a name: ");
			scanf("%10s",name);
			fprintf(stdout, "Enter Student Number: ");
			scanf("%d",&number);
			stat = fulltime;
			fprintf(stdout, "Enter Degree type: ");
			scanf("%1d",&degree_type);
			fprintf(stdout, "Adding a Student now...\n");
			addStudent(name,number,stat,degree_type,&system);
			removeStudent(name,number,&system);
		}
	}while (selection!=0);
	return 0;
}
int addStudent(char name[10],int number, Status status_, Degree type,System* system){

	int i=0;
	while(system->students[i].number!=0){
		i++;
	}
	strncpy(system->students[i].name,name,10);
	system->students[i].number = number;
	system->students[i].status = status_;
	system->students[i].type = type;
}
int removeStudent(char name[10], int number,System *system){
	int i=0;
	while ((system->students[i].number!=number) || (strncmp(system->students[i].name,name,10)!=0) ){
		if (i>=64){
			fprintf(stdout,"Can't find this user...");
			return -1;
		}
		i++;
	}
	printf("Removing the student %s from index %d:\n",system->students[i].name,i);
}
int addCourse(char name[10], int number, char department[20],System* system){
	int i=0;
	while(system->classes[i].number!=0){
		i++;
	}
	strncpy(system->classes[i].name,name,20);
	system->students[i].number = number;
	strncpy(system->classes[i].department,department,20);
}
	
