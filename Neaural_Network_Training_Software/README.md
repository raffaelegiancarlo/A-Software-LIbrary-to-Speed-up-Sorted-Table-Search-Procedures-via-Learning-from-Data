# Neural Network Training Software

## General Structure
This directory contains one python files. This script (trainNN.py) implements NN training using Keras API with Tensorflow Backend.

## Requirements and Use

### NN Training

#### Requirements

NN Training Software need python interpreter 3.6 or above and use the following python packages:

* argparse
* tensorflow or tensorflow-gpu (If a NVIDIA card was provided)
* numpy
* h5py 
* json
* time

This script use a json file to configure training options. This file have the following structure:

```JSON

{
    "loss":"mse", //Name of the loss Function
    "learning-rate": 0.1, //Learning Rate used during training
    "momentum":0.9, //Momentum of the SDG algorithm
    "epochs": 20000, //Max Number of Epochs
    "batch-size":64, //Size of the batch during training
    "verbose":1, //1 if you want print info during execution, 0 otherwise
    "val-split":0.3, //Percentage of Training Set used as validation set
    "monitor": "loss", //Metric used to evaluate training
    "patience": 5, //Number of iteration before the early stopping 
    "chk-dir": "ckpt_models", //Dir in which save models
    "log-dir": "logs" //Dir in which save logs file
}

```

#### Run

To run NN Training Software use:

```Shell

./trainNN.py -p [Path] -d [Dataset] -q [Query] -o [Output] -e [epsilon] -n [iteration]

```

Argument:
* -i Input File Name (e.g.: uni01.sorted.mat)
* -id Input File Path (e.g.: ./Resources)
* -m Model Name (e.g.: NN0)
* -o Output File Path and name (e.g.: ./Results)
* -p Training Params file path with file name (e.g.: ./models/params.json)

