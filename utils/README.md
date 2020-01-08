# Utility
This directory contains two python files. The first (weights2txt.py) implements a script that extract weigths from trained model in order to use its on CUDA C++ software. The second (csv2h5df.py) implements a script that create h5df file from csv dataset.

## Requirements and Use

### Read and save Weigths from NN Models

#### Requirements

This Software need python interpreter 3.6 or above and use the following python packages:

* argparse
* tensorflow or tensorflow-gpu (If a NVIDIA card was provided)
* numpy
* h5py 
* json
* pickle
* os

#### Run

To run this Software use:

```Shell

./weights2txt.py -i [Input File] -id [Inputh Path] -m [Model] -md [Model Path] -o [Output File Path] -p [Params File Path]

```

Argument:
* -i Input File Name (e.g.: uni01)
* -id Input File Path (e.g.: ./Resources)
* -m Model Name (e.g.: NN0)
* -md Model Path (e.g.: ./model/json)
* -o Output File Path and name (e.g.: ./Results)
* -p Training Params file path with file name (e.g.: ./models/params.json)

### Create h5df file from CSV

#### Requirements

This Software need python interpreter 3.6 or above and use the following python packages:

* argparse
* tensorflow or tensorflow-gpu (If a NVIDIA card was provided)
* numpy
* h5py 
* json
* pickle
* os

#### Run

To run this Software use:

```Shell

./csv2h5df.py -i [Input File] -id [Inputh Path] -o [Output File Path]

```

Argument:
* -i Input File Name (e.g.: uni01)
* -id Input File Path (e.g.: ./Resources)
* -o Output File Path and name (e.g.: ./Results)
