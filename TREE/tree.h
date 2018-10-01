#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

const int MAX_CHARS = 40;

struct tree_elem_t
{
    tree_elem_t* parent;
    char data [MAX_CHARS];
    tree_elem_t* left;
    tree_elem_t* right;
    int number;
};

struct tree_t
{
    tree_elem_t* root;
    int nElements;
};

int constructTree  (tree_t* rTree, char firstElemData [MAX_CHARS]);

//working with a tree
int addElemLeft    (tree_t* rTree, tree_elem_t* parentElement, char addedElemData [MAX_CHARS]);
int addElemRight   (tree_t* rTree, tree_elem_t* parentElement, char addedElemData [MAX_CHARS]);
int changeElemData (tree_t* rTree, tree_elem_t* element, char data [MAX_CHARS]);

//functions for dump
int dumpWithDot    (tree_t* rTree);
int fPrintfElem    (tree_elem_t* element, FILE* ptrFile);
int fPrintfArrow   (tree_elem_t* element, FILE* ptrFile);

#endif
