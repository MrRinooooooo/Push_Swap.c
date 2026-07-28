#include "push_swap.h"
// compute disorder
float   compute_disorder(int array[], int arraylen)
{
    int   mistakes;
    int   total_pairs;
    float   disorder;
    int i;
    int j;

    total_pairs = 0;
    mistakes = 0;
    i = 0;
    while (i < arraylen)
    {
        j = i + 1;
        while (j < arraylen)
        {
            if (array[i] > array[j])
                mistakes += 1;
            else if (array[i] == array[j])
                print_error();
            j++;
            total_pairs += 1;
        }
        i++;
    }
    disorder = mistakes / total_pairs;
    return (disorder);
}