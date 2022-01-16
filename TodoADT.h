struct Tasks
{
    char label[50];
    int priority;
    int numberTasks;
    int status;         //0 if not completed ,1 if completed
};

void printCLIUsage();
int listItems(struct Tasks TaskItems[]);
void addItem(struct Tasks TaskItems[],char * label1,int priority1);
void deleteItem(struct Tasks TaskItems[],int index);
void markItem(struct Tasks TaskItems[],int index);
void printReport(struct Tasks TaskItems[]);

