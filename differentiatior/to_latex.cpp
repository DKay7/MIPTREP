#include "differentiator.h"
#include "text_lib/texlib.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/random.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LatexCtor (Latex* latex)
{   
    assert (latex);
         
    char filename_latex[] = "/tmp/diff_fileXXXXXX";
    int latex_fd = mkstemp (filename_latex);
    ASS (latex_fd != -1, (void) 0);

    FILE* latex_file = fdopen (latex_fd, "w");
    ASS (latex_file, (void) 0);
    
    latex->print_to = latex_file;
    strcpy (latex->filename, filename_latex);

    TextCtor (&latex->init, "./data/latex_init.txt");
    TextCtor (&latex->close, "./data/latex_ending.txt");
    TextCtor (&latex->trans_phrases, "./data/latex_phrases.txt");
    TextCtor (&latex->final_phrases, "./data/latex_end_phrases.txt");

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void LatexDtor (Latex* latex)
{
    fclose   (latex->print_to);
    TextDtor (&latex->init);
    TextDtor (&latex->close);
    TextDtor (&latex->trans_phrases);
    TextDtor (&latex->final_phrases);
    
    latex = NULL;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void InitTexPrint (Latex* latex, Node* node)
{   
    assert (latex);
    assert (latex->print_to);

    unsigned int seed;
    getrandom (&seed, sizeof (seed), GRND_NONBLOCK);
    srand(seed);

    SaveLinesToFile (&latex->init, latex->print_to);
    
    char replacement_letter = 'A';
    int depth = 0;

    bool need_replacement = FindNodesToReplace (node, &depth, &replacement_letter);

    fprintf (latex->print_to, "\n\n\\begin{equation}\n");
    PrintNodeToTex (node, latex->print_to);
    fprintf (latex->print_to, "\n\\end{equation}\n\n");

    if (need_replacement)
    {   
        fprintf (latex->print_to, "где:\n\n");
        PrintReplacementNotation (latex, node);
        fprintf (latex->print_to, "\n\n");
    }

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void EndTexPrint (Latex* latex, Node* node)
{   
    assert (latex);
    assert (latex->print_to);

    setvbuf(latex->print_to, NULL, _IONBF, 0);

    int phrase_num = rand () % (int) latex->final_phrases.non_empty_lines;
    char* end_phrase = latex->final_phrases.lines[phrase_num].ptr;

    char replacement_letter = 'A';
    int depth = 0;
    bool need_replacement = FindNodesToReplace (node, &depth, &replacement_letter);

    fprintf (latex->print_to, "\n%s\n", end_phrase);
    fprintf (latex->print_to, "\n\n\\begin{equation}\n");
    PrintNodeToTex (node, latex->print_to);
    fprintf (latex->print_to, "\n\\end{equation}\n\n");
    
    if (need_replacement)
    {   
        fprintf (latex->print_to, "где:\n\n");
        PrintReplacementNotation (latex, node);
        fprintf (latex->print_to, "\n\n");
    }

    SaveLinesToFile (&latex->close, latex->print_to);

    printf("\n[имя latex-файла:\t%s]\n", latex->filename);

    char compile_cmd[128] = "";
    sprintf (compile_cmd, "./data/cleartex.sh %s ./data", latex->filename);

    ASS (system (compile_cmd) == 0, (void) 0);
    
    return;    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintDifferentiationToTex (Latex* latex, Node* prev_node, Node* cur_node)
{   
    assert (latex);
    assert (latex->print_to);
    assert (cur_node);
    assert (prev_node);

    if (rand () % 100 <= RANDOM_PROBABILITY)
    {
        int phrase_num = rand () % (int) latex->trans_phrases.non_empty_lines;
        char* trans_phrase = latex->trans_phrases.lines[phrase_num].ptr;
        fprintf (latex->print_to, "\n\n%s\n\n", trans_phrase);
    }

    char replacement_letter = 'A';

    int diff_subtree_depth = 0;
    int orig_subtree_depth = 0;
    bool need_diff_replacement = FindNodesToReplace (cur_node,  &diff_subtree_depth, &replacement_letter);
    bool need_orig_replacement = FindNodesToReplace (prev_node, &orig_subtree_depth, &replacement_letter);

    fprintf (latex->print_to, "\n\n\\begin{equation}\n\\frac{d}{dx}\\left(");
    PrintNodeToTex (prev_node, latex->print_to);
    fprintf (latex->print_to, "\\right) = ");
    PrintNodeToTex (cur_node, latex->print_to);
    fprintf (latex->print_to, "\n\\end{equation}\n\n");

    if (need_diff_replacement || need_orig_replacement)
    {   
        fprintf (latex->print_to, "где:\n\n");
        PrintReplacementNotation (latex, prev_node);
        fprintf (latex->print_to, "\n\n");
        PrintReplacementNotation (latex, cur_node);
        fprintf (latex->print_to, "\n\n");
    } 

    return;
}

void PrintSimplificationToTex (Latex* latex, Node* prev_node, Node* cur_node)
{   
    assert (latex);
    assert (latex->print_to);
    assert (cur_node);
    assert (prev_node);

    if (rand () % 100 <= RANDOM_PROBABILITY)
    {
        int phrase_num = rand () % (int) latex->trans_phrases.non_empty_lines;
        char* trans_phrase = latex->trans_phrases.lines[phrase_num].ptr;
        fprintf (latex->print_to, "\n\n%s\n\n", trans_phrase);
    }
    
    char replacement_letter = 'A';
    int orig_depth = 0;
    int simp_depth = 0;
    bool orig_need_replacement = FindNodesToReplace (prev_node, &orig_depth, &replacement_letter);
    bool simp_need_replacement = FindNodesToReplace (cur_node,  &simp_depth, &replacement_letter);

    fprintf (latex->print_to, "\n\n\\begin{equation}\n");
    PrintNodeToTex (prev_node, latex->print_to);
    fprintf (latex->print_to, " = ");
    PrintNodeToTex (cur_node, latex->print_to);
    fprintf (latex->print_to, "\n\\end{equation}\n\n");

    if (simp_need_replacement || orig_need_replacement)
    {   
        fprintf (latex->print_to, "где:\n\n");
        PrintReplacementNotation (latex, prev_node);
        fprintf (latex->print_to, "\n\n");
        PrintReplacementNotation (latex, cur_node);
        fprintf (latex->print_to, "\n\n");
    }

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintNodeToTex (Node* cur_node, FILE* latex)
{
    assert (cur_node);
    assert (latex);

    if (cur_node->need_replacement)
    {
        fprintf (latex, "%c", cur_node->replacement_letter);
        return;
    }
    

    switch (cur_node->type)
    {   
        case OPERATOR:
        {
            bool need_l_brackets = false;
            bool need_r_brackets = false;
            IsBracketsNedeed (cur_node, &need_l_brackets, &need_r_brackets);

            switch (cur_node->data.operator_)
            {
                #define OP_DEF(enum_name, str, c, d, o, latex_repr, ...) \
                    case (enum_name):                                    \
                        latex_repr;
                
                #include "operators.h"
                #undef OP_DEF

                default:
                    fprintf (latex, "Unknown operator");
                    break;
            }
            break;
        }

        case VARIABLE:
            fprintf (latex, " %c ", cur_node->data.variable_);
            break;

        case CONSTANT:
            fprintf (latex, " %lg ", cur_node->data.constant_);
            break;

        case INV_T:
        default:
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool FindNodesToReplace (Node* cur_node, int* cur_depth, char* replacement_letter)
{   
    assert (cur_depth);
    assert (cur_node);
    assert (replacement_letter);

    int  left_depth  = 0;
    int  right_depth = 0;
    bool need_left_replacement  = false;
    bool need_right_replacement = false;
    
    if (L)
        need_left_replacement  = FindNodesToReplace (L, &left_depth, replacement_letter);

    if (R)
        need_right_replacement = FindNodesToReplace (R, &right_depth, replacement_letter);

    if (cur_node->type == CONSTANT || cur_node->type == VARIABLE)
    {
        (*cur_depth) = 1;
        return false;
    }

    (*cur_depth) = left_depth + right_depth;

    if (cur_node->type == OPERATOR         && (*cur_depth) >= DEPTH_LEEVEL_MAX && \
        right_depth    <  DEPTH_LEEVEL_MAX && left_depth   < DEPTH_LEEVEL_MAX)
    {
        cur_node->need_replacement = true;
        cur_node->replacement_letter = (*replacement_letter);
        (*replacement_letter) ++;
        (*cur_depth) = 1;

        return true;
    }

    return need_left_replacement | need_right_replacement;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintReplacementNotation (Latex* latex, Node* cur_node)
{   
    assert (latex);
    assert (cur_node);

    if (cur_node->type == OPERATOR && cur_node->need_replacement)
    {   
        fprintf (latex->print_to, "$%c = ", cur_node->replacement_letter);

        cur_node->need_replacement = false;

        PrintNodeToTex (cur_node, latex->print_to);
        fprintf (latex->print_to, "$\n\n");
    }

    if (L)
        PrintReplacementNotation (latex, L);
    if (R)
        PrintReplacementNotation (latex, R);

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void IsBracketsNedeed (Node* cur_node, bool* need_l_brackets, bool* need_r_brackets)
{
    assert (cur_node);
    assert (need_l_brackets);
    assert (need_r_brackets);
    assert (need_l_brackets != need_r_brackets);
    ASS (cur_node->type == OPERATOR, (void) 0);

    int cur_priority   = GetOperatorPriority (cur_node);
    int left_priority  = -1;
    int right_priority = -1;

    if (L)
        left_priority  = GetOperatorPriority (L);
        
    if (R)
        right_priority = GetOperatorPriority (R);

    if (cur_priority > left_priority)
        (*need_l_brackets) = true;
    
    if (cur_priority > right_priority)
        (*need_r_brackets) = true;
    
    if (left_priority  == -1)
        (*need_l_brackets) = false;
    
    if (right_priority == -1)
        (*need_r_brackets) = false;

    return;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetOperatorPriority (Node* node)
{
    assert (node);
    
    if (node->type != OPERATOR)
        return -1;

    switch (node->data.operator_)
    {
        #define OP_DEF(enum, str, comp, diff, simp, print, priority)    \
            case enum:                                                  \
                return priority;

        #include "operators.h"
        #undef OP_DEF

        default:
            return -1;
    }
}