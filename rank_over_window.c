#include <stdio.h>
#include <stdlib.h>

#include "bostree.h"

void _free_function(BOSNode *node)
{
    // Skip.
}

int _comparison_function(const double *lhs, const double *rhs)
{
    if (*lhs == *rhs)
    {
        return 0;
    }
    return *lhs > *rhs ? 1 : -1;
}

// output[j] = rank(input[j]) = k means there are k elements smaller than input[j] in input[j - window_size+1 : j]
void rank_over_window(double input[], unsigned int output[], unsigned int input_size, unsigned int window_size)
{
    BOSTree *tree = bostree_new((BOSTree_cmp_function)_comparison_function, _free_function);
    // Initializing the tree with the first window_size of elements;
    for (size_t i = 0; i < window_size; i++)
    {
        bostree_insert(tree, &input[i], NULL);
        // Skip first window_size elements in the output.
        output[i] = -1;
    }
    // Move the window forward
    for (size_t j = window_size; j < input_size; j++)
    {
        BOSNode *front_node_to_remove = bostree_lookup(tree, &input[j - window_size]);
        bostree_remove(tree, front_node_to_remove);
        BOSNode *new_node = bostree_insert(tree, &input[j], NULL);
        output[j] = bostree_rank(new_node);
    }
    bostree_destroy(tree);
}

int main()
{
    double input[10] = {0.0, 1.0, 2.0, 3.0, 4.0, 4.5, 3.5, 4.2, 4.1, 0.5};
    unsigned int output[10];
    unsigned int expected_output[10] = {-1, -1, -1, -1, -1, 4, 2, 3, 2, 0};
    unsigned int input_size = 10;
    unsigned int window_size = 5;
    rank_over_window(input, output, input_size, window_size);

    for (int i = 0; i < input_size; i++)
    {

        if (output[i] != expected_output[i])
        {
            fprintf(stderr, "Exiting due to errors.\n");
            abort();
        }
    }
    fprintf(stdout, "Looks OK.\n");
    exit(0);
}
