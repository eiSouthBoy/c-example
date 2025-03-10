#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// stu_id 作为主键，不允许重复
static int stu_id_constraint_primary_key(const List *p_list, const Node *node)
{
	int result = 0;
	Node *p = p_list->head;
	while (p != NULL)
	{
		if (p->stu_id == node->stu_id)
		{
			result = -1;
			break;
		}
		p = p->next;
	}

	return result;
}

static int student_information_check(const List *p_list, const Node *node, Error *err)
{
	int repetition = stu_id_constraint_primary_key(p_list, node);
	if (0 != repetition)
	{
		err->id = PK_ERROR;
		sprintf(err->msg, "%%student id: %d repeat", node->stu_id);
		return -1;
	}
	else if (9999 < node->stu_id || node->stu_id < 1000)
	{
		err->id = ID_ERROR;
		sprintf(err->msg, "%%student id: %d invalid(valid range: 1000~9999)", node->stu_id);
		return -2;
	}
	else if (0 != strcmp("M", node->stu_sex) && 0 != strcmp("F", node->stu_sex))
	{
		err->id = SEX_ERROR;
		sprintf(err->msg, "%%student sex: \'%s\' invalid(valid sex: \'M\' 或 \'F\')", node->stu_sex);
		return -3;
	}
	else if (50 < node->stu_age || node->stu_age <= 0)
	{
		err->id = AGE_ERROR;
		sprintf(err->msg, "%%student age: %d invalid(valid range: 1~50)", node->stu_age);
		return -4;
	}
	else
	{
		err->id = NO_ERROR;
	}
	return 0;
}

void student_information_show(List *p_list)
{
	if (NULL == p_list->head)
	{
		printf("--> There is not any student. Maybe you can add a student.\n");
	}
	else
	{
        printf("----------------------------------------\n");
		printf("id        name      sex       age       \n");
        printf("----------------------------------------\n");
		int stu_num = 0;
		Node *last = NULL;
		for(last = p_list->head; last; last = last->next)
		{
            printf("%-10d%-*s%-10s%-10d\n", last->stu_id, 
                MAX_STU_NAME_SIZE, last->stu_name, last->stu_sex, last->stu_age);
			stu_num++;
		}
		printf("--> Total Student:%d\n", stu_num);
	}
}

void student_information_add(List *p_list)
{
	printf("Now you can add a student information.\n");
	printf("Tips: there are some attributes that like stu_id, "
           "stu_name, stu_sex and stu_age with student.\n"
		   "Of course, the attribute has some limitation.\n");
	printf("stu_id range 1000 to 9999.\n");
	printf("stu_name character max (4 Chinese or 9 English).\n");
	printf("stu_sex range M or F.\n");
	printf("stu_age range 1 to 50.\n\n");
	Node *p = malloc(sizeof(Node));
	Error err;
	memset(&err, 0, sizeof(err));
	p->next = NULL;

	printf("student id:");
	scanf("%d", &(p->stu_id));
	printf("student name:");
	scanf("%s", p->stu_name);
	printf("student sex:");
	scanf("%s", p->stu_sex);
	printf("student age:");
	scanf("%d", &(p->stu_age));

	p->stu_name[MAX_STU_NAME_SIZE - 1] = '\0';
	p->stu_sex[MAX_STU_SEX_SIZE - 1] = '\0';
	while(student_information_check(p_list, p, &err) < 0)
	{ 
		if (NO_ERROR != err.id)
		{
			printf("%s\n", err.msg);
			if (PK_ERROR == err.id)
			{
				printf("student id:");
				scanf("%d", &(p->stu_id));
				continue;
			}
			else if (ID_ERROR == err.id)
			{
				printf("student id:");
				scanf("%d", &(p->stu_id));
				continue;
			}
			else if (SEX_ERROR == err.id)
			{
				printf("student sex:");
				scanf("%s", p->stu_sex);
				continue;
			}
			else if (AGE_ERROR == err.id)
			{
				printf("student age:");
				scanf("%d", &(p->stu_age));
				continue;
			}
		}
	}
	printf("--> Adding a student successful.\n");

	Node *last = p_list->head;
	if (last != NULL)  // 判断第一个结点是否存在
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = p;
	}
	else
	{
		p_list->head = p;
	}
}

void student_information_del(List *p_list, int stu_id)
{
	Node *p, *q;
	int is_found = 0;
	for (q = NULL, p = p_list->head; p != NULL; q = p, p = p->next)
	{
		if (stu_id == p->stu_id)
		{
			if (q != NULL) // 判断是否为头节点
			{
				q->next = p->next;
			}
			else
			{
				p_list->head = p->next;
			}
			free(p);
			is_found = 1;
			break;
		}
	}
	if (is_found)
	{
		printf("--> Delete successful.\n");
	}
	else
	{
		printf("--> Delete failure.\n");
	}
}

int student_information_search_by_stu_id(List *p_list, int stu_id)
{
	int is_found = 0;
	Node *last;
	char stu_info[100] = {0};
	for (last = p_list->head; last != NULL; last = last->next)
	{
		if (stu_id == last->stu_id)
		{
			sprintf(stu_info, "stu_id: %d, stu_name: %s, stu_sex: %s, stu_age: %d", 
				last->stu_id, last->stu_name, last->stu_sex, last->stu_age);
			is_found = 1;
			break;
		}
	}
	if (is_found)
	{
		printf("--> Found a student || %s.\n", stu_info);
	}
	else
	{
		printf("--> Not Found.\n");
	}
	return 0;
}

void student_information_save(const List *p_list, const char *filename)
{
	Node *last;
	char stu_info[100] = { 0 };
	FILE *file_handle = fopen(filename, "a");
	if(NULL != file_handle)
	{ 
		for (last = p_list->head; last != NULL; last = last->next)
		{
			sprintf(stu_info, "{\"stu_id\":%d,\"stu_name\":\"%s\",\"stu_sex\":\"%s\",\"stu_age\":%d}\n",
				last->stu_id, last->stu_name, last->stu_sex, last->stu_age);
			fwrite(stu_info, sizeof(char), strlen(stu_info), file_handle);
		}
		fclose(file_handle);
	}
	printf("--> Save all student Successful.\n");
}

int student_information_update(List *p_list, int stu_id, const char *stu_name)
{
	int result = 0;
	Node *p = p_list->head;
	while (p != NULL)
	{
		if (p->stu_id == stu_id)
		{
			strcpy(p->stu_name, stu_name);
			result = 1;
			break;
		}
		p = p->next;
	}
	if (1 == result)
	{
		printf("--> Update successful.\n");
	}
	else
	{
		printf("--> Update failure: %d not exist.\n", stu_id);
	}

	return 0;
}

void student_mamgement_system_quit(List *p_list)
{
	Node *temp = NULL;
	while (p_list->head != NULL)
	{
		temp = p_list->head;   //从第一个结点开始释放
		p_list->head = temp->next;
		free(temp);
	}
}