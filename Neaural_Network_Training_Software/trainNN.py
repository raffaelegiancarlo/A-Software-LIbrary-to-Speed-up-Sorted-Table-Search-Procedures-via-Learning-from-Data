import argparse
import tensorflow as tf
import numpy as np
import h5py 
import json
import time
import os

def mean_error(set_dim):
    def mean_error_metric(y_true, y_pred):
        dim = tf.constant(set_dim, dtype=tf.float32)
        real = tf.math.scalar_mul(dim, y_true)
        pred = tf.math.scalar_mul(dim, y_pred)
        mean_err = tf.math.reduce_mean(tf.math.abs(tf.math.subtract(real,pred)))
        return mean_err

    return mean_error_metric
        
def max_error(set_dim):
    def max_error_metric(y_true, y_pred):
        dim = tf.constant(set_dim, dtype=tf.float32)
        #y_pred = tf.nn.relu(y_pred)
        real = tf.math.ceil(tf.math.scalar_mul(dim, y_true))
        pred = tf.math.ceil(tf.math.scalar_mul(dim, y_pred))
        pred = tf.nn.relu(pred)
        max_err = tf.math.reduce_max(tf.math.abs(tf.math.subtract(real,pred)))
        return max_err

    return max_error_metric


#Set Argument Parser for input information
parser = argparse.ArgumentParser(description='Train NN for Datastructure index')
parser.add_argument('-i', '--input', dest="inputFile", default="uni01_bin.sorted",
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
with h5py.File(args.inputDir+"/"+args.inputFile+".mat",'r') as f:
    data = f.get('Sb') 
    bin_data = np.array(data, dtype=np.bool) # For converting to numpy array
bin_data = np.transpose(bin_data)
bin_data = np.flip(bin_data,axis=1)
dim_set = len(bin_data)
print(dim_set)
print(bin_data)
        

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

#Callback for Training
stopping = tf.keras.callbacks.EarlyStopping(monitor=params["monitor"], patience=params["patience"], verbose=params["verbose"])
chkpoints = tf.keras.callbacks.ModelCheckpoint(filepath=args.outputPath+"/"+args.inputFile+"/"+params["chk-dir"]+"/"+nn_name+"/best_model.h5py", monitor=params["monitor"], verbose=params["verbose"], save_best_only=True, save_weights_only=True, mode='auto', period=1)
tensorboard = tf.keras.callbacks.TensorBoard(log_dir=args.outputPath+"/"+args.inputFile+"/"+params["log-dir"]+"/"+nn_name, histogram_freq=None, embeddings_freq=None)


sgd = tf.keras.optimizers.SGD(lr=params["learning-rate"], momentum=params["momentum"])
nn_model.compile(optimizer=sgd, loss=params["loss"], metrics=[max_error(dim_set), mean_error(dim_set)])
start = time.time()
nn_model.fit(x=bin_data, y=labels, batch_size=params["batch-size"], epochs=params["epochs"], 
            verbose=params["verbose"], callbacks=[stopping, chkpoints, tensorboard], 
            validation_split=params["val-split"], shuffle=True)
end = time.time()

elapsed = end - start

y_pred = nn_model.predict(x=bin_data)

epsilon = np.max(np.subtract(np.ceil(y_pred*dim_set), np.ceil(labels*dim_set)))

print(epsilon)

with open(args.outputPath+"/trainingTime"+nn_name+".csv", "a+") as fp:
    fp.write(args.inputFile+", "+str(elapsed)+", "+str(epsilon)+"\n")
