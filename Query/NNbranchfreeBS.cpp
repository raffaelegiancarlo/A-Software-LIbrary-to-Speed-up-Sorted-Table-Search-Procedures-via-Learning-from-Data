#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <string.h>

#include "../lib/search_algh.h"
#include "../lib/utils.h"
#include "../lib/NNutils.h"

#define N 100

int main(int argc, char * argv[]) {

    char *dataName, *queryName, *outputFn;

    std::cout << "Check Parameters..." << std::endl;

    //Print help
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        std::cout << "Help"<< std::endl;
        return 0;
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
            std::cerr << "Output filename missed...Aborting..." << std::endl;
            return 1;
        }
    }


    /*
    *
    * Creating Filename from params   
    * 
    */
    std::stringstream ss;
    std::string iFn, wFn, bFn, oFn, qFn, QFn, AFn;
    ss.str("");
    ss.clear();

    ss << dataName << "_bin.sorted.dat";
    iFn = ss.str();
    ss.str("");
    ss.clear();

    ss << dataName << "Query" << queryName << "_bin.dat";
    qFn = ss.str();
    ss.str("");
    ss.clear();


    ss << "weights_" << dataName << ".dat";
    wFn = ss.str();
    ss.str("");
    ss.clear();

    ss << "bias_" << dataName << ".dat";
    bFn = ss.str();
    ss.str("");
    ss.clear();

    ss << dataName << "Query" << queryName << ".csv";
    QFn = ss.str();
    ss.str("");
    ss.clear();

    ss << dataName << "sorted.csv";
    AFn = ss.str();
    ss.str("");
    ss.clear();

    /*
    *
    * Reading Files
    *
    */

    int m,q;
    int *A, *Q;

    m = readCSV(AFn, &A);
    q = readCSVQ(QFn, &Q);

    std::cout << "DIM A:" << m << std::endl;
    std::cout << "DIM Q:" << q << std::endl;
    
}