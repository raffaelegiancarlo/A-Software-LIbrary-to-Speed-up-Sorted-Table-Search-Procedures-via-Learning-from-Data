# Binary Search

## Genaral 
This directory contains two cpp files. The first (branchfreeBS.cpp) implements branch-free binary search. The second (eytzBS.cpp) Eytzeinger Layout Binary Search. Both programs are stand-alone. 
## Requirements and Use

### Branch-free Binary Search

#### Requirements

In order to compile cpp files a gcc 6 or above is needed

#### Compile

To compile use:

```Shell

g++ branchfreeBS.cpp -o [outputFilename]

```

[outputFilename] must be replaced by the name of the file that will be executed

#### Run

To run Branchfree Binary Search use:

```Shell

./[outputFilename] -p [Path] -d [Dataset] -q [Query] -o [Output] -n [iteration]

```

Argument:
* -p Path of Resource file (e.g.: "./Resource/")  
* -d Name of dataset file (e.g.: "uni01")  
* -q Name of query (e.g.: 10% query name is "10")  
* -o Name of output csv file with time results (e.g.: "branchfreeBSTime.csv")
* -n Number of times to repeat the experiment (Final time is the mean of the times of each iteration) 

### Eytzeinger Layout Binary Search

#### Requirements

In order to compile cpp files a gcc 6 or above is needed

#### Compile

To compile use:

```Shell

g++ eytzBS.cpp -o [outputFilename]

```

[outputFilename] must be replaced by the name of the file that will be executed

#### Run

To run Eitzeinger Binary Search use:

```Shell

./[outputFilename] -p [Path] -d [Dataset] -q [Query] -o [Output] -n [iteration]

```

Argument:
* -p Path of Resource file (e.g.: "./Resource/")  
* -d Name of dataset file (e.g.: "uni01")  
* -q Name of query (e.g.: 10% query name is "10")  
* -o Name of output csv file with time results (e.g.: "eytzBSTime.csv")
* -n Number of times to repeat the experiment (Final time is the mean of the times of each iteration) 
