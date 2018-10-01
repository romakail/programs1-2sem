#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include "tree.h"

const int MAX_PATH = 20;

int akinator           ();
int akinatorRun        (tree_t*  rTree);
int chooseCharacter    (tree_t* rTree);
int addingNewCharacter (tree_t* rTree,tree_elem_t* branch);
int scanfWithSpace     (char* buffer);

// saving base in the file
int saveBase           (tree_t* rTree);
int printfElem         (tree_elem_t* element, FILE* ptrFile);
int fprintfNtabs       (FILE* ptrFile, int nTabs);

// constucting a base from file
int constructBase      (tree_t* rTree, char* savedFile);
int createTreeElement  (tree_t* rTree, tree_elem_t* element, FILE* ptrFile);
char skipGetChar       (FILE* ptrFile);
int readBetweenQuots   (FILE* ptrFile, char* phrase);

// searching a character
int searchingForCharactert (tree_t* rTree);
tree_elem_t* getElementPtr (tree_elem_t* element, char* lostElement);
int printCharacteristic (tree_elem_t* element, char* name);

#endif
