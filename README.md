# Benchmarking Software for Learned Binary and Interpolation Search

This repository provides a benchmarking platform to evaluate how  Machine Learning can be effectively used to improve the performance of classic index data structures. Such an approach, referred to as Learned Data Structures, has been recently introduced by Kraska et al.[2]. In their framework,  the learning part is made of a directed graph of models that refine the interval in a sorted table where a query element could be. Then, the final stage is a binary search. The models are either Feed Forward Neural Networks, with RELU activators or multi/univariate linear regression. In order to enuclate  the methodological innovations of this proposal from the engineering aspects of it, we focus on a very basic scenario. One model for a single prediction and then a routine to search in a sorted table to finish the job. The table is kept in main memory. With the use of the mentioned Neural Networks, this "atomic" index is as general as the one proposed by Kraska et al., since  those networks, with RELU activators,  are able to approximate any function [1]. Moreover, our approach can be simply cast as the study of learned search in a sorted table. It is a fundamental one, as outlined in [3,4].

We include in this repository:

1. The directory [Atomic Indexes](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Atomic_Index), contains our implementtions of learned binary and interpolation search.
1. The directory [Binary Search Software](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Binary_Search) contains binary search implementations, mostly taken from [4] (http://cglab.ca/~morin/misc/arraylayout-v2/), and adapted for our purposes. 
1. The directory [Interpolation Search](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/Interpolation_Search) contains a standard textbook implementation of interpolation search, adapted for our purposes. 
1. The directory [Neural Networks Training Software](https://github.com/raffaelegiancarlo/BENCHMARKING-SOFTWARE-FOR-LEARNED-BINARY-AND-INTERPOLATION-SEARCH/tree/master/NN_Train) contains  software for Feed-Forward, RELU, training
1. The directory [Multi and Univariate Linear Regression Software] contains  software implementing  textbook versions of multi/univariate linear regression.

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
