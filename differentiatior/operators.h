#ifndef OP_DEF
#define OP_DEF(...)
#endif

#ifndef UNARY
#define UNARY OP_DEF
#endif

#ifndef BINARY
#define BINARY OP_DEF
#endif

#define CHECK_BINARY                \
        ASS (cur_node->left, 0);    \
        ASS (cur_node->right, 0);

#define CHECK_UNARY                 \
        ASS (cur_node->left, 0);

//right-open
#define BRACKET_RO              \
        if (need_r_brackets)    \
            fprintf (latex, "\\left(");
//right-close
#define BRACKET_RC              \
        if (need_r_brackets)    \
            fprintf (latex, "\\right)");

//left-open
#define BRACKET_LO              \
        if (need_l_brackets)    \
            fprintf (latex, "\\left(");

//left-close
#define BRACKET_LC              \
        if (need_l_brackets)    \
            fprintf (latex, "\\right)");

#define PRINT_L                     \
        BRACKET_LO                  \
        PrintNodeToTex (L, latex);  \
        BRACKET_LC

#define PRINT_R                     \
        BRACKET_RO                  \
        PrintNodeToTex (R, latex);  \
        BRACKET_RC  

//PARAMETERS: enum name, string repr., 
//            func to compute, 
//            func to differentiate,
//            func to  simplify
//            func to  print to latex
//            priority value

