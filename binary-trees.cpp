#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    node *left, *right;
};

node* crnode(int v) {
    node *nnode = new node;
    nnode->left = nullptr;
    nnode->right = nullptr;
    nnode->val = v;
    return nnode;
}

node* add_tree(node *root, int val) {
    if (root == nullptr) {
        root = crnode(val);
        return root;
    }
    if (val < root->val) {
        if (root->left == nullptr) root->left = crnode(val);
        else add_tree(root->left, val);
    } else {
        if (root->right == nullptr) root->right = crnode(val);
        else add_tree(root->right, val);
    }
    return root;
}

node* find_tree(node *root, int val) {
    if (root == nullptr) return nullptr;
    if (val == root->val) return root;
    if (val < root->val) return find_tree(root->left, val);
    if (val > root->val) return find_tree(root->right, val);
}

int rightmost(node* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->val;
}

node* del_tree(node *root, int val) {
    if (root == nullptr) return nullptr;
    if (root->val == val) {
        if (root->left == nullptr && root->right == nullptr) {
            free(root);
            return nullptr;
        }
        if (root->left == nullptr && root->right != nullptr) {
            node *temp = root->right;
            free(root);
            return temp;
        }
        if (root->left != nullptr && root->right == nullptr) {
            node *temp = root->left;
            free(root);
            return temp;
        }
        root->val = rightmost(root->left);
        root->left = del_tree(root->left, root->val);
        return root;
    }
    if (val < root->val) {
        root->left = del_tree(root->left, val);
    } else {
        root->right = del_tree(root->right, val);
    }
    return root;
}

void print_tree(node *root) {
    if (root != nullptr) {
        print_tree(root->left);
        printf("%d ", root->val);
        print_tree(root->right);
    }
}

int main() {
    node* tree = nullptr;
    tree = add_tree(tree, 5);
    tree = add_tree(tree, 1);
    tree = add_tree(tree, 3);
    tree = add_tree(tree, 7);
    tree = add_tree(tree, 6);
    print_tree(tree);
    return 0;
}
