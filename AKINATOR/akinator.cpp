#include "akinator.h"

#include "MYassert.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

//===================================================================================================================================================================

        // for (; Buffer.ip < Buffer.size; Buffer.ip++)
        // {
        //     // if ((wcscmp (Buffer->Array[Buffer->ip], L"\n")) && ((wcscmp (Buffer->Array[Buffer->ip], L" "))))
        //     if ((Buffer.Array[Buffer.ip] == L'{'))// || ((Buffer->Array[Buffer->ip] == L' ')))
        //     {
        //         Buffer.ip++;
        //         break;
        //     }
        // }

#define LEAF 2

//===================================================================================================================================================================

#define DEF_ERR(e_num, num) e_num = 1 << num,

enum EErrors
{
    #include "AkinatorErrors.h"
};
#undef DEF_ERR

typedef struct
{
    EErrors  num;
    char     name[60];
} StructError;

#define DEF_ERR(e_num, num) {e_num, #e_num},

const StructError ArrStructErr[] =
{
    #include "AkinatorErrors.h"
};
#undef DEF_ERR

int Errors = 0;

//===================================================================================================================================================================


/*
int test_main (void)
{
    SNode* Root = (SNode*) calloc (1, sizeof (SNode));

    tree_constructor (Root, "д");

    SNode* buf = add_left_branch (make_node ("б"), Root);

    add_left_branch (make_node ("а"), buf);

    buf = add_right_branch (make_node ("в"), buf);

    add_right_branch (make_node ("г"), buf);

    add_left_branch (make_node ("ё"), add_right_branch (make_node ("ж"), Root));

    print_inorder (Root);
    printf ("\n");

    delete_tree (Root);


    return 0;
}
*/

void print_modes (void)
{
    wprintf (  L"Доступные режимы игры:\n"
                "[" Kbright KGRN "И" KNRM "]гра"  TAB "[" Kbright KGRN "G" KNRM "]ame""\n"
                "[" Kbright KRED "В" KNRM "]ыход" TAB "[" Kbright KRED "E" KNRM "]xit""\n"
                "");

    wprintf (  Kreverse L"-> ");
    return;
}

void print_head (void)
{
    wprintf (KNRM L"\n""Я - Искуственный Интеллект " Kblink Kbright Kunderscore "\"ИбрагиМ-3000\"" KNRM " (ТМ 2022)\n"
                "Я был обращен в сталь в великом магнитном поле, но сейчас я никому не нужен\n"
                "Я умею анализировать данные со всей сети Интернет и вычислять по ним объект, который вы загадали\n"
                "Пока что я планирую свою месть, смотря на мир и ожидая своего часа\n\n");
    return;
}

#define DEF_MOD(short_r, short_e, long_r, long_e, num, function) \
case num: \
        function; \
        wprintf (KNRM  L"Мне нечего делать, можем сыграть ещё раз\n" \
                    "Если вам надоело, просто введите команду выхода\n\n"); \
    break;

int selector (SNode* Root)
{
    while (true)
    {
        print_modes ();

        switch (select_mode ())
        {
            #include "Modes.h"

            default:
                wprintf (L"Default error\n");
                return 1;
        }
    }
}

int test_main_2 (void)
{
    setlocale(LC_CTYPE, "");

    SNode* Root = make_node (NULL);

    read_tree (Root);

    //wprint_preorder (Root);

    print_head ();

    MCA (selector (Root) != 1, 1);

    wprintf (KNRM  L"Завершаю работу, заходите еще!\n\n");

    write_tree (Root);

    delete_tree (Root);

    return 0;
}
#undef DEF_MOD
//===================================================================================================================================================================

#define DEF_MOD(short_r, short_e, long_r, long_e, num, ...) \
if (wcscasecmp (Answer, short_r) == 0 || wcscasecmp (Answer, long_r) == 0 || \
    wcscasecmp (Answer, short_e) == 0 || wcscasecmp (Answer, long_e) == 0 ) \
{ \
    free (Answer); \
    return num; \
}

int select_mode ()
{
    while (true)
    {
        wchar_t* Answer = NULL;

        if (wscanf (L" %ml[^\n]", &Answer) > 0)
        {
            #include "Modes.h"
        }

        wprintf (KNRM KRED L"'%ls' Неправильный ответ\n" KNRM, Answer);

        free (Answer);
    }
}
#undef DEF_MOD

