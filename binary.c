#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

struct node
{
    int val;
    struct node * left;
    struct node * right;
};

struct node * alloc_node(int val)
{
    struct node * n = malloc(sizeof(struct node));

    n->val = val;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void free_node(struct node * root)
{
    if (!root)
        return;

    free_node(root->left);
    free_node(root->right);

    free(root);
}

void pre_order(struct node * root)
{
    if (!root)
        return;

    printf("%d ", root->val);
    pre_order(root->left);
    pre_order(root->right);
}

void post_order(struct node * root)
{
    if (!root)
        return;

    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->val);
}

void in_order(struct node * root)
{
    if (!root)
        return;

    in_order(root->left);
    printf("%d ", root->val);
    in_order(root->right);
}

bool search(struct node * root, int val)
{
    if (!root)
        return false;

    return val == root->val ||
        search(root->left, val) ||
        search(root->right, val);
}

int main()
{
    struct node * n = alloc_node(1);
    n->left = alloc_node(2);

    free_node(n);
}
