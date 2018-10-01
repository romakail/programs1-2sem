
#define DEF_push                              \
    fscanf  (ptrSource      , "%lg", &temp);  \
    fprintf (ptrProcCommands, "%lg", temp);   \
    nCommands++;

#define DEF_pop

#define DEF_out

#define DEF_scan

#define DEF_add

#define DEF_diff

#define DEF_mult

#define DEF_div

#define DEF_sqrt

#define DEF_e

#define DEF_ne

#define DEF_m

#define DEF_me

#define DEF_l

#define DEF_le

#define DEF_pushreg                                             \
    fscanf  (ptrSource      , "%s" , labelName);                \
    fprintf (ptrProcCommands, "%d" , labelName [0] - AMINUS1);  \
    nCommands++;

#define DEF_popreg                                              \
    fscanf  (ptrSource      , "%s" , labelName);                \
    fprintf (ptrProcCommands, "%d" , labelName [0] - AMINUS1);  \
    nCommands++;

#define DEF_pushop                            \
    fscanf  (ptrSource      , "%d", &temp2);  \
    fprintf (ptrProcCommands, "%d", temp2);  \
    nCommands++;

#define DEF_popop                             \
    fscanf  (ptrSource      , "%d", &temp2);  \
    fprintf (ptrProcCommands, "%d", temp2);   \
    nCommands++;

#define DEF_label                                                       \
    fscanf (ptrSource, "%s", labelName);                                \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jump                                                        \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumpe                                                       \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumpne                                                      \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumpm                                                       \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumpme                                                      \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumpl                                                       \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_jumple                                                      \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_End                                                         \
    endOfProg = 1;

#define DEF_meow

#define DEF_call                                                        \
    fscanf  (ptrSource, "%s", labelName);                               \
    fprintf (ptrProcCommands, "%lg", nameInNumber (labelName, names));  \
    nCommands++;

#define DEF_ret

/*#define DEF_EOF                                                         \
    endOfProg = 1;*/








//pust` zdes` polezhit
/* if      (strcmp (command, "push") == 0 )
        {
            fprintf (ptrProcCommands, "%d  ", PUSH );
            fscanf  (ptrSource      , "%lg", &temp);
            fprintf (ptrProcCommands, "%lg", temp);
            nCommands ++;
        }
        else if (strcmp (command, "pop")  == 0 )
        {
            fprintf (ptrProcCommands, "%d", POP);
        }
        else if (strcmp (command, "out")  == 0 )
        {
            fprintf (ptrProcCommands, "%d", OUT);
        }
        else if (strcmp (command, "scan")     == 0 )
        {
            fprintf (ptrProcCommands, "%d", SCAN);
        }
        else if (strcmp (command, "add")      == 0 )
        {
            fprintf (ptrProcCommands, "%d", ADD);
        }
        else if (strcmp (command, "diff")     == 0 )
        {
            fprintf (ptrProcCommands, "%d", DIFF);
        }
        else if (strcmp (command, "mult")     == 0 )
        {
            fprintf (ptrProcCommands, "%d", MULT);
        }
        else if (strcmp (command, "div")      == 0 )
        {
            fprintf (ptrProcCommands, "%d", DIV);
        }
        else if (strcmp (command, "sqrt")     == 0 )
        {
            fprintf (ptrProcCommands, "%d", SQRT);
        }
        else if (strcmp (command, "pushreg")  == 0 )
        {
            fprintf (ptrProcCommands, "%d  ", PUSHREG);
            fscanf  (ptrSource      , "%s" , command);
            fprintf (ptrProcCommands, "%d" , command [0] - AMINUS1);
            nCommands++;

        }
        else if (strcmp (command, "popreg")  == 0 )
        {
            fprintf (ptrProcCommands, "%d  ", POPREG);
            fscanf  (ptrSource      , "%s" , command);
            fprintf (ptrProcCommands, "%d" , command [0] - AMINUS1);
            nCommands++;
        }
        else if (strcmp (command, "label") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", LABEL);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jump") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMP);
            fscanf  (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumpe") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPE);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumpne") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPNE);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumpm") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPM);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumpme") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPME);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumpl") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPL);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "jumple") == 0)
        {
            fprintf (ptrProcCommands, "%d  ", JUMPLE);
            fscanf (ptrSource, "%s", command);
            fprintf (ptrProcCommands, "%lg", nameInNumber (command, names));
            nCommands++;
        }
        else if (strcmp (command, "end") == 0 )
        {
            fprintf (ptrProcCommands, "%d", END);
            endOfProg = 1;
        }*/

















