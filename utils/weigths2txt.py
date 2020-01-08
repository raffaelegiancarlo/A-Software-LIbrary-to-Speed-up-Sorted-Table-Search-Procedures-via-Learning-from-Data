import pickle
import os
import h5py
import tensorflow as tf
import numpy as np
import json
import argparse

#Set Argument Parser for input information
parser = argparse.ArgumentParser(description='Train NN for Datastructure index')
parser.add_argument('-i', '--input', dest="inputFile", default="uni01",
                    help='Input file name')
parser.add_argument('-id', '--inputDir', dest="inputDir", default="./Resource",
help='Input file path')
parser.add_argument('-m', '--modelName', dest="modelName", default="NN0",
                    help='Name of json File of the NN structures')
parser.add_argument('-md', '--modelDir', dest="modelDir", default="./Neaural_Network_Training_Software/models/",
                    help='Model files Directory')
parser.add_argument('-o', '--output', dest="outputPath", default="./Result",
                    help='Output file path')
parser.add_argument('-p', '--params', dest="params", default="params.json",
                    help='Params file path with file name')

args = parser.parse_args()

json_file = open(os.path.join(args.modelDir, args.params), "r")
params_str = json_file.read()
json_file.close()
params = json.loads(params_str)
print(params)

#Load Dataset
bin_data=[]
with h5py.File(args.inputDir+"/"+args.inputFile+"_bin.sorted.mat",'r') as f:
    data = f.get('Sb') 
    bin_data = np.array(data, dtype=np.bool) # For converting to numpy array
bin_data = np.transpose(bin_data)
bin_data = np.flip(bin_data,axis=1)
dim_set = len(bin_data)
labels = np.linspace(1, len(bin_data), num=len(bin_data), dtype=np.float64)
labels = labels/len(bin_data)
labels = np.reshape(labels, (-1, 1))

json_file = open(os.path.join(args.modelDir,"json", args.modelName+".json"), "r")
loaded_model = json_file.read()
json_file.close()

nn_model = tf.keras.models.model_from_json(loaded_model)
nn_model.build()
nn_model.summary()
nn_name=args.modelName
#args.outputPath+"/"+params["chk-dir"]+"/"+nn_name+"/best_model.h5py"
nn_model.load_weights(os.path.join(args.inputDir,args.inputFile,params["chk-dir"],nn_name, "best_model.h5py"))

layer = nn_model.layers[0]
weights = nn_model.get_weights()[0] # list of numpy arrays
bias = nn_model.get_weights()[1] # list of numpy arrays
with open(os.path.join(args.outputPath, 'nn_w_'+args.inputFile+'.dat'),'w') as f:
    for weight in weights:
        print(weight[0])
        f.write(str(weight[0])+"\n")    

with open(os.path.join(args.outputPath, 'nn_bias_'+args.inputFile+'.dat'),'w') as f:
    f.write(str(bias[0])+"\n") 
