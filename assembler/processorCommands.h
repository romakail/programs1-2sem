
#define DEF_push                                     \
    stackPush   (rStack, commandsMassive [++i]);

#define DEF_pop                                      \
    stackPop    (rStack);

#define DEF_out                                      \
    printfElem_t (stackPop (rStack));

#define DEF_scan                                     \
    scanf ("%lg", &temp);                            \
    stackPush (rStack, temp);

#define DEF_add                                      \
    stackAddition    (rStack);

#define DEF_diff                                     \
    stackDifference  (rStack);

#define DEF_mult                                     \
    stackComposition (rStack);

#define DEF_div                                      \
    stackDivision    (rStack);

#define DEF_sqrt                                     \
    stackSqrt        (rStack);

#define DEF_e                                        \
    stackEqual       (rStack);

#define DEF_ne                                       \
    stackNotEqual    (rStack);

#define DEF_m                                        \
    stackMore        (rStack);

#define DEF_me                                       \
    stackMoreEqual   (rStack);

#define DEF_l                                        \
    stackLess        (rStack);

#define DEF_le                                       \
    stackLessEqual   (rStack);

#define DEF_pushreg                                  \
    switch ((int) commandsMassive [++i])             \
        {                                            \
            case REGXA : stackPush (rStack, a);      \
                        break;                       \
                                                     \
            case REGXB : stackPush (rStack, b);      \
                        break;                       \
                                                     \
            case REGXC : stackPush (rStack, c);      \
                        break;                       \
                                                     \
            case REGXD : stackPush (rStack, d);      \
                        break;                       \
                                                     \
            default: printf ("\nProblems with pushreg\n");  \
                     printf ("command is : %d\n", (int) commandsMassive [i]);\
                     dumpStack (rStack);\
                     assert (0);\
        }

#define DEF_popreg                                                              \
     switch ((int) commandsMassive [++i])                                       \
    {                                                                           \
            case REGXA : a = stackPop (rStack);                                 \
                        break;                                                  \
                                                                                \
            case REGXB : b = stackPop (rStack);                                 \
                        break;                                                  \
                                                                                \
            case REGXC : c = stackPop (rStack);                                 \
                        break;                                                  \
                                                                                \
            case REGXD : d = stackPop (rStack);                                 \
                        break;                                                  \
                                                                                \
            default: printf ("\nProblems with popreg\n");                       \
                     printf ("command is : %d\n", (int) commandsMassive [i]);   \
                     dumpStack (rStack);                                        \
                     assert (0);                                                \
    }

#define DEF_pushop                                                      \
    if (operMemory [(int)commandsMassive [++i]] != POISON)              \
    {                                                                   \
        stackPush (rStack, operMemory [(int)commandsMassive [i]]);      \
    }                                                                   \
    else                                                                \
    {                                                                   \
        printf ("\n--ERROR--\nusing unfilled oprative memory\n");       \
        printf ("command is : %d", (int) commandsMassive [i]);          \
        dumpStack (rStack);                                             \
        assert (0);                                                     \
    }

#define DEF_popop                                                       \
    operMemory [(int) commandsMassive [++i]] = stackPop (rStack);


#define DEF_label                                  \
     i++;

#define DEF_jump                                   \
    i = commandsMassive [++i];                     \