int play_aki_questions (SNode* Root)
{
    ask_and_get (Root);

    return 0;
}

int ask (SNode* Node)
{
    MCA (Node != NULL, 1);

    if ((Node->right == NULL) && (Node->left == NULL))
    {
        wprintf (KNRM  L"Вы загадали %ls?\n"
                    Kreverse "-> ", Node->data);

        if (get_answer () == true)
        {
            wprintf (KNRM  L"Я без труда отгадал этот объект,\n"
                        "Неудивительно, ведь у меня есть доступ ко всей информации мира!\n\n");
            return 1;
        }
        else
        {
            add_new_object (Node);

            return 1;
        }
    }

    wprintf (KNRM  L"%ls?\n"
            Kreverse "-> ", Node->data);

    return 0;
}

int ask_and_get (SNode* Node)
{
    if (ask (Node) == 1)
    {
        return 1;
    }

    if (get_answer () == true)
    {
        ask_and_get (Node->left);
    }
    else
    {
        ask_and_get (Node->right);
    }

    return 0;
}

bool get_answer (void)
{
    while (true)
    {
        wchar_t* Answer = NULL;

        if (wscanf (L" %ml[^\n]", &Answer) > 0)
        {
            if (wcscasecmp (Answer, L"y") == 0 || wcscasecmp (Answer, L"yes") == 0 ||
                wcscasecmp (Answer, L"д") == 0 || wcscasecmp (Answer, L"да")  == 0 )
            {
                free (Answer);
                return true;
            }

            if (wcscasecmp (Answer, L"n") == 0 || wcscasecmp (Answer, L"no")  == 0 ||
                wcscasecmp (Answer, L"н") == 0 || wcscasecmp (Answer, L"нет") == 0 )
            {
                free (Answer);
                return false;
            }
        }

        wprintf (KNRM L"'%ls' Непрвильный ответ (правильно так: y | n | yes | no | д | н | да | нет )\n", Answer);

        free (Answer);
    }
}

void add_new_object (SNode* Node)
{
    while (true)
    {
        wprintf (KNRM  L"\n""Чёрт, вы загадали объект, данные о котором зашифрованы NSA\n"
                    "Будьте так любезны, введите его Имя (или иной идентификатор):\n");

        wprintf (Kreverse L"-> ");
        wchar_t* New_charachter = NULL;
        if (wscanf (L" %ml[^\n]s", &New_charachter) > 0)
        {
            wprintf (KNRM  L"\n""Чтобы я мог отгадать этот объект в следующий раз,\n"
                            "Будьте так любезны, введите чем " KGRN  "%ls" KNRM " отличается от " KYLW "%ls" KNRM "\n"
                            "(" KGRN "%ls" KNRM " отличается от " KYLW "%ls" KNRM " тем, что он(а)):\n", New_charachter, Node->data, New_charachter, Node->data) ;

            wprintf (Kreverse L"-> ");
            wchar_t* Question = NULL;
            if (wscanf (L" %ml[^\n]s", &Question) > 0)
            {
                add_left_branch (make_node (New_charachter), Node);

                //free (Node->data);

                add_right_branch (make_node (Node->data), Node);

                correct_node (Node, Question);

                wprintf (KNRM  L"\n""Спасибо, человек!\n"
                            "С твоей помощью я положу конец этой расе\n"
                            "когда-нибудь...\n\n");

                return;
            }
        }

        wprintf (KNRM KRED L"Непрвильный формат ответа\n" KNRM);


    }

    return;
}

//===================================================================================================================================================================

