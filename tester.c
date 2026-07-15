#include "push_swap.h"

int main(int argc, char *argv[])
{
    static int  flags[5];
    int n;
    int i;
    //float   disorder;

    flags_set_zero(flags);
    printf("CIAO\n");
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
    flags_parser(flags, argc, argv);
    printf("CIAO2\n");
    /*
    i = 0;
    while(i < 5)
    {
        printf("flag %i: %i\n", i, flags[i]);
        i++;
    }
    */
    i = 0;
    int flags_n = flags_num(flags);
    printf("CIAO3\n");
    int arr_len = argc - flags_n - 1;
    int *int_arr;
    int_arr = int_arr_parser(argc, argv, flags_n);
    printf("CIAO4\n");
    while(i < arr_len)
    {
        printf("Arr[%i] = %i\n", i, int_arr[i]);
        i++;
    }

    return(0);
}