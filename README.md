Moving-rank in a window

Problem description - Given an input array of size N, window size of K. Find the rank of the each element of the input array within its trailling window of K. Output the rank into an array of size N. Rank(d) = t means there are t elements smaller for d in the trailling window.

For example, given a length-10 input {0.0, 1.0, 2.0, 3.0, 4.0, 4.5, 3.5, 4.2, 4.1, 0.5} and window_size = 5. The rank of 4.5 will be 4 since there the trailling window for 4.5 is {1.0, 2.0, 3.0, 4.0, 4.5} and there are 4 elements smaller than 4.5. Note the rank for 2.0 is undefined since there are only 2 elements and can't be used to construct a training_window. So the output is {-1, -1, -1, -1, -1, 4, 2, 3, 2, 0} while -1 represnts undefined.

Solution - Maintain a binary search tree to represent the trailing window of size K. Lookup, removal, insertion and ranking of a tree node all take log(K) time. Moving the training window to the end of the input array by removing the front element and adding the new element, and then calaculate the rank. For the O(N) output, the total time complexity will be O(log(K) * N).

The tricky part is we will need a balanced binary search tree with the Rank operation(https://algs4.cs.princeton.edu/32bst/) supported. I am using https://github.com/phillipberndt/bostree as this is the only implementation I can find.