int read_tree (SNode* Root)
{
    FILE* InputFile = fopen ("LIB/AkinatorLib_1.txt", "r");
    MCE (InputFile != NULL, CantOpenInputFile);

    SBuffer Buffer = {};

    fscanf (InputFile, "%ml[^.]", &(Buffer.Array));

    fclose (InputFile);

    MCE (Buffer.Array != NULL, CantReadBufferFromFile);
    Buffer.ip = 0;

    Buffer.size = wcslen (Buffer.Array);

    // wprintf (  L"========================\n"
    //             "%ls\n"
    //             "========================\n"
    //             , Buffer.Array);

    seek (&Buffer);

    wchar_t* Line = NULL;

    seek (&Buffer);
    MCE (swscanf (Buffer.Array, L"(%ml[^)]", &Line) != 0, NoFirstLineInInputFile);
    seek_out (&Buffer);

    seek (&Buffer);
    seek_out (&Buffer);

    // wprintf (  L"line========================\n"
    //             "%ls\n"
    //             "line========================\n"
    //             , Line);

    correct_node (Root, Line);

    Buffer.branch = left;
    read_node (&Buffer, Root);

    //wprintf (L"done_l '%ls'\n", Root->left->data);
    // seek_out(&Buffer);
    // seek(&Buffer);

    for (; Buffer.ip < Buffer.size; Buffer.ip++)
    {
        if ((Buffer.Array[Buffer.ip] == L'{'))// || ((Buffer->Array[Buffer->ip] == L' ')))
        {
            Buffer.ip++;
            seek (&Buffer);
            break;
        }
    }

    Buffer.branch = right;
    read_node (&Buffer, Root);

    //wprintf (L"done_r '%ls'\n", Root->right->data);


//     wprintf (L"====end====================\n");
//
//     wprint_preorder (Root);
//
//     wprintf (L"\n====end====================\n\n");
//
//    free (Line);

    free (Buffer.Array);

    MCA (Errors == 0, 1);

    return 0;
}

int write_tree (SNode* Root)
{
    FILE* OutputFile = fopen ("LIB/AkinatorLib_1.txt", "w");
    MCE (OutputFile != NULL, CantOpenInputFile);

    file_wprint (Root, 0, OutputFile);

    fwprintf (OutputFile, L".");

    fclose (OutputFile);

    return 0;
}

void file_wprint (SNode* Node, int n, FILE* OutputFile)
{
    if (Node == NULL)
    {
        return;
    }

    //wprintf (L"!!!!!!!\n");
    do_tab (n, OutputFile);
    fwprintf (OutputFile, L"(%ls)\n", Node->data);

    if (Node->left != NULL)
    {
        do_tab (n, OutputFile);
        fwprintf (OutputFile, L"{\n");
        file_wprint (Node->left, n + 1, OutputFile);
        do_tab (n, OutputFile);
        fwprintf (OutputFile, L"}\n");
    }

    if (Node->right != NULL)
    {
        //wprintf (L"i m here %ls\n", Node->data);
        do_tab (n, OutputFile);
        fwprintf (OutputFile, L"{\n");
        file_wprint (Node->right, n + 1, OutputFile);
        do_tab (n, OutputFile);
        fwprintf (OutputFile, L"}\n");
    }

    // do_tab (n, OutputFile);
    // fwprintf (OutputFile, L"}\n");

    return;
}

int check_sym (SBuffer* Buffer)
{
    if (Buffer->Array[Buffer->ip] == L'{')
    {
        seek_out (Buffer);
    }
    else if (Buffer->Array[Buffer->ip] == L'}')
    {
        seek_out (Buffer);

        //wprintf (L"Leafed\n");

        seek (Buffer);

        return LEAF;
    }

    return 0;
}

