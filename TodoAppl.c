#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include"TodoImpl.h"

int main(int argc, char* argv[])
{
    struct Tasks TaskItems[100];    //initialise the structure.

    for (int i = 0; i < 100; i++)
    {
        TaskItems[i].numberTasks=0;     //set all number of tasks to 0
        TaskItems[i].priority=-1;
        TaskItems[i].status=0;
    }

    if(argc==1 || strcmp(argv[1],"help")==0)
    {
        printCLIUsage();
    }
    else if(strcmp(argv[1],"ls")==0)
    {
        listItems(TaskItems);
    }
    else if(strcmp(argv[1],"add")==0)
    {
        addItem(TaskItems,argv[3],atoi(argv[2]));
    }
    else if(strcmp(argv[1],"del")==0)
    {
        deleteItem(TaskItems,atoi(argv[2]));
    }
    else if(strcmp(argv[1],"done")==0)
    {
        markItem(TaskItems,atoi(argv[2]));
    }
    else if(strcmp(argv[1],"report")==0)
    {
        printReport(TaskItems);
    }
    else
    {
        printCLIUsage();
    }

    return 0;
}