#define DEF_jumpe                                  \
    if (stackPop (rStack) == stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_jumpne                                 \
    if (stackPop (rStack) != stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_jumpm                                  \
    if (stackPop (rStack) <  stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_jumpme                                 \
    if (stackPop (rStack) <= stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_jumpl                                  \
    if (stackPop (rStack) >  stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_jumple                                 \
    if (stackPop (rStack) >= stackPop (rStack))    \
        i = commandsMassive [++i];                 \
    else                                           \
        i++;

#define DEF_End                                    \
    out = 1;

#define DEF_meow                                   \
   // printf ("\n\
::::::::::::::::::::::::OOOOOOO:::::::::\n\
::::::::::::::::::::::OOO:OOO:OO::::::::\n\
::OOOOOOO::::::::::OOOO:OOO:OO:OO:::::::\n\
:OOOOOOOOOOOOOOOOOOOO:::OOO::O::O:::::::\n\
:OO::::OOOOOOO::::::::::::OOO::OO:::::::\n\
:OOO::::OOOOOOO::::::::::::::::OO:::::::\n\
::OOO::OOOOOOOO:::::::::::::::::OO::::::\n\
::OOOOOOOOOOOOO::::::::::::::::::OO:::::\n\
:::OOOOOOOOOOO::::::::::::::::::::O:::::\n\
::::OOOOOOOOO:::::::::::::OOOO::::O:::::\n\
::OOOOOOOOOO:::OOO::::::::::::OO::O:::::\n\
:OO:::::OOO::::O:::::OOOO:::::O:::O:::::\n\
O:::::::::OO:::::::::OOO:::::::OOOO:::::\n\
O::::::O:OO:O:O::::::::OO:OO:::::OOO::::\n\
O::O:O::::::O:OO:::OOOOOOO:::::OO:::OO::\n\
::::OOO:::OOO::O:::::::::::::OOO:::OOOO:\n\
:::::::OOOOOOOO:::::::::OOOOOOO::::OOOOO\n\
:::::::::::::OOOOOOOOOOOO:::::OO:::OOOOO\n\
::::::::::::::::OOOOOO::::::::::O::::OOO\n");


#define DEF_call                                   \
    stackPush (&funcStack, (Elem_t) i);            \
    i = commandsMassive [++i];

#define DEF_ret                                    \
    i = 1 + (int) stackPop (&funcStack);

/*#define DEF_EOF                                    \
    i = i;*/




//pust` zdes` polezhit

/*case PUSH : stackPush        (rStack, commandsMassive [++i]);
                     break;

            case POP  : stackPop         (rStack);
                     break;

            case OUT  : printfElem_t     (stackPop (rStack));
                     break;

            case SCAN : scanf ("%lg", &temp);
                        stackPush (rStack, temp);
                     break;

            case ADD  : stackAddition    (rStack);
                     break;

            case DIFF : stackDifference  (rStack);
                     break;

            case MULT : stackComposition (rStack);
                     break;

            case DIV  : stackDivision    (rStack);
                     break;

            case SQRT : stackSqrt        (rStack);
                     break;

            case PUSHREG : switch ((int) commandsMassive [++i])
                     {
                         case REGXA : stackPush (rStack, a);
                                  break;

                         case REGXB : stackPush (rStack, b);
                                  break;

                         case REGXC : stackPush (rStack, c);
                                  break;

                         case REGXD : stackPush (rStack, d);
                                  break;

                         default: printf ("\nProblems with pushreg\n");
                                  printf ("command is : %d\n", (int) commandsMassive [i]);
                                  dumpStack (rStack);
                                  assert (0);

                     }

                     break;

            case POPREG : switch ((int) commandsMassive [++i])
                      {
                          case REGXA : a = stackPop (rStack);
                                   break;

                          case REGXB : b = stackPop (rStack);
                                   break;

                          case REGXC : c = stackPop (rStack);
                                   break;

                          case REGXD : d = stackPop (rStack);
                                   break;

                          default: printf ("\nProblems with popreg\n");
                                   printf ("command is : %d\n", (int) commandsMassive [i]);
                                   dumpStack (rStack);
                                   assert (0);

                      }
                      break;

            case LABEL  : i++;
                          break;

            case JUMP   : i = commandsMassive [++i];
                          break;

            case JUMPE  : if (stackPop (rStack) == stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                          break;

            case JUMPNE : if (stackPop (rStack) != stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                          break;

            case JUMPM  : if (stackPop (rStack) < stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                          break;

            case JUMPME : if (stackPop (rStack) <= stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                          break;

            case JUMPL  : if (stackPop (rStack) > stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                          break;

            case JUMPLE : if (stackPop (rStack) >= stackPop (rStack))
                             i = commandsMassive [++i];
                          else
                             i++;
                         break;

            case END    : out = 1;
                         break;

            default : out = 1;
                     printf ("NO command found\n");
                     dumpStack(rStack);
                     exit (1);*/




