#ifndef AKINATOR_H
#define AKINATOR_H

#include <stddef.h>
#include <stdio.h>

//===================================================================================================================================================================

#define TNodePrintType "%ls"

typedef wchar_t* TNode;

typedef struct SNode
{
    SNode* left   = NULL;
    SNode* right  = NULL;
    TNode  data   = 0;
    SNode* parent = NULL;
} SNode;

enum EBranch
{
    left  = -1,
    right =  1
};

//===================================================================================================================================================================

typedef struct
{
    size_t      ip     = 0;
    EBranch  branch = left;
    size_t      size   = 0;
    wchar_t* Array  = NULL;
} SBuffer;


//===================================================================================================================================================================
void clear_input (void);

void print_modes (void);

void print_head (void);

int test_main_2 (void);

//===================================================================================================================================================================
int selector (SNode* Root);

int select_mode ();

int play_aki_questions (SNode* Root);

int play_find_akinator (SNode* Root);

int ask (SNode* Node);

int ask_and_get (SNode* Node);

bool get_answer (void);

void add_new_object (SNode* Node);

//===================================================================================================================================================================

int check_sym (SBuffer* Buffer);

int read_tree (SNode* Root);

int write_tree (SNode* Root);

void file_wprint (SNode* Node, int n, FILE* OutputFile);

int read_node (SBuffer* Buffer, SNode* Parent);

void seek (SBuffer* Buffer);

void seek_out (SBuffer* Buffer);

void do_tab (int n, FILE* OutputFile);

//===================================================================================================================================================================

SNode* make_node (TNode Data);

SNode* add_left_branch (SNode* Node, SNode* Parent);

SNode* add_right_branch (SNode* Node, SNode* Parent);

void correct_node (SNode* Node, TNode Data);

int tree_deconstructor (SNode* Root);

int delete_tree (SNode* Node);

void print_inorder (SNode* Node);

void wprint_inorder (SNode* Node);

void wprint_preorder (SNode* Node);

void print_node (TNode Data);

void wprint_node (wchar_t* Data);



#endif
