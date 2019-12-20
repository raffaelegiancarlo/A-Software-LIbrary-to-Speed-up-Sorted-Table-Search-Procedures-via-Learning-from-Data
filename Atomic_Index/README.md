# Atomic Index

## NN Predictor

### Requirements

NN Predictor Software has been made using Intel Math Kernel Library (MKL) downloadable from [https://software.intel.com/en-us/mkl/choose-download](https://software.intel.com/en-us/mkl/choose-download)

### Compile

In order to compile Atomic Index with NN Predictor Software, MKL params must be applied on g++ compiler using:

```Shell

g++ NNbranchfreeBS.cpp -o [outputFilename] -Wl,--start-group [MKL Library PATH]/libmkl_intel_lp64.a [MKL Library PATH]/libmkl_sequential.a [MKL Library PATH]/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl

```

[MKL Library PATH] must be replaced by the installation absolute path of the MKL libraries on the execution environment 

[outputFilename] must be replaced by the name of the file that will be executed

### Run

To run NN Predictor use:

```Shell

./[outputFilename] -p [Path] -d [Dataset] -q [Query] -o [Output] -e [epsilon] -n [iteration]

Argument:
- -p Path of Resource file (e.g.: "./Resource/")  
- -d Name of dataset file (e.g.: "uni01")  
- -q Name of query (e.g.: 10% query name is "10")  
- -o Name of output csv file with time results (e.g.: "NNPredictorTime.csv")
- -e Maximum error made by NN Predictor
- -n Number of times to repeat the experiment (Final time is the mean of the times of each iteration) 

```


## ULR Predictor