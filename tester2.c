#include "push_swap.h"

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
            if (array[i]  == array[j])
                print_error();
            if (array[i] > array[j])
                mistakes += 1;
            j++;
            total_pairs += 1;
        }
        i++;
    }
    disorder = (float)mistakes / (float)total_pairs;
    return (disorder);
}

int main(void)
{
    int array[] = {4,4,8,10,-30};
    int arraylen;
    float disorder;

    disorder = compute_disorder(array, 5);
    printf("%f", disorder);
    return (0);   
}