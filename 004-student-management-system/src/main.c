#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

static void menu_show(void)
{
	printf("\nThere are some options, Please select a option.(You must input a number!)\n");
	printf("***************************************************************************\n");
	printf("1 : Show all student\n");
	printf("2 : Add a student\n");
	printf("3 : Delete a student by stu_id\n");
	printf("4 : Search a student by stu_id\n");
	printf("5 : Save all student\n");
	printf("6 : Update a student by stu_id\n");
	printf("7 : Quit student mangement system\n");
	printf("***************************************************************************\n");
}

static int function_select(int option, List *p_list)
{
	int stu_id = 0;
	int result = 0;
	char filename[300] = {0};
	char stu_name[10] = {0};

	switch (option)
	{
		case SHOW_STU:
			student_information_show(p_list);
			break;
		case ADD_STU:
			student_information_add(p_list);
			break;
		case DEL_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			student_information_del(p_list, stu_id);
			break;
		case SEAR_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			student_information_search_by_stu_id(p_list, stu_id);
			break;
		case SAVE_STU:
			printf("Please input file name that you want to save:");
			scanf("%s", filename);
			student_information_save(p_list, filename);
			break;
		case UPDATE_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			printf("Please input a student's name that you want to update:");
			scanf("%s", stu_name);
			stu_name[9] = '\0';
			student_information_update(p_list, stu_id, stu_name);
			break;
		case QUIT_STU:
			student_mamgement_system_quit(p_list);
			result = 1;
			break;
		default:
			break;
	}
	return result;
}

int main(int argc, const char *argv[])
{
	List list;
	list.head = NULL;

	printf("Welcome to Student Mangement System(Version 1.0).\n\n");
Loop:
	menu_show();
	
	int option = 0;
	printf("Pick a Num:");
	scanf("%d", &option);
	while (option != SHOW_STU && option != ADD_STU  && option != DEL_STU  && 
		   option != SEAR_STU && option != QUIT_STU && option != SAVE_STU && 
		   option != UPDATE_STU)
	{
		printf("Error: Please valid number.\n");
		printf("Pick a Num:");
		scanf("%d", &option);
	}
	if (function_select(option, &list) > 0)
	{
		printf("Free link List memory and Quit program.\n");
	}
	else
	{
		goto Loop;
	}
	
	return 0;
}