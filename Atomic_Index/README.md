# Atomic Index

## NN Predictor

### Requirements

NN Predictor Software has been made using Intel Math Kernel Library (MKL) downloadable from [https://software.intel.com/en-us/mkl/choose-download](https://software.intel.com/en-us/mkl/choose-download)

### Compile

In order to compile Atomic Index with NN Predictor Software, MKL params must be applied on g++ compiler using:

```Shell

g++ NNbranchfreeBS.cpp -o [outputFilename] -Wl,--start-group [MKL Library PATH]/libmkl_intel_lp64.a [MKL Library PATH]/libmkl_sequential.a [MKL Library PATH]/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl

```

[MKL Library PATH] must be replaced by the installation path of the MKL libraries on the execution environment 

### Run



## ULR Predictor