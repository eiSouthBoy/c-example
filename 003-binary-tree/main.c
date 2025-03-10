#include <stdio.h>
#include <stdlib.h>
#include "sq_btree.h"


int main(int argc, const char *argv[])
{
	BSTree root = NULL;
	//int number_list[] = {1, 5, 4, 3, 2, 6};
	int number_list[] = { 2, 1, 4, 3, 5};
	int list_num = sizeof(number_list) / sizeof(number_list[0]);
	
	printf("Insert number:");
	for (int i = 0; i < list_num; i++)
	{
		printf("%d ", number_list[i]);
		root = bstree_insert_with_key(root, number_list[i]);
	}
	printf("\n\n");

	// 前序遍历
	printf("Preorder BSTree:");
	bstree_preorder(root);
	printf("\n");
	// 中序遍历
	printf("Midorder BSTree:");
	bstree_midorder(root);
	printf("\n");
	// 后序遍历
	printf("Posorder BSTree:");
	bstree_postorder(root);
	printf("\n\n");
	
	// 查找key值最小的结点
	Node *p = bstree_node_minimum_find(root);
	if (NULL != p)
	{
		printf("the key minimum: %d\n", p->key);
	}
	else
	{
		printf("the key minimum not exist.\n");
	}
	
	// 查找key值最大的结点
	p = bstree_node_maximum_find(root);
	if (NULL != p)
	{
		printf("the key maximum: %d\n", p->key);
	}
	else
	{
		printf("the key maximum not exist.\n\n");
	}

	// 查找指定key值的结点
	int key = 3;
	p = bstree_node_search_with_key(root, key);
	if (NULL != p)
	{
		printf("the key:%d node exist.\n", key);
	}
	else
	{
		printf("the key:%d node not exist.\n", key);
	}
	// 查找指定key值的结点的前驱结点
	if (NULL != p)
	{
		Node *r = bstree_predecessor(p);
		printf("结点(key=%d)的前驱结点:key=", p->key);
		if (r != NULL)
		{
			printf("%d", r->key);
		}
		else
		{
			printf("not exist.");
		}
		printf("\n");
	}

	// 查找指定key值的结点的后继结点
	if (NULL != p)
	{
		Node *r = bstree_successor(p);
		printf("结点(key=%d)的后继结点:key=", p->key);
		if (r != NULL)
		{
			printf("%d", r->key);
		}
		else
		{
			printf("not exist.");
		}
		printf("\n\n");
	}


	// 删除指定key值的结点
	key = 5;
	p = bstree_delete_with_key(root, key);
	printf("删除key=%d的结点\n\n", key);

	// 前序遍历
	printf("Preorder BSTree:");
	bstree_preorder(root);
	printf("\n");
	// 中序遍历
	printf("Midorder BSTree:");
	bstree_midorder(root);
	printf("\n");
	// 后序遍历
	printf("Posorder BSTree:");
	bstree_postorder(root);
	printf("\n\n");

	bstree_destroy(root);
	return 0;
}