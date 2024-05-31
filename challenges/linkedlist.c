#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* string;
    struct node* left;
    struct node* right;
} node;

node createRoot(char* string);
void insertInto(node* currentNode, char* string);
void traverseLinked(node* currentNode);
node* findString(node* root, char* string);
int deleteNode(node* root, char* string);

int main() {
    node root = createRoot("Hello world");
    insertInto(&root, "Hello Moon");
    insertInto(&root, "Goodbye World");
    insertInto(&root, "Guu gu gaa gaa");
    traverseLinked(&root);
    node* n = findString(&root, "Goodbye World");
    traverseLinked(n);
    deleteNode(&root, "Hello Moon");
    traverseLinked(&root);
    return 0;
}

node createRoot(char* string) {
    node root;
    root.string = string;
    root.left = NULL;
    root.right = NULL;
    return root;
}

void insertInto(node* root, char* string) {
    node* newNode = (node*)malloc(sizeof(node));
    node* currentNode = root;
    while(currentNode->right) {
        currentNode = currentNode->right;
    }
    newNode->left = currentNode;
    newNode->right = NULL;
    newNode->string = string;
    currentNode->right = newNode;
}

void traverseLinked(node* root) {
    node* currentNode = root;
    while(currentNode->right) {
        printf("%s ", currentNode->string);
        currentNode = currentNode->right;
    }
    printf("%s\n", currentNode->string);
}

node* findString(node* root, char* string) {
    while(root->right) {
        if(strcmp(root->string, string) == 0) {
            return root;
        }
        root = root->right;
    }
    return NULL;
}

int deleteNode(node* root, char* string) {
    while(root->right) {
        if(strcmp(root->string, string) == 0) {
            if(root->left){ 
                root->left->right = root->right;
            }
            if(root->right) {
                root->right->left = root->left;
            }
            free(root);
            return 0;
        }
        root = root->right;
    }
    return 1;
}
