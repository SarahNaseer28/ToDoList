#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include"TodoADT.h"
#define MAX 50



void printCLIUsage()
{

    printf("Usage:-\n");
    printf("$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n");
    printf("$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n");
    printf("$ ./task del INDEX            # Delete the incomplete item with the given index\n");
    printf("$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n");
    printf("$ ./task help                 # Show usage\n");
    printf("$ ./task report               # Statistics\n");

}

int listItems(struct Tasks TaskItems[])  //prints all the tasks and returns the no of items listed
{   
    FILE *fptr;
    char line[MAX];
    int i,k,j;
    i=0,k=0;

    fptr=fopen("..\\task.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].priority=atoi(&line[j]);
        TaskItems[i].status=0;

        for(j=2;line[j]!='\0' && line[j]!='\n';j++)          
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;
    }
    fclose(fptr);


    //now print them 
    for(i=0;i<TaskItems[0].numberTasks;i++)
    {
        if(TaskItems[i].status==0)
        {
            printf("%d. %s [%d]\n",i+1,TaskItems[i].label,TaskItems[i].priority);
        }
    }

    return i;
}

void addItem(struct Tasks TaskItems[],char * label1,int priority1)
{
    FILE *fptr;
    char line[MAX];
    int i,k,j,lineNum=0;
    int linesWritten;
    i=0,k=0;

    fptr=fopen("..\\task.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].priority=atoi(&line[j]);
        TaskItems[i].status=0;

        for(j=2;line[j]!='\0' && line[j]!='\n';j++)           
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;
    }
    fclose(fptr);

    //check priority and add accordingly
    for(i=0;i<TaskItems[0].numberTasks;i++)
    {
        if(priority1<TaskItems[i].priority)
        {   
            lineNum=i;break;
        }
    }   
    lineNum=i;
    TaskItems[0].numberTasks++; //increment tasks because there is a new task 

    //add it to the structure.
    for(int j=TaskItems[0].numberTasks-1;j>=lineNum;j--)     //shift the elements 
    {
        strcpy(TaskItems[j].label,TaskItems[j-1].label);
        TaskItems[j].priority=TaskItems[j-1].priority;
        TaskItems[j].status=TaskItems[j-1].status;
        TaskItems[j].numberTasks=TaskItems[0].numberTasks;
    }

    strcpy(TaskItems[lineNum].label,label1);
    TaskItems[lineNum].priority=priority1;
    TaskItems[lineNum].status=0;
    TaskItems[lineNum].numberTasks=TaskItems[0].numberTasks;

    fptr=fopen("..\\task.txt","w");

    if (fptr == NULL)
    {
        perror("error");printf("failed to open file.\n");exit(1);
    }

    for (int i = 0; i < TaskItems[0].numberTasks; i++)
    {
        if(TaskItems[i].status==0)
        {
            sprintf(line,"%d %s\n",TaskItems[i].priority,TaskItems[i].label);
            if((linesWritten=fputs(line,fptr))<0)
            {
                printf("Cannot add task to the File.\n");return;
            }
        }
    }

    printf("Added task: \"%s\" with priority %d\n",label1,priority1);

    fclose(fptr);
}

void deleteItem(struct Tasks TaskItems[],int index)
{   
    FILE *fptr;
    char line[MAX];
    int i,k,j;
    int linesWritten;

    i=0,k=0;

    fptr=fopen("..\\task.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].priority=atoi(&line[j]);
        TaskItems[i].status=0;

        for(j=2;line[j]!='\0' && line[j]!='\n';j++)           
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;
    }
    fclose(fptr);

    //Delete the Task from the list.
    if(index>TaskItems[0].numberTasks)
    {
        printf("Error: item with index %d does not exist. Nothing deleted.\n",index);return;
    }

    for(i=index-1;i<TaskItems[0].numberTasks;i++)
    {
        strcpy(TaskItems[i].label,TaskItems[i+1].label);
        TaskItems[i].priority=TaskItems[i+1].priority;
        TaskItems[i].status=TaskItems[i+1].status;
    }
    strcpy(TaskItems[i-1].label,"");
    TaskItems[i-1].priority=-1;
    TaskItems[i-1].status=0;

    TaskItems[0].numberTasks--; //decrement because its delete

    printf("Deleted item with index %d\n",index);


    //Writing it to the file.
    fptr=fopen("..\\task.txt","w");

    if (fptr == NULL)
    {
        perror("error");printf("failed to open file.\n");exit(1);
    }

    for (int i = 0; i < TaskItems[0].numberTasks; i++)
    {
        if(TaskItems[i].status==0)
        {
            sprintf(line,"%d %s\n",TaskItems[i].priority,TaskItems[i].label);
            if((linesWritten=fputs(line,fptr))<0)
            {
                printf("Cannot add task to the File.\n");return;
            }
        }
    }
    fclose(fptr);

}



