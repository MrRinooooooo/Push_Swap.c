#include "push_swap.h"

/*
    Flag [0] = BENCH
    Flag [1] = SIMPLE
    Flag [2] = MEDIUM
    Flag [3] = COMPLEX
    Flag [4] = ADAPTIVE
*/

void    flags_set_zero(int flags[])
{
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;
    flags[4] = 0;
}

void    set_flags(int flags[], int i)
{
    flags[i] += 1;
}

void    n_flags(int flags[], int argc, char *argv[])
{
    int i;

    i = 1;
    while (i <= 2)
    {
        if (argv[i][0] == '-' && argv[i][1] == '-')
        {
            if (ps_strcmp(argv[i], "--bench") == 0)
                set_flags(flags, 0); 
            else if (ps_strcmp(argv[i], "--simple") == 0)
                set_flags(flags, 1);
            else if (ps_strcmp(argv[i], "--medium") == 0)
                set_flags(flags, 2);
            else if (ps_strcmp(argv[i], "--complex") == 0)
                set_flags(flags, 3);
            else if (ps_strcmp(argv[i], "--adaptive") == 0)
                set_flags(flags, 4);
            else 
                print_error();
        }
        i++;
    }
}