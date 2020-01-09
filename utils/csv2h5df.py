import argparse
import json
import pickle
import os
import h5py
import tensorflow as tf
import numpy as np
from numpy import genfromtxt



#Set Argument Parser for input information
parser = argparse.ArgumentParser(description='Train NN for Datastructure index')
parser.add_argument('-i', '--input', dest="inputFile", default="uni01",
                    help='Input file name')
parser.add_argument('-id', '--inputDir', dest="inputDir", default="./Resource",
help='Input file path')
parser.add_argument('-o', '--output', dest="outputPath", default="./Result",
                    help='Output file path and file name')

args = parser.parse_args()

my_data = genfromtxt(os.path.join(args.inputDir, args.inputFile+".sorted.csv"), delimiter=',', dtype=int)

with h5py.File(os.path.join(args.outputPath, args.inputFile+".sorted.mat"), "w") as f:
    f.create_dataset("M", data=[my_data])

binData=[]
for data in my_data:
    binData.append([int(x) for x in list('{0:064b}'.format(data))])

with h5py.File(os.path.join(args.outputPath, args.inputFile+"_bin.sorted.mat"), "w") as f:
    f.create_dataset("Sb", data=binData)

