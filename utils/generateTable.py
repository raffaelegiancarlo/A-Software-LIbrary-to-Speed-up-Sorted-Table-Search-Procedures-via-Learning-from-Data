import argparse
import json
import pickle
import os
import random
import numpy as np


#Set Argument Parser for input information
parser = argparse.ArgumentParser(description='Generating Table Software')
parser.add_argument('-n', '--number', dest="nElem", default=128,
                    help='Number of elements in Table')
parser.add_argument('-st', '--step', dest="step", default=2,
                    help='Incremental step')
parser.add_argument('-od', '--outputDir', dest="outputPath", default="./Result",
                    help='Output file path ')
parser.add_argument('-o', '--output', dest="outputFile", default="table128",
                    help='Output file name')

args = parser.parse_args()
l = np.arange(1,2*args.nElem+1, 2)

#l = random.sample(range(args.start, args.end,args.step), args.nElem)
#l.sort()


with open(os.path.join(args.outputPath, args.outputFile+'.sorted.csv'),'w') as f:
   for sample in l:
       f.write(str(sample)+"\n") 