#include <stdio.h>
#include <stdlib.h>
#include "sq_btree.h"


/* 创建结点 */
static Node* bstree_node_create(int key, Node *parent, Node *left, Node *right)
{
	Node *p = (Node *)malloc(1*sizeof(Node));
	if (NULL == p)
	{
		return NULL;
	}
	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;
	return p;
}

/* 销毁二叉树 */
void bstree_destroy(BSTree tree)
{
	if (NULL != tree)
	{
		if (tree->left != NULL)
		{
			bstree_destroy(tree->left);
		}
		if (tree->right != NULL)
		{
			bstree_destroy(tree->right);
		}
		free(tree);
	}
}

/* 插入结点 */
static Node* bstree_node_insert(BSTree tree, Node *node)
{
	Node *p = NULL;
	Node *q = tree;

	// find the last node(as the new node's parent)
	while (q != NULL)
	{
		p = q;
		if (node->key < q->key)
		{
			q = q->left;
		}
		else
		{
			q = q->right;
		}
	}
	node->parent = p;
	if (NULL == p)
	{
		tree = node;
	}
	else if (node->key < p->key)
	{
		p->left = node;
	}
	else
	{
		p->right = node;
	}
	return tree;
}

/* 通过指定key值插入结点 */
Node* bstree_insert_with_key(BSTree tree, int key)
{
	Node *p = bstree_node_create(key, NULL, NULL, NULL);
	if (NULL == p)
	{
		return tree;
	}
	Node *q = bstree_node_insert(tree, p);
	return q;
}

/* 查找key值最大的结点 */
Node* bstree_node_maximum_find(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

/* 查找key值最小的结点 */
Node* bstree_node_minimum_find(BSTree tree)
{
	if (NULL == tree)
	{
		return NULL;
	}
	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	return tree;
}

/* 递归查找法 通过指定key值搜索结点 */
Node* bstree_node_search_with_key(BSTree tree, int key)
{
	if (NULL == tree || tree->key == key)
	{
		return tree;
	}
	if (key < tree->key)
	{
		return bstree_node_search_with_key(tree->left, key);
	}
	else
	{
		return bstree_node_search_with_key(tree->right, key);
	}
}

/* 查找结点node的后继结点，即查找"二叉树中数据值大于该结点的最小结点" */
Node* bstree_successor(Node *node)
{
	// 若该结点存在右孩子，则查找以右孩子为根结点二叉树的最小结点
	if (node->right != NULL)
	{
		return bstree_node_minimum_find(node->right);
	}
	// 若该结点没有右孩子。则该结点有两种可能：
	// 01) 该结点是一个左孩子，则该结点的后继结点就是它的父结点
	// 02) 该结点是一个右孩子，则查找该结点的最低父结点，且该父结点拥有左孩子，满足条件的最低父结点就是结点node的后继结点
	Node *p = node->parent;
	while (p != NULL && node == p->right)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

/* 查找结点node的前驱结点，即查找"二叉树中数据值小于该结点的最大结点" */
Node* bstree_predecessor(Node *node)
{
	// 若该结点存在左孩子，则查找以左孩子为根结点二叉树的最大结点
	if (node->left != NULL)
	{
		return bstree_node_maximum_find(node->left);
	}
	// 若该结点没有左孩子。则该结点有两种可能：
	// 01) 该结点是一个左孩子，则查找该结点的最低父结点，且该父结点拥有右孩子，满足条件的最低父结点就是结点的前驱结点
	// 02) 该结点是一个右孩子，则该结点的前驱结点就是它的父结点
	Node *p = node->parent;
	while (p != NULL && node == p->left)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

/* 删除结点 */
static Node* bstree_node_delete(BSTree tree, Node *node)
{
	Node *p = NULL, *q = NULL;
	// 判断结点node是否存在左孩子或右孩子，若该结点没有左右孩子，则查找该结点的后继结点
	if (node->left == NULL || node->right == NULL)
	{
		q = node;
	}
	else
	{
		q = bstree_successor(node);
	}
	if (q->left != NULL)
	{
		p = q->left;
	}
	else
	{
		p = q->right;
	}

	if (p != NULL)
	{
		p->parent = q->parent;
	}

	if (q->parent == NULL)
	{
		tree = p;
	}
	else if (q == q->parent->left)
	{
		q->parent->left = p;
	}
	else
	{
		q->parent->right = p;
	}

	if (q != node)
	{
		node->key = q->key;
	}
	if (q != NULL)
	{
		free(q);
	}
	return tree;
}

/* 通过指定key值的结点 */
Node* bstree_delete_with_key(BSTree tree, int key)
{
	Node *p = bstree_node_search_with_key(tree, key);
	if (p != NULL)
	{
		tree = bstree_node_delete(tree, p);
	}
	return tree;
}

/* 前序遍历 */
void bstree_preorder(BSTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->key);
		bstree_preorder(tree->left);
		bstree_preorder(tree->right);
	}
}


/* 中序遍历 */
void bstree_midorder(BSTree tree)
{
	if (tree != NULL)
	{ 
		bstree_midorder(tree->left);
		printf("%d ", tree->key);
		bstree_midorder(tree->right);
	}
}


/* 后序遍历 */
void bstree_postorder(BSTree tree)
{
	if (tree != NULL)
	{
		bstree_postorder(tree->left);
		bstree_postorder(tree->right);
		printf("%d ", tree->key);
	}
}