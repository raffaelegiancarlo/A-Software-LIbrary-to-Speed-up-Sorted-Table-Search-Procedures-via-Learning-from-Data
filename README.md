# Benchmarking Software for Learned Binary and Interpolation Search

This repository provides a benchmarking platform to evaluate how Feed Forward Neural Networks can be effectively used as index data structures. That is, how well in terms of time and space, those Networks can solve the well known predecessor problem, i.e., searching for an element in a sorted table. In theory, those networks, with RELU activators,  are able to approximate any function [1] , including the one needed to solve predecessor search. Then, a simple binary search concludes the task.  In order to make clear the innovation of this approach, proposed by Kraska et al.[2], we consider an ATOMIC LEARNED INDEX. That is, we use only one prediction node in the Recursive Model Index intyroduced by Kraska et al. . Moreover, we also consider multivariate and univariate linear regression as alternative “predictors” to Neural Networks.

The scenario we have considered is in memory data and batch queries, which is a fundamental one, as outlined in [3].

We include:

1. Software implementing [Atomic Indexes](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Atomic%20Index), including Neural Network  and unvariate linear regression as predictors. The final stage is the branch-free binary search proposed in  [4].
1. [Binary Search Software](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Binary%20Search), adapted for our benchmarking, mostly adapted from [4] (GitHUb site loro)
1. [Neural Networks Training Software](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Atomic%20Index/NN_Train)
1. [Multi and Univariate Linear Regression Software]()

## Bibliography

[1] Sho Sonoda and Noboru Murata. Neural network with unbounded activation
functions is universal approximator. Applied and Computational
Harmonic Analysis , 43(2):233 { 268, 2017.

[2] Tim Kraska, Alex Beutel, Ed H Chi, Je_rey Dean, and Neoklis Polyzotis.
The case for learned index structures. In Proceedings of the 2018 Interna-
tional Conference on Management of Data , pages 489{504. ACM, 2018.


[3] Jun Rao and Kenneth A Ross. Cache conscious indexing for decisionsupport
in main memory. In Proceedings of the 25th International Confer-
ence on Very Large Data Bases , pages 78{89. Morgan Kaufmann Publishers
Inc., 1999.

[4] Paul-Virak Khuong and Pat Morin.  Array layouts for comparison-basedsearching.J. Exp. Algorithmics, 22:1.3:1–1.3:39, 2017.
