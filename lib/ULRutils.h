void readRegrParams(std::string fn, double **wdata, double **bdata){
    std::cout << "Reading Weigths..."<< std::endl;
    FILE* fp; 
    //long num = 0;
    fp = fopen( fn.c_str(), "r" );
    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "Opening File " << fn << " Failed...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    *wdata = (double*)malloc(sizeof(double));
    *bdata = (double*)malloc(sizeof(double));

    if (wdata == NULL || bdata == NULL) {  

        std::stringstream errMsg;
        errMsg << "Allocation Error: Not enough Memory...";
        throw std::runtime_error(errMsg.str().c_str());
    }

    fscanf(fp, "%lf\n%lf\n", &wdata[0][0], &bdata[0][0]);  
    printf("%.16lf\n", wdata[0][0]);
    printf("%.16lf\n", bdata[0][0]);
    //printf("\n");

    fclose(fp);
}

double * ULRprediction(char* fn, int *A, double* W, double* b, int m, int n, double *timerMain){
    
    double  *C;
    int i, j;
    double alpha, beta;

    double* timer;
    std::clock_t c_start, c_end;

    std::cout << "Starting ULR Prediction..." << std::endl;

    alpha = 1.0; beta = 0.0;
    C = (double *)calloc( m*n, sizeof( double ));
    if (C == NULL) {  
        C = NULL;
        std::stringstream errMsg;
        errMsg << "Allocation Error: Not enough Memory...";
        throw std::runtime_error(errMsg.str().c_str());
    }

    std::cout << "Computing Weigth Multiplication..." << std::endl;

    timer = (double*)calloc(2,sizeof(double));

    if (timer == NULL) {  
        std::stringstream errMsg;
        errMsg << "Allocation Error: Not enough Memory...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    
    c_start = std::clock();
    for(int i = 0; i<m; i++){
        C[i] = A[i]*W[0];
    }
    c_end = std::clock();
    
    timer[0] = ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC;
    //mult_acc += timer[0];

    std::cout << "Computing Bias Sum..." << std::endl;
    c_start = std::clock();
    for(int i = 0; i<m; i++){
        C[i] = C[i]+b[0];
    }
    c_end = std::clock();
    timer[1] = ((double)c_end-(double)c_start) / (double)CLOCKS_PER_SEC;
    //bias_acc += timer[1];

    double tot = 0;
    for(int t=0; t<2; t++){
        tot +=timer[t];
    }
    *timerMain = tot/m;

    return C;
}