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

ofstream result_file("result.dat");

struct instance {
    string sky, temp, humid, wind, water, forecast;

    print() {
	result_file << "{" << sky << " " << temp << " " << humid << " " << wind << " " << water << " " << forecast << "}" << endl;
    }
};

struct example {
    instance features;
    string outcome;
};

int counter =1;
vector<example> examples;
instance hypothesis;

instance target_concept = {"Sunny", "Warm", "?", "?", "?", "?"};

void read_file(string filename) {
    ifstream input_file(filename);
    string line;
    while (std::getline(input_file, line)) {
	istringstream ss(line);
	example temp_example;
	ss >> temp_example.features.sky >> temp_example.features.temp >> temp_example.features.humid >> temp_example.features.wind;
	ss >> temp_example.features.water >> temp_example.features.forecast >> temp_example.outcome;
	examples.push_back(temp_example);
    }
    input_file.close();
    hypothesis.sky = hypothesis.temp = hypothesis.humid = hypothesis.wind = hypothesis.water = hypothesis.forecast = "0";
}

void compute_and_evaluate(string& example_s1, string& hypothesis_s1) {
    if (hypothesis_s1 != example_s1) {
	if (hypothesis_s1 != "?") {
	    hypothesis_s1 = "?";
	}
    }
}

void evaluate_example(example& examp) {
    ++counter;
    if (hypothesis.sky == "0") {
	hypothesis = examp.features;
    } else {
	compute_and_evaluate(examp.features.sky, hypothesis.sky);
	compute_and_evaluate(examp.features.temp, hypothesis.temp);
	compute_and_evaluate(examp.features.humid, hypothesis.humid);
	compute_and_evaluate(examp.features.wind, hypothesis.wind);
	compute_and_evaluate(examp.features.water, hypothesis.water);
	compute_and_evaluate(examp.features.forecast, hypothesis.forecast);
    }
}

void train() {
    int counter = 0;
    result_file << "h <- ";
    hypothesis.print();
    for (example e : examples) {
	if (e.outcome == "Yes" || e.outcome == "yes" || e.outcome == "YES") {
	    evaluate_example(e);
	    result_file << "h <- ";
	    hypothesis.print();
	}
    }
}

bool test_string(string& example_s1, string& hypothesis_s1) {
    if (hypothesis_s1 != "?") {
	return ( example_s1 == hypothesis_s1);
    }
    return true;
}

void test(instance inst) {
    bool output = test_string(inst.sky, hypothesis.sky) && test_string(inst.humid, hypothesis.humid)
	    && test_string(inst.temp, hypothesis.temp) && test_string(inst.wind, hypothesis.wind) && test_string(inst.water, hypothesis.water)
	    && test_string(inst.forecast, hypothesis.forecast);
    result_file << ((output) ? "Yes" : "No");
}

/*
 * 
 */
int main(int argc, char** argv) {
    read_file("testing.txt");
    train();
    result_file << "\n******************************************" << endl;
    result_file << "Testing with: ";
    examples[0].features.print(); result_file << endl;
    test(examples[0].features);
    result_file << "\n******************************************" << endl;
    result_file << "We need: " << counter << " examples to get the target hypothesis that means " << (counter - 4) << " at minimum need to be added" <<endl;
    result_file.close();
    return 0;
}