OP_DEF (INVALID, "unknown operator!",
    {
        return 0;
    },
    {
        break;
    },
    {
        return false;
    },
    {
        fprintf (latex, " бебра ");
        break;
    },
    -1
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

BINARY (ADD, "+",
    {
        CHECK_BINARY
        return ComputeTree (cur_node->left, vars_table) + ComputeTree (cur_node->right, vars_table);
    },
    {
        CHECK_BINARY
        (*size) += 1;
        return_node = UNITE (ADD, DL, DR);
        break;
    },
    {
        if (L->type == CONSTANT && R->type == CONSTANT)
        {   
            REPLACE_SUBTREE (L->data.constant_ + R->data.constant_);
            return true;
        }

        if (L->type == CONSTANT && EQUALS (0, L->data.constant_))
        {
            MOVE_SUBTREE (right);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (0, R->data.constant_))
        {
            MOVE_SUBTREE (left);
            return true;
        }

        return false;
    },
    {   

        PRINT_L

        fprintf (latex, " + ");

        PRINT_R

        break;
    },
    1
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

BINARY (SUB, "-",
    {
        CHECK_BINARY
        return ComputeTree (cur_node->left, vars_table) - ComputeTree (cur_node->right, vars_table);
    },
    {
        CHECK_BINARY
        (*size) += 1;
        return_node = UNITE (SUB, DL, DR);
        break;
    },
    {
        if (L->type == CONSTANT && R->type == CONSTANT)
        {
            REPLACE_SUBTREE (L->data.constant_ - R->data.constant_);
            return true;
        }

        if (L->type == CONSTANT && EQUALS (0, L->data.constant_))
        {   // 0 - left_subtree = -1 * left_subtree

            Node* new_node = NEW_O (MUL);
            new_node->right = cur_node->right;
            new_node->left = NEW_C (-1);

            cur_node->right = NULL;
            NodeDtor (cur_node);
            cur_node = new_node;
                
            return true;
        }

        if (R->type == CONSTANT && EQUALS (0, R->data.constant_))
        {
            REPLACE_SUBTREE (L->data.constant_);
            return true;
        }

        return false;
    },
    {   
        PRINT_L
        fprintf (latex, " - ");
        PRINT_R
        break;
    },
    1
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

BINARY (MUL, "*",
    {
        CHECK_BINARY
        return ComputeTree (cur_node->left, vars_table) * ComputeTree (cur_node->right, vars_table);
    },
    {   
        CHECK_BINARY
        (*size) += 3;
        return_node = UNITE (ADD, UNITE (MUL, CR, DL), UNITE (MUL, DR, CL));
        break;
    },
    {   

        if (L->type == CONSTANT && R->type == CONSTANT)
        {   
            REPLACE_SUBTREE (L->data.constant_ * R->data.constant_);
            return true;
        }

        #define is ->type ==
        if (L is CONSTANT && EQUALS (1, L->data.constant_))
        {   
            MOVE_SUBTREE (right);
            return true;
        }

        if (L->type == CONSTANT && EQUALS (0, L->data.constant_))
        {   
            REPLACE_SUBTREE (0);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (1, R->data.constant_))
        {   
            MOVE_SUBTREE (left);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (0, R->data.constant_))
        {   
            REPLACE_SUBTREE (0);
            return true;
        }

        return false;
    },
    {   
        PRINT_L
        fprintf (latex, " \\cdot ");
        PRINT_R
        break;
    },
    2
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

BINARY (DIV, "/",
    {
        CHECK_BINARY
        return ComputeTree (cur_node->left, vars_table) / ComputeTree (cur_node->right, vars_table);
    },
    {   
        CHECK_BINARY
        (*size) += 6;

        Node* numerator = UNITE (SUB, UNITE (MUL, DL, CR), UNITE (MUL, CL, DR));
        Node* denumerator = UNITE (POW, CR, NEW_C (2));

        return_node = UNITE (DIV, numerator, denumerator);
        break;
    },
    {
        if (L->type == CONSTANT && R->type == CONSTANT)
        {
            REPLACE_SUBTREE (L->data.constant_ / R->data.constant_);
            return true;
        }

        if (L->type == CONSTANT && EQUALS (0, L->data.constant_))
        {
            REPLACE_SUBTREE (0);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (1, R->data.constant_))
        {
            MOVE_SUBTREE (left);
            return true;
        }

        return false;
    },
    {   
        fprintf (latex, " \\frac{ ");
        PrintNodeToTex (L, latex);
        fprintf (latex, " }{ ");
        PrintNodeToTex (R, latex);
        fprintf (latex, " } ");
        break;
    },
    2
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

BINARY (POW, "^",
    {
        CHECK_BINARY
        return pow (ComputeTree (cur_node->left, vars_table), ComputeTree (cur_node->right, vars_table));
    },
    {   
        CHECK_BINARY
        (*size) += 10;
        
        Node* power_term =  UNITE (POW, CL, UNITE (SUB, CL, NEW_C (1)));
        Node* first_term = UNITE (MUL, UNITE (MUL, UNITE (POW, CL, CR), UNITE (LOG, CL, NULL)), DR);
        Node* second_term = UNITE (MUL, UNITE (MUL, power_term, CL), DR);

        return_node = UNITE (ADD, first_term, second_term);
        break;
    },
    {
        if (L->type == CONSTANT && R->type == CONSTANT)
        {
            REPLACE_SUBTREE (pow (L->data.constant_, R->data.constant_));
            return true;
        }

        if (L->type == CONSTANT && EQUALS (0, L->data.constant_))
        {
            REPLACE_SUBTREE (0);
            return true;
        }

        if (L->type == CONSTANT && EQUALS (1, L->data.constant_))
        {
            REPLACE_SUBTREE (1);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (0, R->data.constant_))
        {
            REPLACE_SUBTREE (1);
            return true;
        }

        if (R->type == CONSTANT && EQUALS (1, R->data.constant_))
        {   
            MOVE_SUBTREE (left);
            return true;
        }

        return false;
    },
    {
        fprintf (latex, " { ");
        PRINT_L
        fprintf (latex, " }^{ ");
        PRINT_R
        fprintf (latex, " } ");
        break;
    },
    3
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

UNARY (SIN, "sin",
    {
        CHECK_UNARY
        return sin(ComputeTree (cur_node->left, vars_table));
    },
    {   
        CHECK_UNARY
        (*size) += 2;
        return_node = UNITE (MUL, UNITE (COS, CL, NULL), DL);
        break;
    },
    {
        if (L->type == CONSTANT)
        {
            REPLACE_SUBTREE (sin (L->data.constant_));
            return true;
        }

        return false;
    },
    {
        fprintf (latex, " \\sin {");
        PRINT_L
        fprintf (latex, " } ");
        break;
    },
    2
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

UNARY (COS, "cos",
    {
        CHECK_UNARY
        return cos(ComputeTree (cur_node->left, vars_table));
    },
    {   
        CHECK_UNARY
        (*size) += 4;
        return_node = UNITE (MUL, NEW_C (-1), UNITE (MUL, UNITE (SIN, CL, NULL), DL));
        break;
    },
    {
        if (L->type == CONSTANT)
        {
            REPLACE_SUBTREE (cos (L->data.constant_));
            return true;
        }

        return false;
    },
    {
        fprintf (latex, " \\cos {");
        PRINT_L
        fprintf (latex, " } ");
        break;
    },
    2
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

UNARY (LOG, "ln",
    {
        CHECK_UNARY
        return  log(ComputeTree (cur_node->left, vars_table));
    },
    {   
        CHECK_UNARY
        (*size) += 1;
        return_node = UNITE (DIV, DL, CL);
        break;
    },
    {
        if (L->type == CONSTANT)
        {
            REPLACE_SUBTREE (log (L->data.constant_));
            return true;
        }

        return false;
    },
    {
        fprintf (latex, " \\ln {");
        PRINT_L;
        fprintf (latex, " } ");
        break;
    },
    2
)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef UNARY
#undef UNARY
#endif

#ifdef BINARY
#undef BINARY
#endif

#ifdef OP_DEF
#undef OP_DEF
#endif
