#include <stdio.h>
#include <stdbool.h>
#define MAX 10
typedef unsigned int uint8;

int counter = 0, initialize = 0;
int global_id, global_year;
int global_subject[3] = {}; 
int global_grade[3] = {}; 
int* subject_ptr = global_subject; int* grade_ptr = global_grade;

struct SimpleDB
{
    int s_id, s_year, c1_id, c2_id, c3_id, c1_g, c2_g, c3_g;
    struct SimpleDB *next;
};

struct SimpleDB *head;
struct SimpleDB *current;
struct SimpleDB *one = NULL;
struct SimpleDB *two = NULL;
struct SimpleDB *three = NULL;
struct SimpleDB *four = NULL;
struct SimpleDB *five = NULL;
struct SimpleDB *six = NULL;
struct SimpleDB *seven = NULL;
struct SimpleDB *eight = NULL;
struct SimpleDB *nine = NULL;
struct SimpleDB *ten = NULL;

bool SDB_IsFull(void)
{
    if(counter == MAX)
        return 1;
    else
        return 0;
}

uint8 GetUsedSize(void)
{
    return counter;
}

bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{
    if(current != NULL && counter != MAX)
    {
        current->s_id = id;
        current->s_year = year;
        
        
        current->c1_id = *subjects;
        current->c1_g = *grades;
        
        *subjects++;
        current->c2_id = *subjects;
        *grades++;
        current->c2_g = *grades;
        
        *subjects++;
        current->c3_id = *subjects;
        *grades++;
        current->c3_g = *grades;
         
        current = current->next;
        counter++;
        return 1;
    }
    else
    {
        printf("Reached the limit!\n");
    }
}

void SDB_DeleteEntry(uint8 id)
{
    struct SimpleDB *tem = head, *pre;
     if(tem != NULL && tem->s_id == id)
    {
        head = tem->next;
        free(tem);
        counter--;
        return;
    }
    
    while(tem != NULL && tem->s_id != id)
    {
        pre = tem;
        tem = tem->next;
    }
    
    if(tem == NULL)
        return;
        
    pre->next = tem->next;
    free(tem);
    counter--;
    return;
}

bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades)
{
    struct SimpleDB *temp = head, *prev;
    
    if(temp != NULL && temp->s_id == id)
    {
        *year = temp->s_year;
        
        *subjects = temp->c1_id;
        *grades = temp->c1_g;
        
        *subjects++;
        *subjects = temp->c2_id;
        *grades++;
        *grades = temp->c2_g; 
        
        *subjects++;
        *subjects = temp->c3_id;
        *grades++;
        *grades = temp->c3_g; 
        return;
    }
    
    while(temp != NULL && temp->s_id != id)
    {
        temp = temp->next;
    }
    
    if(temp == NULL)
    {
        *year = 0;
        
        *subjects = 0;
        *grades = 0;
        
        *subjects++;
        *subjects = 0;
        *grades++;
        *grades = 0; 
        
        *subjects++;
        *subjects = 0;
        *grades++;
        *grades = 0; 
        return;
    }
        
    *year = temp->s_year;
    
    *subjects = temp->c1_id;
    *grades = temp->c1_g;
    
    *subjects++;
    *subjects = temp->c2_id;
    *grades++;
    *grades = temp->c2_g; 
    
    *subjects++;
    *subjects = temp->c3_id;
    *grades++;
    *grades = temp->c3_g;
}

void SDB_GetidList(uint8* count, uint8* list)
{
    struct SimpleDB *temp = head;
    for(int i = 0; i < counter; i++)
    {
        *list = temp->s_id;
        *list++;
        temp = temp->next;
    }
}

bool SDB_IsIdExist(uint8 id)
{
    struct SimpleDB *temp = head;
    for(int i = 0; i < counter; i++)
    {
        if(temp != NULL && temp->s_id == id)
        {
        return 1;
        break;
        }
        temp = temp->next;
    }
    return 0;
}

void store_entry(void)
{
    printf("Student ID: "); scanf("%d", &global_id);
    printf("\nStudent Year: "); scanf("%d", &global_year);
    for(int i = 0; i < 3; i++)
    {
        printf("\nCourse_%d ID: ", i + 1); 
        scanf("%d", &global_subject[i]);
        printf("\nCourse_%d Grade: ", i + 1); 
        scanf("%d", &global_grade[i]);
        if(global_grade[i] < 0 || global_grade[i] > 100)
        {
            printf("REPEAT\nCourse_%d Grade: ", i + 1); scanf("%d", &global_grade[i]);
        }
    }
}

int main() 
{
    one = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    two = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    three = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    four = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    five = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    six = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    seven = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    eight = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    nine = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    ten = (struct SimpleDB *)malloc(sizeof(struct SimpleDB));
    
    one->next = two;
    two->next = three;
    three->next = four; 
    four->next = five;
    five->next = six;
    six->next = seven;
    seven->next = eight;
    eight->next = nine;
    nine->next = ten;
    ten->next = NULL;
    
    head = one;
    current = head;
    
    printf("Hello!\nKindly enter the options you need:\nPress 1 for SDB_IsFull\nPress 2 for GetUsedSize\nPress 3 for SDB_AddEntry\nPress 4 for SDB_DeleteEntry\nPress 5 for SDB_ReadEntry\nPress 6 for SDB_GetidList\nPress 7 for SDB_IsIdExist\n\n");
    
    while(1)
    {
        int option = 0, input = 0, list[MAX] = {};
        scanf("%d", &option);
        
        switch(option)
        {
            case 1: SDB_IsFull(); (SDB_IsFull() == 1) ? printf("FULL\n\n") : printf("NOT FULL\n\n"); break;
            
            case 2: GetUsedSize(); printf("%d\n\n", GetUsedSize()); break;
            
            case 3: store_entry(); int status = SDB_AddEntry(global_id, global_year, subject_ptr, grade_ptr); (status == 1) ? printf("ADDED\n\n") : printf("ERROR\n\n"); break;
            
            case 4: printf("ID: "); scanf("%d", &input); SDB_DeleteEntry(input); printf("DELETED\n\n"); break;
            
            case 5: printf("ID: "); scanf("%d", &input); SDB_ReadEntry(input, &global_year, subject_ptr, grade_ptr); printf("Student Year: %d", global_year); for(int i = 0; i< 3; i++){ printf("\nCourse_%d ID:: %d\nCourse_%d Grade: %d", i+1, global_subject[i], i+1, global_grade[i]);} printf("\n\n"); break;
            
            case 6: SDB_GetidList(&counter, list); printf("Number of entries: %d", counter); for(int i = 0; i < counter; i++){ printf("\nStudent %d ID: %d", i+1, list[i]);} printf("\n\n"); break;
            
            case 7: printf("ID: "); scanf("%d", &input);(SDB_IsIdExist(input) == 1) ? printf("EXIST\n\n") : printf("NOT EXIST\n\n"); break;
        }
    }
    return 0;
}