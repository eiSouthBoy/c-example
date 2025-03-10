#ifndef __SQ_BTREE_H__
#define __SQ_BTREE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BSTreeNode
{
	int    key;                 // 关键字(键值)
	struct BSTreeNode *left;    // 左孩子
	struct BSTreeNode *right;   // 右孩子
	struct BSTreeNode *parent;  // 父结点
}Node, *BSTree;

Node* bstree_insert_with_key(BSTree tree, int key);
Node* bstree_node_minimum_find(BSTree tree);
Node* bstree_node_maximum_find(BSTree tree);
Node* bstree_delete_with_key(BSTree tree, int key);
Node* bstree_node_search_with_key(BSTree tree, int key);
Node* bstree_predecessor(Node *node);
Node* bstree_successor(Node *node);
void bstree_destroy(BSTree tree);

void bstree_preorder(BSTree tree);
void bstree_midorder(BSTree tree);
void bstree_postorder(BSTree tree);


#ifdef __cplusplus
}
#endif

#endif