/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dube_
 *
 * Created on 07 August 2018, 7:46 PM
 */

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct instance{
    string sky, temp, humid, wind, water, forecast;
};

struct example{
    instance features;
    string outcome;
};

vector<example> examples;
instance hypothesis;

void read_file(string filename){
    ifstream input_file(filename);
    string line;
    while(std::getline(input_file, line)){
	istringstream ss(line);
	example temp_example;
	ss >> temp_example.features.sky >> temp_example.features.temp >> temp_example.features.humid >> temp_example.features.wind;
	ss >> temp_example.features.water >> temp_example.features.forecast >> temp_example.outcome;
	examples.push_back(temp_example);
    }
}   
/*
 * 
 */
int main(int argc, char** argv) {
    read_file("testing.txt");
    for( example e: examples){
	cout << e.features.sky <<" " <<e.outcome << endl;
    }
    return 0;
}

