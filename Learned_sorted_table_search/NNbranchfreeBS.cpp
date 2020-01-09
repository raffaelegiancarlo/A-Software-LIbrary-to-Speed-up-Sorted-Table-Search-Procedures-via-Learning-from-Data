#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <vector>

#include "../lib/search_algh.h"
#include "../lib/utils.h"
#include "../lib/NNutils.h"


int main(int argc, char * argv[]) {

    char *dataName, *queryName, *outputFn, *nIter, *path;
    int epsilon;

    std::cout << "Check Parameters..." << std::endl;

    //Print help
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        std::cout << "Help"<< std::endl;
        return 0;
    }

    //Check Dataset name parameter
    if(!cmdOptionExists(argv, argv+argc, "-p"))
    {
        path = NULL;
    }else{
        path = getCmdOption(argv, argv + argc, "-p");
        if(!path || !strncmp ( path, "-", 1 )){
            path = NULL;
        }
    }


    //Check Dataset name parameter
    if(!cmdOptionExists(argv, argv+argc, "-d"))
    {
        std::cerr << "Dataset name missed...Aborting..." << std::endl;
        return 1;
    }else{
        dataName = getCmdOption(argv, argv + argc, "-d");
        if(!dataName || !strncmp ( dataName, "-", 1 )){
            std::cerr << "Dataset name missed...Aborting..." << std::endl;
            return 1;
        }
    }

    //Check Query name parameter
    if(!cmdOptionExists(argv, argv+argc, "-q"))
    {
        std::cerr << "Query name missed...Aborting..." << std::endl;
        return 1;
    }else{
        queryName = getCmdOption(argv, argv + argc, "-q");
        if(!queryName || !strncmp ( queryName, "-", 1 )){
            std::cerr << "Query name missed...Aborting..." << std::endl;
            return 1;
        }
    }

    //Check Output filename parameter
    if(!cmdOptionExists(argv, argv+argc, "-o"))
    {
        std::cerr << "Output filename missed...Aborting..." << std::endl;
        return 1;
    }else{
        outputFn = getCmdOption(argv, argv + argc, "-o");
        if(!outputFn || !strncmp ( outputFn, "-", 1 )){
            std::cerr << "Output file path missed...Aborting..." << std::endl;
            return 1;
        }
    }

    //Check Number of iterations parameter
    if(!cmdOptionExists(argv, argv+argc, "-n"))
    {
        std::cerr << "Iterations Number Missed...Aborting..." << std::endl;
        return 1;
    }else{
        nIter = getCmdOption(argv, argv + argc, "-n");
        if(!nIter || !strncmp ( nIter, "-", 1 )){
            std::cerr << "Iterations Number Missed...Aborting..." << std::endl;
            return 1;
        }
    }

    //Check Number of iterations parameter
    if(!cmdOptionExists(argv, argv+argc, "-e"))
    {
        std::cerr << "Epsilon Missed...Aborting..." << std::endl;
        return 1;
    }else{
        char * aus;
        aus = getCmdOption(argv, argv + argc, "-e");
        if(!aus || !strncmp ( aus, "-", 1 )){
            std::cerr << "Epsilon Missed...Aborting..." << std::endl;
            return 1;
        }else{
            epsilon = atoi(aus);
        }
    }


    /*
    *
    * Creating Filename from params   
    * 
    */
    std::stringstream ss;
    std::string iFn, wFn, bFn, oFn, QFn, AFn;
    ss.str("");
    ss.clear();

    if(path == NULL){
        ss << dataName << "Query" << queryName << ".dat";
        iFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << dataName << "Query" << queryName << ".dat";
        iFn = ss.str();
        ss.str("");
        ss.clear();
    }

    if(path == NULL){
        ss << "nn_w_" << dataName << ".dat";
        wFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << "nn_w_" << dataName << ".dat";
        wFn = ss.str();
        ss.str("");
        ss.clear();
    }
    if(path == NULL){
        ss << "nn_bias_" << dataName << ".dat";
        bFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << "nn_bias_" << dataName << ".dat";
        bFn = ss.str();
        ss.str("");
        ss.clear();
    }

    if(path == NULL){
        ss << dataName << "Query" << queryName << ".csv";
        QFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << dataName << "Query" << queryName << ".csv";
        QFn = ss.str();
        ss.str("");
        ss.clear();
    }
    if(path == NULL){
        ss << dataName << ".csv";
        AFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << dataName << ".csv";
        AFn = ss.str();
        ss.str("");
        ss.clear();
    }

    /*
    *
    * Reading Files
    *
    */

    int m,q;
    int *A, *Q;
    double *W, *b, *I, *O;
    FILE * out;

    double *timer;
    double timerAcc = 0, devStd=0;
    int res;

    std::cout << AFn << std::endl;

    std::cout << "Reading Input data" << std::endl;
    m = readCSV(AFn, &A);

    std::cout << "Reading Query data" << std::endl;
    q = readCSV(QFn, &Q);

    std::cout << "DIM A:" << m << std::endl;
    std::cout << "DIM Q:" << q << std::endl;

    readNNInput(iFn, &I, q);
    readNNParams(wFn, &W, 64);
    readNNBias(bFn, &b, m, 1);

    out = fopen(outputFn, "r");
    if(out == NULL){
        out = fopen(outputFn, "w+");
        fprintf(out, "File, Query, NN + BS Mean, NN + BS DevStd\n");
    }else{
        fclose(out);
        out = fopen(outputFn, "a+");
    }
    int n = atoi(nIter);
    timer = (double*)calloc(n, sizeof(double));
    std::cout << nIter << std::endl;
    for( int j = 0; j < n; j++){
        O = NNprediction(dataName, atoi(queryName), I, W, b, q, 64, 1, &timer[j]);

        std::cout << "Performing Branch Free Binary Search" << std::endl;
        std::clock_t c_start = std::clock();
        for(int i = 0; i<q; i++){
            res = branchfreeBS(A, Q[i], (int)O[i]-epsilon <= 0 ? 0 : (int)O[i]-epsilon, (int)O[i]+epsilon >= m-1 ? m-1 : (int)O[i]+epsilon);
        }
        std::clock_t c_end = std::clock();
        timer[j] += ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC/q;
        timerAcc += timer[j];
        
    }

    for(int i = 0; i<n; i++){
        
        devStd += (timer[i] - timerAcc/n)*(timer[i] - timerAcc/n);
    }


    fprintf(out, "%s, %s, %.15lf, %.15lf\n", dataName, queryName, timerAcc/n, devStd/n>0 ? sqrt(devStd/n) : 0);

    return 0;    
}