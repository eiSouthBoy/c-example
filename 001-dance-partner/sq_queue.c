//==============================================================================
//
// Title:
// Purpose:
// Author:
// Created on:
// Copyright:
//
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sq_queue.h"

// 队列初始化
extern int queue_init(sq_queue_t *sq_queue_pt)
{
	sq_queue_pt->base = (QElemType *)malloc(MAX_Q_SIZE * sizeof(QElemType));
	if (NULL == sq_queue_pt->base)
		return Q_MALLOC_ERROR;
	memset(sq_queue_pt->base, 0, MAX_Q_SIZE * sizeof(QElemType));
	sq_queue_pt->front = 0;
	sq_queue_pt->rear = 0;
	return OK;
}

// 队列销毁
extern int queue_destory(sq_queue_t *sq_queue_pt)
{
	if (NULL != sq_queue_pt->base)
		free(sq_queue_pt->base);
	sq_queue_pt->front = 0;
	sq_queue_pt->rear = 0;
	return OK;
}

// 求队列长度
extern int queue_length(sq_queue_t *sq_queue_pt)
{
	return  (sq_queue_pt->rear - sq_queue_pt->front + MAX_Q_SIZE) % MAX_Q_SIZE;
}

// 入队
extern int queue_push(sq_queue_t *sq_queue_pt, QElemType elem)
{
	// 判断是否队满(循环队列)，若队列为满，则报错
	if ((sq_queue_pt->rear + 1) % MAX_Q_SIZE == sq_queue_pt->front)
		return Q_OVERFLOW;
	sq_queue_pt->base[sq_queue_pt->rear] = elem;
	sq_queue_pt->rear = (sq_queue_pt->rear + 1) % MAX_Q_SIZE;
	return OK;
}

// 出队
extern int queue_pop(sq_queue_t *sq_queue_pt, QElemType *elem)
{
	// 判断是否对空，若队列为空，则报错
	if (sq_queue_pt->front == sq_queue_pt->rear)
		return Q_EMPTY;
	*elem = sq_queue_pt->base[sq_queue_pt->front];
	sq_queue_pt->front = (sq_queue_pt->front + 1) % MAX_Q_SIZE;
	return OK;
}

// 取队头元素
extern QElemType * queue_head_elem_get(sq_queue_t *sq_queue_pt)
{
	//若队列为空，则返回空指针NULL
	QElemType *p_elem = NULL;
	if (sq_queue_pt->front == sq_queue_pt->rear)
		p_elem = NULL;
	else
		p_elem = &sq_queue_pt->base[sq_queue_pt->front];
	return p_elem;
}

// 判断队列是否为空
extern int  queue_empty(sq_queue_t *sq_queue_pt)
{
	// 若队列为空，则返回值为非0值
	return !((sq_queue_pt->rear - sq_queue_pt->front + MAX_Q_SIZE) % MAX_Q_SIZE);
}
