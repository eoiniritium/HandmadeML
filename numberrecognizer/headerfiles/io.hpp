#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <ctime>
#include <cstdlib>

std::vector<std::string> splitstring(std::string input, char delim){ // Splits string into vector using a delimiter
    std::stringstream ss(input);
    std::string item;
    std::vector<std::string> splittedstrings;
    while(std::getline(ss, item, delim)){
        splittedstrings.push_back(item);
    }
    return splittedstrings;
}

std::vector<int> read(std::string input){ // Reads int for model
    std::fstream file;
    std::string out;
    
    file.open(input);
    file >> out;
    file.close();

    std::vector<int> outlist;
    std::vector<std::string> stringNums = splitstring(out, ',');
    for(int i = 0; i < stringNums.size(); i++) {
        outlist.push_back(std::stoi(stringNums[i]));
    }

    return outlist;
}

std::string sread(std::string dir){ //Read string
    std::string out;
    std::fstream file;

    file.open(dir);
    file >> out;
    file.close();

    return out;
}

void write(std::string dir, std::string towrite){ //Write string
    std::ofstream file;
    file.open(dir);

    file << towrite;
    file.close();
}

double randomnum(double minimum, double maximum){
    return ((float(rand()) / float(RAND_MAX)) * (maximum - minimum)) + minimum;
}

void printmodel(std::vector<std::vector<std::vector<double>>> input){
    for(int top = 0; top < input.size(); top++){
        std::vector<std::vector<double>> middle = input[top];
        for(int middlec = 0; middlec < middle.size(); middlec++){
            std::vector<double> valueWeights = middle[middlec];
            std::cout << valueWeights[0] << " ";
            for(int lower = 1; lower < valueWeights.size(); lower++){
                std::cout << valueWeights[lower] << ", ";
            }
            std::cout << std::endl; //Next node
        }
        std::cout << "\n" << std::endl; //Next layer
    }
}

double sigmoid(double x){
    return 1 / (1 + exp(-x));
}