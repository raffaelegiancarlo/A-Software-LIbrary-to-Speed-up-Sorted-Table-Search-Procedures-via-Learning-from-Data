#include <iostream>
#include<bits/stdc++.h> 

long readCSV(std::string fn, int **data){
    FILE* fp; 
    int i = 0;
    char ch;
    fp = fopen( fn.c_str(), "r" );
    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "File Error: Opening File Failed.";
        throw std::runtime_error(errMsg.str().c_str());
    }
    i++;
    while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
        i++;
    }
    std::cout << i << std::endl;
    *data = (int*)malloc(i*sizeof(int));
    if(*data == NULL) { 
        std::stringstream errMsg;
        errMsg << "Allocation Error: Not enough Memory...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    fseek(fp, 0L, SEEK_SET);
    for(i = 0; !feof(fp); i++){
        fscanf(fp, "%d\n", &data[0][i]);
    }

    return i;
}

long readCSVQ(std::string fn, int **data){
    std::cout << "Reading Queries..." << std::endl;
    FILE* fp; 
    int i = 0;

    fp = fopen( fn.c_str(), "r" );
    if(fp == NULL){ 
        std::stringstream errMsg;
        errMsg << "File Error: Opening File Failed.";
        throw std::runtime_error(errMsg.str().c_str());
    }
    *data = (int*)malloc(sizeof(int));
    if(*data == NULL) { 
        std::stringstream errMsg;
        errMsg << "Allocation Error: Not enough Memory...";
        throw std::runtime_error(errMsg.str().c_str());
    }
    for(i = 0; !feof(fp); i++){
        fscanf(fp, "%d\n", &data[0][i]); 
        *data = (int*)realloc(*data, (i+2)*sizeof(int));   
    }

    return i;
}

void print_matrix(const float *A, int nr_rows_A, int nr_cols_A) {

	for(int i = 0; i < nr_rows_A; ++i){
		for(int j = 0; j < nr_cols_A; ++j){
		   std::cout << A[j * nr_rows_A + i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_matrix_float(const float *A, int nr_rows_A, int nr_cols_A) {

	for(int i = 0; i < nr_rows_A; ++i){
		for(int j = 0; j < nr_cols_A; ++j){
		   std::cout << A[j * nr_rows_A + i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}
