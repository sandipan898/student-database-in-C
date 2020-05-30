#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	int roll, age,  p_year; 
	char name[30], dept[20], year[5];
	struct student *next;
}student;

student *s_head = NULL, *curr = NULL, *temp = NULL, *p = NULL;

void search_record(int, student*);
void show_record(student*);
student *store_record(student*);
student *edit_record(int, student*);
student *delete_record(int, student*);
student *new_student(void);
void save_into_file(student*);
student *get_from_file(void);

int main()
{
	int op, roll;
	while(1)
	{
		printf("\n<1> To Enter data.\n<2> To show all saved data.\n<3> To search a student data.\n<4> To edit record.\n<5> To delete data.\n<0> To Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &op);
		fflush(stdin);
		switch(op)
		{
			case 1: s_head = store_record(s_head);
					break;
			case 2: show_record(s_head);
					break;
			case 3: printf("\nEnter the roll number to search student data: ");
					fflush(stdin);
					scanf("%d", &roll);
					search_record(roll, s_head);
					break;
			case 4: printf("\nEnter the roll to edit data: ");
					scanf("%d", &roll);
					s_head = edit_record(roll, s_head);
					break;
			case 5: printf("\nEnter the roll to delete data: ");
					scanf("%d", &roll);
					s_head = delete_record(roll, s_head);
					break;
			case 0: printf("\nThank you for using our service made by Sandipan Das.\nVisit again.(press any key to end process.)\n");
					getchar();
					exit(0);
			default:printf("\nEnter the correct choice!");
		}
	}
	return 0;
}

student *store_record(student *s_head)
{
	char ch; 
	int i;
	FILE *fp;
	while(1)
	{
	    fp = fopen("student_database.txt", "a+");
	    if(fp == NULL)
	        printf("Cannot open file.");
	        
		printf("\nDo you want to add new student?(y/n): ");
		fflush(stdin);
		scanf("%c", &ch);
		if(ch == 'n' || ch == 'N')
			break;
		
		temp = new_student();
		printf("\nEnter student name: ");
		fflush(stdin);
		scanf("%[^\n]%*c", &temp->name);
		fprintf(fp, "\nName: %s\n", temp->name);
		//fputs(temp->name, fp);
		//gets(temp->name);
		
		printf("\nEnter student roll: ");
		scanf("%d", &temp->roll);
		fprintf(fp, "Roll: %d\n", temp->roll);
		
		fflush(stdin);
		printf("\nEnter the department: ");
		scanf("%[^\n]%*c", &temp->dept);
		//fputs(temp->dept, fp);
		//gets(temp->dept);
		fprintf(fp, "Dept: %s\n", temp->dept);
		
		printf("\nEnter the year of studying: ");
		scanf("%[^\n]%*c", &temp->year);
		fgets(temp->year, 5, fp);
        fprintf(fp, "Studying Year: %s\n", temp->year);
        
		printf("\nEnter the passout year: ");
		fflush(stdin);
		scanf("%d", &temp->p_year);
        fprintf(fp, "Passout Year: %d\n", temp->p_year);
        
		printf("\nEnter student age: ");
		scanf("%d", &temp->age);
		fprintf(fp, "Age: %d\n", temp->age);
		fclose(fp);
	
		if(s_head == NULL)
			s_head = temp;
		else
		{
			curr = s_head;
			while(curr->next!=NULL)
				curr = curr->next;
			curr->next = temp;
		}
	}
	return s_head;
}

void search_record(int r, student *s_head)
{
	printf("\n---------------Student Data-------------------\n");
	if(s_head == NULL)
		printf("\nNo data Found");
	else
	{
		curr = s_head;
		while(1)
		{
			if(curr == NULL)
			{
				printf("\nNo data Found with Roll %d", r);
				break;
			}
			if(curr->roll == r)
			{
				printf("\nName: %s", curr->name);
				printf("\nRoll: %d", curr->roll);
				printf("\nDepartment: %s", curr->dept);
				printf("\nStudying year: %s", curr->year);
				printf("\nPassing year: %d", curr->p_year);
				printf("\nAge: %d", curr->age);
				curr = curr->next;
				break;
			}
			curr = curr->next;
		}
	}
	printf("\n\n----------------------------------------------");
}

student *delete_record(int r, student *s_head)
{
	if(s_head == NULL)
	{
		printf("\nNo data to delete!!!\n");
		return s_head;		
	}
	curr = s_head;
	while(1)
	{
		if(curr->next == NULL && curr->roll == r)
		{
			free(curr);
			s_head = NULL;
			break;
		}
		
		if(curr->next->roll == r)
		{
			p = curr->next;
			curr->next = p->next;
			// p->next = NULL;
			free(p);
			break;
		}
		if(curr == NULL)
			break;
		curr = curr->next;
	}
	return s_head;
}

void show_record(student *s_head)
{
	curr = s_head;
	printf("\n---------------Student Data-------------------\n");
	if(s_head == NULL)
		printf("\nNo data Found");
	else
	{	
		while(1)
		{
			printf("\nName: %s", curr->name);
			printf("\nRoll: %d", curr->roll);
			printf("\nDepartment: %s", curr->dept);
			printf("\nStudying year: %s", curr->year);
			printf("\nPassing year: %d", curr->p_year);
			printf("\nAge: %d", curr->age);
			printf("\n");
			curr = curr->next;
			if(curr == NULL)
				break;
		}
	}
	printf("\n----------------------------------------------");
}

student *edit_record(int r, student *s_head)
{
	char item[7], ch;
	if(s_head == NULL)
		printf("\nNo data Found");
	else
	{
		curr = s_head;
		while(1)
		{
			if(curr == NULL)
			{
				printf("\nNo data Found with Roll %d", r);
				break;
			}
			if(curr->roll == r)
			{
				printf("\nName: %s", curr->name);
				printf("\nRoll: %d", curr->roll);
				printf("\nDepartment: %s", curr->dept);
				printf("\nStudying year: %s", curr->year);
				printf("\nPassing year: %d", curr->p_year);
				printf("\nAge: %d\n", curr->age);
				while(1)
				{
					printf("\nEnter the parameter name(in lowercase) to edit: ");
					fflush(stdin);
                    scanf("%[^\n]%*c", &item);
					fflush(stdin);
					if(!strcmp(item, "name"))
					{
						printf("\nEnter the new name: ");
						scanf("%[^\n]%*c", &curr->name);
					}
					if(!strcmp(item, "roll"))
					{
						printf("\nEnter the new roll: ");
						scanf("%d", &curr->roll);
					}
					if(!strcmp(item, "department"))
					{
						printf("\nEnter the new department name: ");
						scanf("%[^\n]%*c", &curr->dept);
					}
					if(!strcmp(item, "studying year"))
					{
						printf("\nEnter the new studying year: ");
						scanf("%[^\n]%*c", &curr->year);
						//gets(curr->year);
					}
					if(!strcmp(item, "passing year"))
					{
						printf("\nEnter the new passing year: ");
						scanf("%d", &curr->p_year);
					}
					if(!strcmp(item, "age"))
					{
						printf("\nEnter the new age: ");
						scanf("%d", &curr->age);
					}
					printf("Want to edit more?(y/n): ");
					fflush(stdin);
					scanf("%c", &ch);
					if(ch == 'N' || ch == 'n')
						break;
				}
				break;
			}
		}
	}
	return s_head;
}

student *new_student(void){
	temp = (student*)malloc(sizeof(student));
	temp->age = -1;
	// temp->name = NULL;
	temp->roll = -1;
	temp->next = NULL;
	return temp;
}

