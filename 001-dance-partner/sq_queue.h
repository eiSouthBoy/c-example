//==============================================================================
//
// Title:		
// Purpose:		
// Author:
// Created on:
// Copyright:
//
//==============================================================================

#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files


//==============================================================================
// Constants
#define MAX_Q_SIZE 100 // 队列空间最大长度
#define MAX_NAME_SIZE 10

#define ERROR -1
#define OK 0
#define OVERFLOW 1

enum 
{
	Q_OK = 0,
	Q_ERROR,
	Q_MALLOC_ERROR,
	Q_OVERFLOW,
	Q_EMPTY,
};
//==============================================================================
// Types
typedef struct person_t
{
	char name[MAX_NAME_SIZE];
	char sex;
}person_t;

typedef person_t QElemType;

typedef struct
{
	QElemType *base;  // 存储空间的基地址
	int front;        // 头指针
	int rear;         // 尾指针
}sq_queue_t;
//==============================================================================
// External variables

//==============================================================================
// Global functions
// d-111
// d-222

int queue_init(sq_queue_t *sq_queue_pt);
int queue_destory(sq_queue_t *sq_queue_pt);
int queue_length(sq_queue_t *sq_queue_pt);
int queue_push(sq_queue_t *sq_queue_pt, QElemType elem);
int queue_pop(sq_queue_t *sq_queue_pt, QElemType *elem);
QElemType * queue_head_elem_get(sq_queue_t *sq_queue_pt);
int  queue_empty(sq_queue_t *sq_queue_pt);

#ifdef __cplusplus
}
#endif

#endif
