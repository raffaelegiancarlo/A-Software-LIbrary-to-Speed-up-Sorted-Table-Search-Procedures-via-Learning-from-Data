import numpy as np 
import h5py 
from sklearn.linear_model import LinearRegression
import json
from time import clock
import os
import argparse

#Set Argument Parser for input information
parser = argparse.ArgumentParser(description='Train NN for Datastructure index')
parser.add_argument('-i', '--input', dest="inputFile", default="uni01.sorted",
                    help='Input file name')
parser.add_argument('-id', '--inputDir', dest="inputDir", default="./Resource",
help='Input file path')
parser.add_argument('-o', '--output', dest="outputFile", default="multivariate_linear_regression.json",
                    help='Output file name')
parser.add_argument('-od', '--outputDir', dest="outputDir", default="./",
                    help='Output file path')


args = parser.parse_args()


if(os.path.exists(os.path.join(args.outputDir, args.outputFile))):
    with open(os.path.join(args.outputDir, args.outputFile)) as json_file:
        resJson = json.load(json_file)
else:
    resJson = {}

resJson[args.inputFile] = {}

print("Reading Input File...")
with h5py.File(os.path.join(args.inputDir, args.inputFile+".mat"),'r') as f:
    data = f.get('M')
    bin_data = np.array(data, dtype=np.int64)
bin_data = np.concatenate((bin_data, np.log2(bin_data), np.square(bin_data)))
bin_data = np.transpose(bin_data)
dim_set = len(bin_data)
bin_data = np.concatenate((bin_data, np.ones((dim_set,1))), axis=1)

labels_index = np.linspace(1, len(bin_data), num=len(bin_data), dtype=np.float64)
labels = labels_index/len(bin_data)
labels = np.reshape(labels, (-1, 1))

p = np.random.permutation(dim_set)

bin_data = bin_data[p]
labels_index = labels_index[p]
labels = labels[p]
print("Performing Multivariate Linear Regression...")
start = clock()
w = np.linalg.inv(np.transpose(bin_data).dot(bin_data)).dot(np.transpose(bin_data)).dot(labels)
end = clock()

pred = np.transpose(w).dot(np.transpose(bin_data))
l_pred = np.floor(pred * len(bin_data)) 
max_err = np.amax(np.abs(labels_index - l_pred)[0])

resJson[args.inputFile]["Overhead"] = max_err/len(bin_data)*100
resJson[args.inputFile]["Space"] = w.nbytes/bin_data.nbytes   
resJson[args.inputFile]["epsilon"] = max_err
resJson[args.inputFile]["time"] = float(end - start)
resJson[args.inputFile]["meanTime"] = resJson[args.inputFile]["time"]/len(bin_data)



with open(os.path.join(args.outputDir, "mlr_w_"+args.inputFile+".dat"),'w') as f:
    for weight in w:
        print(weight[0])
        f.write(str(weight[0])+"\n")

with open(os.path.join(args.outputDir, args.outputFile), 'w') as outfile:
    json.dump(resJson, outfile)