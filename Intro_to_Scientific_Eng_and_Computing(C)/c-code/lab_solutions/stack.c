
struct Student {
	int no;
	char name[16];
	char fname[24];
	double grade;
	struct Student *next;
};

void setRandomStudent(struct Student *p);
void push(struct Student **list, struct Student *s);
void pop(struct Student **list);
void display(struct Student *list);



void push(struct Student **list, struct Student *s)
{
	struct Student *new_node;

	new_node = (struct Student *)checkedMalloc(sizeof(struct Student));
	new_node->no = s->no;
	strcpy(new_node->name, s->name);
	strcpy(new_node->fname, s->fname);
	new_node->grade = s->grade;
	new_node->next = *list;

	printf("%d %s %s %.2f is inserted to the top of the stack of plates! \n", new_node->no, new_node->name, new_node->fname, new_node->grade);

	*list = new_node;
}

void pop(struct Student **list)
{
	struct Student *ptr;

	if (*list != NULL) {
		ptr = *list;
		*list = (*list)->next;
		printf("%d %s %s %.2f is removed from the top of the stack of plates! \n", ptr->no, ptr->name, ptr->fname, ptr->grade);
		free(ptr);
	}
}

void display(struct Student *list)
{
	struct Student *temp = list;

	if (temp == NULL)
		printf("Stack is empty...\n");

	while (temp != NULL) {
		printf("%d %s %s %.2f \n", temp->no, temp->name, temp->fname, temp->grade);
		temp = temp->next;
	}
}



// 06.06.2020 Saturday
