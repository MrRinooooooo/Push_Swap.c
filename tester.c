#include "push_swap.h"

int main(int argc, char *argv[])
{
    static int  flags[5];
    int n;
    //float   disorder;

    flags_set_zero(flags);
    //set_flags(flags, 1);
    /*
    errors_checker(int argc, char *argv[], int flags);
    arg_parser(int argc, char *argv[]);
    disorder = compute_disorder(stack a);
    */
    //n = atoi_safe("-444444444");
    //printf("%i\n", n);

    //printf("\nps_strlen(Ciao Mondo!) = %i", ps_strlen("Ciao Mondo!"));
    //print_error();

    n_flags(flags, argc, argv);

    int i = 0;
        while(i < 5)
        {
            printf("flag %i: %i\n", i, flags[i]);
            i++;
        }

    return(0);
}