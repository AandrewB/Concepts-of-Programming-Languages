#include "bst.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static node* create_node(shape sh){
    node* n = malloc(sizeof(node));
    assert(n != NULL && "malloc failed in create_node");

    n->sh =sh;
    n->left = NULL;
    n->right = NULL;

    return n;
}

static node* insert_node(node* root, shape sh){
    if (root == NULL){
        return create_node(sh);
    }

    int cmp = cmp_shapes(sh, root->sh);

    if (cmp < 0){
        root->left = insert_node(root->left, sh);

    } 
    else {
        root->right = insert_node(root->right, sh);
    }

    return root;
    

}
bst create_bst(){
    bst t;
    t.root = NULL;
    return t;
}

void insert_in_bst(bst* t, shape sh){
    assert(t !=NULL);
    t->root = insert_node(t->root, sh);
}

static void inorder_node(node* root){
    if (root == NULL) return;
    
    inorder_node(root->left);

    char* s = to_string(root->sh);
    printf("%s\n", s);
    free(s);

    inorder_node(root->right);
    
}

void inorder(bst t){
    inorder_node(t.root);
}

static void free_node(node* root){
    if (root == NULL) return;

    free_node(root->left);
    free_node(root->right);

    free_shape(root->sh);
    free(root);
    
}

void free_bst(bst t){
    free_node(t.root);
}