void markItem(struct Tasks TaskItems[],int index)
{
    FILE *fptr;
    char line[MAX];
    int i,k,j;
    int linesWritten;
    char label1[MAX];

    i=0,k=0;

    fptr=fopen("..\\task.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].priority=atoi(&line[j]);
        TaskItems[i].status=0;

        for(j=2;line[j]!='\0' && line[j]!='\n';j++)           
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;
    }
    fclose(fptr);

    if(index>TaskItems[0].numberTasks)
    {
        printf("Error: no incomplete item with index %d exists.\n",index);return;
    }

    if(TaskItems[index-1].status==1)
    {
        printf("Error: no incomplete item with index %d exists.\n",index);return;
    }

    TaskItems[index-1].status=1;
    strcpy(label1,TaskItems[index-1].label);
    printf("Marked item as done.\n");

    //write the pending tasks back to task file
    fptr=fopen("..\\task.txt","w");

    if (fptr == NULL)
    {
        perror("error");printf("failed to open file.\n");exit(1);
    }

    for (int i = 0; i < TaskItems[0].numberTasks; i++)
    {
        if(TaskItems[i].status==0)
        {
            sprintf(line,"%d %s\n",TaskItems[i].priority,TaskItems[i].label);
            if((linesWritten=fputs(line,fptr))<0)
            {
                printf("Cannot add task to the File.\n");return;
            }
        }
    }
    fclose(fptr);

    //write the completed tasks to the completed file
    fptr=fopen("..\\completed.txt","a+");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    sprintf(line,"%s\n",label1);
    if((linesWritten=fputs(line,fptr))<0)
    {
        return;
    }
    fclose(fptr);

}

void printReport(struct Tasks TaskItems[])
{
    FILE *fptr;
    char line[MAX];
    int i,k,j;
    i=0,k=0;

    fptr=fopen("..\\task.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].priority=atoi(&line[j]);
        TaskItems[i].status=0;

        for(j=2;line[j]!='\0' && line[j]!='\n';j++)           
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;
    }
    fclose(fptr);

    printf("Pending : %d\n",TaskItems[0].numberTasks);
    for(i=0;i<TaskItems[0].numberTasks;i++)
    {
        printf("%d. %s [%d]\n",i+1,TaskItems[i].label,TaskItems[i].priority);
    }
    printf("\n");

    //Now read lines from the completed.txt file

    for(i=0;i<TaskItems[0].numberTasks;i++)     //reset the array of structures.
    {
        strcpy(TaskItems[i].label,"");
        TaskItems[i].priority=-1;
    }
    TaskItems[0].numberTasks=0;strcpy(line,"");

    i=0,k=0;

    fptr=fopen("..\\completed.txt","r");
    if (fptr == NULL)
    {
        perror("error");exit(1);
    }
    
    while(fgets(line,MAX,fptr)!=NULL)
    {
        k=0,j=0;
        TaskItems[i].status=1;
        for(j=0;line[j]!='\0' && line[j]!='\n';j++)           
        {
            strcpy(&TaskItems[i].label[k],&line[j]);k++;
        }
        strcpy(&TaskItems[i].label[k],"\0");    //to remove the blank space
        TaskItems[0].numberTasks=i+1;
        i++;strcpy(line,"");
    }
    fclose(fptr);

    printf("Completed : %d\n",TaskItems[0].numberTasks);
    for(i=0;i<TaskItems[0].numberTasks;i++)
    {
        printf("%d. %s\n",i+1,TaskItems[i].label);
    }

}


