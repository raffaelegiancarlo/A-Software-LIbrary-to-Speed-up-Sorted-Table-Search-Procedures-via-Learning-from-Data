# Multi and Univariate Linear Regression Software

## General Structure
This directory contains two python files. The first (uniLinRegr.py) implements univariate linear regression. The second (multiLinRegr.py) implements multivariate linear regression. All the software is stand alone.

## Requirements and Use

### Univariate Linear Regression

#### Requirements

Univariate Linear Regression Software need python interpreter 3.6 or above and use the following python packages:

* argparse
* numpy
* h5py 
* json
* time
* scikit-learn

#### Run

To run Univariate Linear Regression Software use:

```Shell

./uniLinRegr.py -i [Input File] -id [Inputh Path] -o [Output File] -od [Output Path]

```

Argument:
* -i Input File Name (e.g.: uni01)
* -id Input File Path (e.g.: ./Resources)
* -o Output File name (e.g.: univariate_linear_regression.json)
* -od Output File Path (e.g.: ./Results)

### Multivariate Linear Regression

#### Requirements

Multivariate Linear Regression Software need python interpreter 3.6 or above and use the following python packages:

* argparse
* numpy
* h5py 
* json
* time
* scikit-learn

#### Run

To run Multivariate Linear Regression Software use:

```Shell

./multiLinRegr.py -i [Input File] -id [Inputh Path] -o [Output File] -od [Output Path]

```

Argument:
* -i Input File Name (e.g.: uni01)
* -id Input File Path (e.g.: ./Resources)
* -o Output File name (e.g.: multivariate_linear_regression.json)
* -od Output File Path (e.g.: ./Results)





