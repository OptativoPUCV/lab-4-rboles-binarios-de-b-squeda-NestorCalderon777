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
        current = father;

        if(is_equal(key, current->pair->key)) return;

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

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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
    return NULL;
}
