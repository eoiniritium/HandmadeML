//STANDARD HEADER FILES
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h>
#include <iomanip>
#include <ctime>

//CUSTOM HEADER FILES
#include "headerfiles/io.hpp"

using namespace std;

//GLOBAL VARIABLES

//

vector<vector<vector<double>>> generatemodel(int inputdimensions, int hiddenLayers, int hiddenLayerDimension, int outputLayerDimension, double rndmin, double rndmax){ //Generate model // Average node
    //Clear Vector: [vectorname].clear();

    vector<vector<vector<double>>> out; //Top layer
    vector<vector<double>> layer; //First layer nodes and weights
    vector<double> weights; //Node value and connection weights
    int connection = hiddenLayerDimension; //Number of connections per node
    //First layer
    weights.push_back(1); //Add constant placeholder
    for(int node = 0; node < connection; node++){ //Constant node connections
        weights.push_back(randomnum(rndmin, rndmax)); //Connections weights
    }
    layer.push_back(weights);
    weights.clear();


    for(int node = 0; node < inputdimensions; node++){ //Everynode in first layer
        weights.push_back(1); //Add node value to weights
        for(int weight = 0; weight < connection; weight++){ //Every connection from first layer
            weights.push_back(randomnum(rndmin, rndmax)); //Generate weight from -2 to 2
        }
        layer.push_back(weights); //Add node value and connection weights to first layer
        weights.clear(); //Clear node values and connection weights ready for next node and connections
    }
    out.push_back(layer); //Export the layer
    layer.clear(); //Ready for next layer

    //Hidden layer(s)
    for(int lay = 0; lay < hiddenLayers - 1; lay++){
        for(int node = 0; node < hiddenLayerDimension; node++){
            weights.push_back(1);
            for(int weight = 0; weight < hiddenLayerDimension; weight++){
                weights.push_back(randomnum(rndmin, rndmax));
            }
            layer.push_back(weights);
            weights.clear();
        }
    }
    out.push_back(layer);
    layer.clear();

    for(int node = 0; node < hiddenLayerDimension; node++){
        weights.push_back(1);
        for(int weight = 0; weight < outputLayerDimension; weight++){
            weights.push_back(randomnum(rndmin, rndmax));
        }
        layer.push_back(weights);
        weights.clear();
    }
    out.push_back(layer);
    layer.clear();

    // Output layer
    for(int node = 0; node < outputLayerDimension; node++){
        weights.push_back(1);
        layer.push_back(weights);
        weights.clear();
    }
    out.push_back(layer);

    //End of function
    return out;
}

vector<vector<vector<double>>> populateinputs(vector<vector<vector<double>>> model, vector<int> pxVal){
    vector<vector<vector<double>>> m = model;
    for(int i = 0; i < m[0].size(); i++){
        m[0][i][0] = pxVal[i];
    }

    return m;
}

vector<vector<vector<double>>> calculateoutput(vector<vector<vector<double>>> model){ //Average
    vector<vector<vector<double>>> out = model;
    for(int layer = 1; layer < out.size(); layer++){
        vector<vector<double>> layerdata = out[layer];
        vector<vector<double>> prevlayerdata = out[layer - 1];
        for(int node = 0; node < layerdata.size(); node++){
            double sum = 0;
            int count = 0;
            for(int prevln = 0; prevln < prevlayerdata.size(); prevln++){
                sum += prevlayerdata[prevln][0] * prevlayerdata[prevln][node + 1];
                count++;
            }
            out[layer][node][0] = sigmoid(sum / count);
        }
    }
    return out;
}

vector<vector<vector<double>>> mutate(vector<vector<vector<double>>> input, double threshold, double rndmax){
    vector<vector<vector<double>>> out;
    for(int layer = 0; layer < input.size(); layer++){
        for(int node = 0; node < input[layer].size(); node++){
            for(int weights = 1; weights < input[layer][node].size() - 1; weights++){
                double a = randomnum(0, threshold);
                if(a >= threshold){
                    double newnum = randomnum(0, rndmax);
                    out[layer][node][weights] = newnum;
                }
            }    
        }
    }
    return out;
}

int main(){
    
    vector<int> pixelvalue = read("images\\pixelvalues\\0.txt");
    vector<vector<vector<double>>> testmodel = generatemodel(pixelvalue.size(), 6, 6, 3, 0, 0.5);
    testmodel = populateinputs(testmodel, pixelvalue);
    testmodel = calculateoutput(testmodel);
    //printmodel(testmodel);
    cout << "Work 1" << endl;
    testmodel = mutate(testmodel, 0.6, 0.5);
    cout << "Work 2" << endl;
    printmodel(testmodel);
    cout << "Work 3" << endl;
    
    //EXIT
    return 0;
}