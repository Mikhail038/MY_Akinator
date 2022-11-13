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

char* FileName = "LIB/AkinatorLib_1.txt";
char* line = NULL;

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
    wprintf ( KNRM L"Доступные режимы игры:\n"
                "[" Kbright KYLW "И" KNRM "]гра                                                                       " TAB "[" Kbright KYLW "G" KNRM "]ame""\n"
                "[" Kbright KCYN "О" KNRM "]пределение                                                                " TAB "[" Kbright KCYN "D" KNRM "]efinition""\n"
                "[" Kbright KBLU "C" KNRM "]охранить (в текущий выбранный файл (по умолчанию \"LIB/AkinatorLib_1.txt\"))" TAB "[" Kbright KBLU "S" KNRM "]ave (to current data-base file)""\n"
                "[" Kbright KMGN "П" KNRM "]оменять (файл базы данных)                                                " TAB "[" Kbright KMGN "C" KNRM "]hange (data-base file)""\n"
                "[" Kbright KRED "В" KNRM "]ыход                                                                      " TAB "[" Kbright KRED "E" KNRM "]xit""\n"
                "");
    return;
}

void print_head (void)
{
    wprintf (KNRM L"\n""Я - Искуственный Интеллект " Kbright Kunderscore KWHT "\"ИбрагиМ-3000\"" KNRM " (ТМ 2022)\n"
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
#undef DEF_MOD

//===================================================================================================================================================================

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

    free (line);

    return 0;
}


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
        wprintf (  Kreverse L"-> ");

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

//===================================================================================================================================================================

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

int change_base (SNode* Root)
{
   // char* InputFile = NULL;

    wprintf (KNRM L"Введите полный путь от текущей директории до файла, из которого требуется брать данные""\n"
            Kreverse "-> " );

    wscanf (L" %m[^\n]", &line);

    FileName = line;

    //write_tree (Root);
    free (Root->data);

    delete_tree (Root->left);

    delete_tree (Root->right);


    //Root = make_node (NULL);
    //wprintf (L"!!!\n");

    read_tree (Root);

    wprintf (KNRM L"Новая база из файла " Kbright "\"%s\"" KNRM " прочитана, готов к работе\n\n", FileName);

    // free (InputFile);

    return 0;
}

//===================================================================================================================================================================

int play_aki_definition (SNode* Root)
{
    wprintf (KNRM L"Введите название объекта, определение которого вы хотите найти\n"
            Kreverse "-> ");

    wchar_t* Line = NULL;

    SNode* Node = NULL;

    while (true)
    {
        if (wscanf (L" %ml[^\n]", &Line) > 0)
        {
            Node = find_node (Line, Root);

            if ( Node != NULL)
            {
                wprintf (KNRM L"Я нашел этот объект - " KYLW "%ls\n" KNRM, Node->data);

                wprintf (KYLW L"");

                print_definition (Node, 0);

                wprintf (L"\n\n");
            }
            else
            {
                wprintf (KNRM L"\"" KRED "%ls" KNRM "\" не найден!\n", Line);
            }

            free (Line);

            return 0;
        }
    }

   // wscanf (L"");

}

SNode* find_node (wchar_t* Line, SNode* Node)
{

    if (Node == NULL)
    {
        return NULL;

        wprintf (L"'%ls'\n", Node->parent);
    }
    // if  (((Node->left == NULL) && (Node->right != NULL)) ||
    //     ((Node->right == NULL))&& (Node->left != NULL))
    // {
    //     wprintf (L"'%ls'\n", Node->data);
    // }

    if ((Node->left == NULL) && (Node->right == NULL))
    {
        if (wcscmp (Line, Node->data) == 0)
        {
            return Node;
        }
    }

    SNode* RetValue = find_node (Line, Node->left);

    if (RetValue != NULL)
    {
        return RetValue;
    }

    RetValue = find_node (Line, Node->right);

    return RetValue;
}

void print_definition (SNode* Node, int n)
{
    //wprintf (L"dt %ls bt %d \n", Node->data, Node->branch);
    wprintf ( L"%ls " KNRM, Node->data);


    if ((n > 0) && (Node->parent != NULL))
    {
        int randomizer = (rand () % 6) + 1;

        switch (randomizer)
        {
            case 1:
                (Node->branch == Left) ? wprintf (KNRM L"и " KGRN) : wprintf (KNRM L"и не " KRED );
                break;

            case 2:
                (Node->branch == Left) ? wprintf (KNRM L"а также " KGRN) : wprintf (KNRM L"a также " KRED "не "  );
                break;

            case 3:
                (Node->branch == Left) ? wprintf (KNRM L"и в том числе " KGRN) : wprintf (KNRM L"но " KRED "не "  );
                break;

            case 4:
                (Node->branch == Left) ? wprintf (KNRM L"плюс " KGRN) : wprintf (KNRM L"и ни капли " KRED "не "  );
                break;

            case 5:
                (Node->branch == Left) ? wprintf (KNRM L"еще и " KGRN) : wprintf (KNRM L"и ни в коем случае " KRED "не "  );
                break;

            case 6:
                (Node->branch == Left) ? wprintf (KNRM L"к тому же " KGRN) : wprintf (KNRM L"хотя и " KRED "не " );
                break;

            default:
                wprintf (L"ERROR\n");
                break;
        }
    }

    if (n == 0)
    {
        wprintf (KNRM L"обладает свойствами: ");
        (Node->branch == Left) ? wprintf (L"" KGRN) : wprintf (L"не " KRED) ;

    }

    if (Node->parent != NULL)
    {
        print_definition (Node->parent, n + 1);
    }

    return;
}

//===================================================================================================================================================================

int read_tree (SNode* Root)
{
    FILE* InputFile = fopen (FileName, "r");
    MCA (InputFile != NULL, CantOpenInputFile);

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

    Buffer.branch = Left;
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

    Buffer.branch = Right;
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
    FILE* OutputFile = fopen (FileName, "w");
    MCE (OutputFile != NULL, CantOpenInputFile);

    file_wprint (Root, 0, OutputFile);

    fwprintf (OutputFile, L".");

    fclose (OutputFile);

    wprintf (KNRM L"\n""Данные сохранены в файл \"%s\" \n\n", FileName);

    make_gv_tree (Root);

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
        case Left:
            add_left_branch (make_node (Line), Parent);

            if (check_sym (Buffer) != 0)
            {
                return LEAF;
            }

           // wprintf (  L"\n==========left==============\n");

            Buffer->branch = Left;

            if (read_node (Buffer, Parent->left) == LEAF)
            {
                //wprintf (  L"\n==========1==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            Buffer->branch = Right;

            if (read_node (Buffer, Parent->left) == LEAF)
            {
                //wprintf (  L"\n==========2==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            break;

        case Right:
            add_right_branch (make_node (Line), Parent);

            if (check_sym (Buffer) != 0)
            {
                return LEAF;
            }

            //wprintf (  L"\n===========right=============\n");

            Buffer->branch = Left;

            if (read_node (Buffer, Parent->right) == LEAF)
            {
                //wprintf (  L"\n==========3==============\n");

                if (check_sym (Buffer) != 0)
                {
                    return LEAF;
                }
            }

            Buffer->branch = Right;

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

    Node->branch = Left;

    return Node;
}

SNode* add_right_branch (SNode* Node, SNode* Parent)
{
    Parent->right = Node;

    Node->parent = Parent;

    Node->branch = Right;

    return Node;
}

int delete_tree (SNode* Node)
{
    //printf ("deleting %lg\n", Node->data);

    if (Node == NULL)
    {
        return 0;
    }

    //Node->data = 0;
    // if (Node->parent != NULL)
    // {
    //     Node->parent = 0;
    // }

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

//===================================================================================================================================================================

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

//===================================================================================================================================================================

int make_gv_tree (SNode* Root)
{
    FILE* gvInputFile = fopen ("gvAkinator.dot", "w");
    MCA (gvInputFile != NULL, 1);

    fprintf (gvInputFile,
        R"(digraph {
    rankdir = VR
    graph [splines = ortho];
    bgcolor = "white";
    node [shape = "plaintext", style = "solid"];)");

    make_gv_node (gvInputFile, Root);

    fprintf (gvInputFile, "\n}\n");

    draw_gv_tree ();

    return 0;
}

void make_gv_node (FILE* File, SNode* Node)
{
    if (Node == NULL)
    {
        return;
    }

    fprintf (File,
        R"(

                    node_%p
                    [
                        label=
                        <
                        <table border="0" cellborder="1" cellspacing="0">
                            <tr>
                                <td colspan="2"> Node #%p </td>
                            </tr>
                            <tr>
                                <td colspan="2" bgcolor = "#d2d459">)", Node, Node);

    print_gv_node (File, Node);

    fprintf (File,
            R"(</td>
                            </tr>)");

    if (Node->left != NULL)
    {
        fprintf(File,
        R"(
                            <tr>
                                <td bgcolor = "#61de4b" port="left" > %p   </td>
                                <td bgcolor = "#f27798" port="right"> %p   </td>
                            </tr>)", Node->left, Node->right);
    }

    fprintf (File, R"(
                        </table>
                        >
                    ]
                    )");

    if (Node->parent != NULL)
    {
        //wprintf (L"!%d!\n", Node->branch);
        if (Node->branch == Left)
        {
            fprintf (File,  "\n                    node_%p:<left> -> node_%p;",
                        Node->parent, Node);
        }
        else
        {
            fprintf (File,  "\n                    node_%p:<right> -> node_%p;",
                        Node->parent, Node);
        }
    }

    make_gv_node (File, Node->left);
    make_gv_node (File, Node->right);
}

void print_gv_node (FILE* File, SNode* Node)
{
    fprintf (File, " %ls ", Node->data);

    //fprintf (File, " 1 ");

    return;
}

void draw_gv_tree (void)
{
    system ("dot -Tpng gvAkinator.dot -o gvAkinator.png");

    system ("xdg-open gvAkinator.png");

    return;
}

//===================================================================================================================================================================

