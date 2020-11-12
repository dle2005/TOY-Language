#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode {
    char data;
    bool MINUS;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
} treeNode;

treeNode* makeTree(char data, treeNode* parentNode) {
    treeNode* root = (treeNode*)malloc(sizeof(treeNode));
    root -> data = data;
    root -> MINUS = false;
    root -> left = NULL;
    root -> right = NULL;
    root -> parent = parentNode;
    return root;
}

char GetData(treeNode* root) {
    return root -> data;
}

treeNode* GetLeft(treeNode* root) {
    return root -> left;
}

treeNode* GetRight(treeNode* root) {
    return root -> right;
}

treeNode* GetParent(treeNode* root) {
    return root -> parent;
}

void LeftSubTree(treeNode* root, char data, bool MINUS) {
    treeNode* child = (treeNode*)malloc(sizeof(treeNode));
    root -> left = child;
    child -> data = data;
    child -> MINUS = MINUS;
    child -> left = NULL;
    child -> right = NULL;
    child -> parent = root;
}

void RightSubTree(treeNode* root, char data, bool MINUS) {
    treeNode* child = (treeNode*)malloc(sizeof(treeNode));
    root -> right = child;
    child -> data = data;
    child -> MINUS = MINUS;
    child -> left = NULL;
    child -> right = NULL;
    child -> parent = root;
}

bool isChildEmpty(treeNode* root) {
    if (root -> left == NULL && root -> right == NULL)
        return true;
    else return false;
}

bool isChildPull(treeNode* root) {
    if (root -> left != NULL && root -> right != NULL)
        return true;
    else return false;
}

bool isLeftEmpty(treeNode* root) {
    if (root -> left == NULL) return true;
    else return false;
}

bool isRightEmpty(treeNode* root) {
    if (root -> right == NULL) return true;
    else return false;
}

bool isOperator(char data) {
    if (data == 'M' || data == 'I') return true;
    else return false;
}

bool isMINUS(char data) {
    if (data == '-') return true;
    else return false;
}

bool isBothNumber(treeNode* root) {
    if(root -> left != NULL && root -> right != NULL) {
        if (root -> left -> data != 'M' && root -> left -> data != 'I' && 
                root -> right -> data != 'M' && root -> right -> data != 'I') return true;
    }
    else return false;
}

bool isLeftNumber(treeNode* root) {
    if(root -> left != NULL && root -> right != NULL) {
        if (root -> left -> data != 'M' && root -> left -> data != 'I') return true;
    }
    else return false;
}

bool isRightNumber(treeNode* root) {
    if(root -> left != NULL && root -> right != NULL) {
        if (root -> right -> data != 'M' && root -> right -> data != 'I') return true;
    }
    else return false;
}

void childFree(treeNode* root) {
    root -> left = NULL;
    root -> right = NULL;
}

void doOperate(treeNode* root) {
    int result;
    if(root -> data == 'M') {
        if(root -> left -> MINUS) {
            root -> MINUS = true;
            result = root -> left -> data - '0';
            result += root -> right -> data - '0';
            root -> data = result + '0';
            childFree(root);
        }
        else {
            int left = root -> left -> data - '0';
            int right = root -> right -> data - '0';
            if (right > left) {
                root -> MINUS = true;
                result = right - left;
                root -> data = result + '0';
                childFree(root);
            }
            else {
                result = left - right;
                root -> data = result + '0';
                root -> left = NULL;
                root -> right = NULL;
            }
        }
    }
    else if (root -> data == 'I') {
        int t1 = root -> left -> data - '0';
        if(t1 <= 0) {
            root -> data = '0';
            childFree(root);
        }
        else {
            root -> data = root -> right -> data;
            childFree(root);
        }
    }
}