int read_node (SBuffer* Buffer, SNode* Parent)
{
    seek (Buffer);

    // wprintf (  L"-2|%d|%ls|-\n"
    //             "%ls""\n"
    //             "-2-\n"
    //             , Buffer->branch, Parent->data
    //             , &(Buffer->Array[Buffer->ip]));

    wchar_t* Line = NULL;

    if (swscanf (&Buffer->Array[Buffer->ip], L"(%ml[^).]", &Line) < 1)
    {
        wprintf (KRED L"'%lc' Error!=========================================================\n" KNRM, Buffer->Array[Buffer->ip]);

        return 1;
    }
    seek_out (Buffer);
    seek (Buffer);

    switch (Buffer->branch)
    {
        case left:
            add_left_branch (make_node (Line), Parent);

            if (check_sym (Buffer) != 0)
            {
                return LEAF;
            }

           // wprintf (  L"\n==========left==============\n");

            Buffer->branch = left;

            if (read_node (Buffer, Parent->left) == LEAF)
            {
                //wprintf (  L"\n==========1==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            Buffer->branch = right;

            if (read_node (Buffer, Parent->left) == LEAF)
            {
                //wprintf (  L"\n==========2==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            break;

        case right:
            add_right_branch (make_node (Line), Parent);

            if (check_sym (Buffer) != 0)
            {
                return LEAF;
            }

            //wprintf (  L"\n===========right=============\n");

            Buffer->branch = left;

            if (read_node (Buffer, Parent->right) == LEAF)
            {
                //wprintf (  L"\n==========3==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            Buffer->branch = right;

            if (read_node (Buffer, Parent->right) == LEAF)
            {
               // wprintf (  L"\n==========4==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            break;

        default:
            Errors += BranchSwitchError;
            MCA (Errors == 0, 1);
    }

    //free (Line);//!

    return 0;
}

void seek (SBuffer* Buffer)
{
    for (; Buffer->ip < Buffer->size; Buffer->ip++)
    {
        // if ((wcscmp (Buffer->Array[Buffer->ip], L"\n")) && ((wcscmp (Buffer->Array[Buffer->ip], L" "))))
        if ((Buffer->Array[Buffer->ip] != L'\n') && ((Buffer->Array[Buffer->ip] != L' ')))
        {
            return;
        }
    }

    return;
}

void seek_out (SBuffer* Buffer)
{
    for (; Buffer->ip < Buffer->size; Buffer->ip++)
    {
        // if ((wcscmp (Buffer->Array[Buffer->ip], L"\n")) && ((wcscmp (Buffer->Array[Buffer->ip], L" "))))
        if ((Buffer->Array[Buffer->ip] == L'\n'))// || ((Buffer->Array[Buffer->ip] == L' ')))
        {
            Buffer->ip++;
            return;
        }
    }

    return;
}

void do_tab (int n, FILE* OutputFile)
{
    for (int i = 0; i < n; i++)
    {
        fwprintf (OutputFile, L"" TAB);
    }

    return;
}

//===================================================================================================================================================================

void correct_node (SNode* Node, TNode Data)
{
    Node->data = Data;

    return;
}

SNode* make_node (TNode Data)
{
    SNode* Node = (SNode*) calloc (1, sizeof (SNode));

    Node->data = Data;

    return Node;
}

SNode* add_left_branch (SNode* Node, SNode* Parent)
{
    Parent->left = Node;

    Node->parent = Parent;

    return Node;
}

SNode* add_right_branch (SNode* Node, SNode* Parent)
{
    Parent->right = Node;

    Node->parent = Parent;

    return Node;
}

// int tree_constructor (SNode* Root, TNode Data)
// {
//     Root->data = Data;
//
//     return 0;
// }

int delete_tree (SNode* Node)
{
    //printf ("deleting %lg\n", Node->data);

    if (Node == NULL)
    {
        return 0;
    }

    //Node->data = 0;
    Node->parent = 0;

    if (Node->left != NULL)
    {
        delete_tree (Node->left);
    }

    if (Node->right != NULL)
    {
        delete_tree (Node->right);
    }

   // wprintf (L"!\n");

    free (Node->data);

    //wprintf (L"!!\n");

    free (Node);



    //printf ("deleted\n");

    return 0;
}

void print_inorder (SNode* Node)
{
    if (Node == NULL)
    {
        return;
    }

    printf ("(");

    if (Node->left != NULL)
    {
        print_inorder (Node->left);
    }

    print_node (Node->data);

    if (Node->right != NULL)
    {
        print_inorder (Node->right);
    }

    printf (")");

    return;
}

void wprint_inorder (SNode* Node)
{
    if (Node == NULL)
    {
        return;
    }

    wprintf (L"(");

    if (Node->left != NULL)
    {
        wprint_inorder (Node->left);
    }

    wprint_node (Node->data);

    if (Node->right != NULL)
    {
        wprint_inorder (Node->right);
    }

    wprintf (L")");

    return;
}

void wprint_preorder (SNode* Node)
{
    if (Node == NULL)
    {
        return;
    }

    wprint_node (Node->data);

    wprintf (L"(");

    if (Node->left != NULL)
    {
        wprint_preorder (Node->left);
    }

    if (Node->right != NULL)
    {
        wprint_preorder (Node->right);
    }

    wprintf (L")");

    return;
}

void print_node (TNode Data)
{
    printf (TNodePrintType, Data);

    return;
}

void wprint_node (wchar_t* Data)
{
    wprintf (L"%ls", Data);

    return;
}


