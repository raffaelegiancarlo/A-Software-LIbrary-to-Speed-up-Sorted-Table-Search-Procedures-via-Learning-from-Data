#include <stdio.h>
#include <time.h>
#include <ctime> 
#include <iostream>
#include <sstream>

/*MKL Libraries for Matrix Multiplication on Intel CPU*/
#include "/opt/intel/mkl/include/mkl.h"
#include "/opt/intel/mkl/include/mkl_vml_functions.h"

long readNNInput(std::string fn, double **data, int m){
    std::cout << "Reading Input"<< std::endl;
    FILE* fp; 
    long num = 0;
    fp = fopen( fn.c_str(), "r" );

    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "Opening File " << fn << " Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }

    fscanf(fp, "%ld\n", &num);
    *data = (double*)mkl_malloc(sizeof(double)*(num*m), 64);
    if(*data == NULL) { 
        std::stringstream errMsg;
        errMsg << "Allocation Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    for(int i = 0; i<num; i++){
        for(int j = 0; j<64;j++){
            fscanf(fp, "%1lf", &data[0][i*m+j]);
        }
        fgetc(fp);
    }
    fclose(fp);
    return num;
}

void readNNParams(std::string fn, double **data, int m){
    std::cout << "Reading W..."<< std::endl;
    FILE* fp; 
    fp = fopen( fn.c_str(), "r" );
    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "Opening File " << fn << " Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    *data = (double*)mkl_malloc(sizeof(double)*(m), 64);
    if(*data == NULL) { 
        std::stringstream errMsg;
        errMsg << "Allocation Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    for(int j = 0; j<m;j++){
        fscanf(fp, "%lf\n", &data[0][j]);
    }
    fclose(fp);
}

void readNNBias(std::string fn, double **data, int n, int m){
    std::cout << "Reading Bias..."<< std::endl;
    FILE* fp; 
    fp = fopen( fn.c_str(), "r" );
    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "Opening File " << fn << " Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    *data = (double*)mkl_malloc(sizeof(double)*(n*m), 64);
    if(*data == NULL) { 
        std::stringstream errMsg;
        errMsg << "Allocation Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    for(int j = 0; j<m;j++){
        fscanf(fp, "%lf\n", &data[0][j]);
        for(int i=0; i<n; i++){
            if(i != 0)
                data[0][i*m+j]=data[0][i*m+j-1];
        }
    }
    fclose(fp);
}

double* NNprediction(char* fn, int q, double *A, double* W, double *b, int m, int k, int n, double *timerMain){
    
    double  *C;
    int i, j;
    double alpha, beta;

    double* timer;
    std::clock_t c_start, c_end;

    std::cout << "Starting NN Prediction..." << std::endl;

    alpha = 1.0; beta = 0.0;
    C = (double *)mkl_calloc( m*n, sizeof( double ), 64 );
    if (C == NULL) {
      
      C = NULL;
      throw "Allocation Error: Not enough Memory...";
    }

    
    timer = (double*)calloc(3,sizeof(double));
    
    std::cout << "Permorming GEMM operation C=A*W..." << std::endl;
    c_start = std::clock();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, W, n, beta, C, n);
    c_end = std::clock();
    timer[0] = ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC;
    std::cout << "Computations completed..." << std::endl;
    

    std::cout << "Adding Bias..." << std::endl;
    c_start = std::clock();
    vdAdd(m, C, b, C );
    c_end = std::clock();
    timer[1] = ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC;
    std::cout << "Computations completed..." << std::endl;

    std::cout << "Leaky Relu Activation..." << std::endl;
    c_start = std::clock();
    for(i=0; i<m; i++){
        C[i] = C[i]>0 ? C[i] : C[i]*0.05;
    }
    c_end = std::clock();
    timer[2] = ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC;
    std::cout << "Computations completed..." << std::endl;

    double tot = 0;
    for(int t=0; t<3; t++){
        tot +=timer[t];
        printf("%1.10lf\n", timer[t]);
    }
    printf("Tot:%1.10lf\n", tot);
    *timerMain = tot/m;

    return C;
}