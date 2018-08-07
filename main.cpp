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
    print(){
	cout <<"<" << sky << " " << temp << " " << humid << " " << wind << " " << water << " " <<forecast <<">" << endl;
    }
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
    hypothesis.sky = hypothesis.temp = hypothesis.humid = hypothesis.wind = hypothesis.water = hypothesis.forecast = "\0";
}   

void compute_and_evaluate(string& example_s1, string& hypothesis_s1){
    if( hypothesis_s1 != example_s1){
	if(hypothesis_s1 != "?"){
	    hypothesis_s1 = "?";
	}
    }
}

void evaluate_example(example& examp){
    if(hypothesis.sky == "\0"){
	hypothesis = examp.features;
    }else{
	compute_and_evaluate(examp.features.sky, hypothesis.sky);
	compute_and_evaluate(examp.features.temp, hypothesis.temp);
	compute_and_evaluate(examp.features.humid, hypothesis.humid);
	compute_and_evaluate(examp.features.wind, hypothesis.wind);
	compute_and_evaluate(examp.features.water, hypothesis.water);
	compute_and_evaluate(examp.features.forecast, hypothesis.forecast);
    }
}

void train(){
    for (example e: examples){
	if(e.outcome == "Yes" || e.outcome == "yes" ||e.outcome == "YES"){
	    evaluate_example(e);
	}
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
    read_file("testing.txt");
    train();
    hypothesis.print();
    return 0;
}

