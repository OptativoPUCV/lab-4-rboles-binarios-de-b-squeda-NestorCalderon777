#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    //reservar memoria del newTreeMap
    TreeMap* newTreeMap = malloc(sizeof(TreeMap));

    //todos los valores de newTreeMap en NULL y lt-->(lower_than) en su valor correspondiente
    if(newTreeMap == NULL) return NULL;
    newTreeMap->root = NULL;
    newTreeMap->current = NULL;
    newTreeMap->lower_than = lower_than;

    return newTreeMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if(tree == NULL) return;

    if(tree->root == NULL){
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
        return;
    }

    TreeNode* current = tree->root;
    TreeNode* father = NULL;

    while(current != NULL){
        father = current;

        if(is_equal(tree, key, current->pair->key)) return;

        if(tree->lower_than(key, current->pair->key)){
            current = current->left;
        } else{
            current = current->right;
        }
    }

    TreeNode* newNodo = createTreeNode(key , value);
    newNodo->parent = father;

    if(tree->lower_than(key, father->pair->key)){
        father->left = newNodo;
    } else{
        father->right = newNodo;
    }

    tree->current = newNodo;

}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if(node == NULL) return;

    //case 1 --> sin hijos
    if(node->left == NULL && node->right == NULL){
        if(node->parent == NULL){
            tree->root = NULL;

        } else if(node->parent->left == node){
            node->parent->left = NULL;
        } else{
            node->parent->right = NULL;
        }
        free(node->pair);
        free(node);
        return;
    }

    //case 2 --> un solo hijo
    if(node->left == NULL || node->right == NULL){
        TreeNode* hijo = (node->left != NULL) ? node->left : node->right;

        if(node->parent == NULL){
            tree->root = hijo; 
        } else if(node->parent->left == node){
            node->parent->left = hijo;
        } else{
            node->parent->right = hijo;
        }
        hijo->parent = node->parent;

        free(node->pair);
        free(node);
        return;
    }

    //case 3 --> 2 hijos
    TreeNode* minNode = minimum(node->right); //sucesor in-order

    //copia de los datos del sucesor al current
    node->pair->key = minNode->pair->key;
    node->pair->value = minNode->pair->value;

    //elimina el nodo minimo del subarbol derecho
    removeNode(tree, minNode);

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* Nodo = tree->root;

    while(Nodo != NULL){
        if(is_equal(tree, key, Nodo->pair->key)){
            tree->current = Nodo;
            return Nodo->pair;
        }
        
        if(tree->lower_than(key, Nodo->pair->key)){
            Nodo = Nodo->left;
        } else {
            Nodo = Nodo->right;
        }
    }

    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
   
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    if(tree == NULL || tree->current == NULL) return NULL;

    TreeNode* current = tree->current;

    //case 1 --> tiene hijo derecho
    if(current->right != NULL){
        TreeNode* next = minimum(current->right);
        return next->pair;
    }

    //case 2 --> encontrar la raiz
    TreeNode* father = current->parent;
    while(father != NULL && current == father->right){
        current = father;
        father = father->parent;
    }
    tree->current = father;

    return father->pair;
}
