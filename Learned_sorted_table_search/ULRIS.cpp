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
#include "../lib/ULRutils.h"



int main(int argc, char * argv[]) {

    char *dataName, *queryName, *outputFn, *nIter, *path;
    int epsilon;
    int align;

    std::cout << "Check Parameters..." << std::endl;

    //Print help
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        std::cout << "Help"<< std::endl;
        return 0;
    }

    //Check Path parameter
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

    //Check Epsilon parameter
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

    //Check align memory params
    if(!cmdOptionExists(argv, argv+argc, "-a"))
    {
        align=0;
    }else{
        align=1;
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
        ss << dataName << "Query" << queryName << "_bin.dat";
        iFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << dataName << "Query" << queryName << "_bin.dat";
        iFn = ss.str();
        ss.str("");
        ss.clear();
    }

    if(path == NULL){
        ss << "ulr_w_" << dataName << ".dat";
        wFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << "ulr_w_" << dataName << ".dat";
        wFn = ss.str();
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
        ss << dataName << ".sorted.csv";
        AFn = ss.str();
        ss.str("");
        ss.clear();
    }else{
        ss << path << dataName << ".sorted.csv";
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
    double *W, *b, *O;
    FILE * out;

    double *timer;
    double timerAcc = 0, devStd=0;
    int res;

    std::cout << AFn << std::endl;

    std::cout << "Reading Input data" << std::endl;
    if(align)
        m = readCSValign(AFn, &A);
    else
        m = readCSV(AFn, &A);
    std::cout << "Reading Query data" << std::endl;
    if(align)
        q = readCSValign(QFn, &Q);
    else
        q = readCSV(QFn, &Q);

    std::cout << "DIM A:" << m << std::endl;
    std::cout << "DIM Q:" << q << std::endl;

    readRegrParams(wFn, &W, &b);

    out = fopen(outputFn, "r");
    if(out == NULL){
        out = fopen(outputFn, "w+");
        fprintf(out, "File, Query, ULR + BS Mean, ULR + BS DevStd\n");
    }else{
        fclose(out);
        out = fopen(outputFn, "a+");
    }

    int n = atoi(nIter);
    timer = (double*)calloc(n, sizeof(double));

    std::cout << nIter << std::endl;
    for( int j = 0; j < n; j++){
        O = ULRprediction(dataName, A, W, b, q, 1, &timer[j]);
        int predIdx=0;
        std::cout << "Performing Branch Free Binary Search" << std::endl;
        std::clock_t c_start = std::clock();
        for(int i = 0; i<q; i++){
            predIdx = O[i]*m;
            res = interpFind(A, Q[i], predIdx-epsilon <= 0 ? 0 : predIdx-epsilon, predIdx+epsilon >= m-1 ? m-1 : predIdx+epsilon);
        }
        std::clock_t c_end = std::clock();
        timer[j] += ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC/q;
        timerAcc += timer[j];
        free(O);
    }

    for(int i = 0; i<n; i++){
        
        devStd += (timer[i] - timerAcc/n)*(timer[i] - timerAcc/n);
    }


    fprintf(out, "%s, %s, %.15lf, %.15lf\n", dataName, queryName, timerAcc/n, devStd/n>0 ? sqrt(devStd/n) : 0);

    return 0;    
}