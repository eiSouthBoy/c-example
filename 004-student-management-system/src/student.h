#ifndef __STUDENT_H__
#define __STUDENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_STU_NAME_SIZE 10
#define MAX_STU_SEX_SIZE 10

// #define SHOW_STU   1
// #define ADD_STU    2
// #define DEL_STU    3
// #define SEAR_STU   4
// #define SAVE_STU   5
// #define UPDATE_STU 6
// #define QUIT_STU   7

enum {
    SHOW_STU = 1,
    ADD_STU,
    DEL_STU,
    SEAR_STU,
    SAVE_STU,
    UPDATE_STU,
    QUIT_STU
};

// #define NO_ERROR  0
// #define SEX_ERROR 1
// #define AGE_ERROR 2
// #define ID_ERROR  3
// #define PK_ERROR  4

enum {
    NO_ERROR = 0,
    SEX_ERROR,
    AGE_ERROR,
    ID_ERROR,
    PK_ERROR
};

typedef struct
{
	char msg[100];
	int id;
}Error;

typedef struct Student
{
	char stu_name[MAX_STU_NAME_SIZE];   // 学生姓名
	char stu_sex[MAX_STU_SEX_SIZE];     // 学生性别
	int stu_age;                        // 学生年龄
	int stu_id;                         // 学生学号
	struct Student *next;
}Node;

typedef struct
{
	Node *head;
}List;


void student_information_show(List *p_list);
void student_information_add(List *p_list);
void student_information_del(List *p_list, int stu_id);
int student_information_search_by_stu_id(List *p_list, int stu_id);
void student_information_save(const List *p_list, const char *filename);
int student_information_update(List *p_list, int stu_id, const char *stu_name);
void student_mamgement_system_quit(List *p_list);


#ifdef __cplusplus
}
#endif

#endif