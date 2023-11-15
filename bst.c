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

bool search_it(struct node * root, int val)
{
    while (root)
    {
        if (val == root->val)
            return true;

        if (val < root->val)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}


bool search(struct node * root, int val)
{
    if (!root)
        return false;

    if (val == root->val)
        return true;

    if (val < root->val)
        return search(root->left, val);
    else
        return search(root->right, val);
}

bool all_less(struct node * root, int val)
{
    if (!root)
        return true;
    return root->val < val &&
        all_less(root->left, val) &&
        all_less(root->right, val);
}
bool all_greater(struct node * root, int val)
{
    if (!root)
        return true;
    return root->val > val &&
        all_greater(root->left, val) &&
        all_greater(root->right, val);
}

bool is_bst(struct node * root)
{
    if (!root)
        return true;
    return all_less(root->left, root->val) &&
        all_greater(root->right, root->val) &&
        is_bst(root->left) &&
        is_bst(root->right);
}

struct node * insert(struct node * root, int val)
{
    assert(is_bst(root));

    if (!root)
        return alloc_node(val);

    if (val < root->val)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = insert(root->right, val);
    }
    // no case for == to ignore duplicates

    assert(is_bst(root));

    return root;
}

struct node * delete(struct node * root, int val)
{
    assert(is_bst(root));

    if (!root)
        return root;

    if (val < root->val)
    {
        root->left = delete(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = delete(root->right, val);
    }
    else // we found the node to delete
    {
        // 0 or 1 child
        if (!root->left)
        {
            struct node * temp = root->right;
            free(root);

            assert(is_bst(temp));
            return temp;
        }
        else if (!root->right)
        {
            struct node * temp = root->left;
            free(root);

            assert(is_bst(temp));
            return temp;
        }
        else
        {
            // 2 children
            struct node * successor = root->right;
            while (successor->left)
            {
                successor = successor->left;
            }

            // "swap" root and successor, and recursively delete successor
            root->val = successor->val;
            root->right = delete(root->right, successor->val);
        }
    }

    assert(is_bst(root));
    return root;
}

struct node * example1()
{
    struct node * root = alloc_node(4);

    root->left = alloc_node(-5);
    root->left->right = alloc_node(-1);
    root->left->right->right = alloc_node(3);

    root->right = alloc_node(7);
    root->right->left = alloc_node(5);
    root->right->right = alloc_node(9);

    return root;
}

struct node * example2()
{
    struct node * root = insert(NULL, 4);
    root = insert(root, -5);
    root = insert(root, -1);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 5);
    root = insert(root, 9);

    return root;
}

int main()
{
    struct node * n = example1();

    pre_order(n);
    printf("\n");
    in_order(n);
    printf("\n");
    post_order(n);
    printf("\n");

    printf("%d\n", search_it(n, 4));

    n = delete(n, 4);

    pre_order(n);
    printf("\n");
    in_order(n);
    printf("\n");
    post_order(n);
    printf("\n");

    printf("%d\n", search_it(n, 4));

    free_node(n);
}
