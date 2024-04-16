#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <math.h>

using namespace std;

#define INPUT_FILE "servere.in"
#define OUTPUT_FILE "servere.out"

#define EPSILON 0.01

int read_input(vector<int> &power, vector<int> &cost) {
    // Declare input file
    ifstream fin(INPUT_FILE);

    // Read the number of servers
    int num_of_servers;
    fin >> num_of_servers;

    // Resize vectors
    power.resize(num_of_servers);
    cost.resize(num_of_servers);

    // Read the vector of powers
    for (int i = 0; i < num_of_servers; i++) {
        fin >> power[i];
    }

    // Read the vector of powers
    for (int i = 0; i < num_of_servers; i++) {
        fin >> cost[i];
    }

    fin.close();
    return num_of_servers;
}

void print_output(double solution) {
    ofstream fout(OUTPUT_FILE);
    fout << fixed << setprecision(1) << solution << "\n";
    fout.close();
}

double solve(int num_of_servers, vector<int> &power, vector<int> &cost) {
    double solution = 0.0;

    // Do a binary search to find the actual solution
    double left = INT_MIN;
    //double right = *(max_element(power.begin(), power.end()));
    double right = INT_MAX;

    while (right - left > EPSILON) {
        double middle = (left + right) / 2;

        // Check if all absolute values are positive
        bool all_positive = true;
        for (int i = 0; i < num_of_servers; i++) {
            if (power[i] - middle < 0) {
                all_positive = false;
                break;
            }
        }

        // If not all absolut calues are posible, search in the left side
        if(!all_positive) {
            right = middle;
            continue;
        }

        // Verify if there is a valid solution for every server
        double interval_left = INT_MIN, interval_rigth = INT_MAX;
        for (int i = 0; i < num_of_servers; i++) {
            double diff = power[i] - middle;

            double current_interval_left = cost[i] - diff;
            double current_interval_right = cost[i] + diff; 
            
            interval_left = max(interval_left, current_interval_left);
            interval_rigth = min(interval_rigth, current_interval_right);
        }

        // If interval_left is greater than interval_right 
        // then the interval is not a valid one
        if (interval_left > interval_rigth) {
            right = middle;
        } else {
            left = middle;
        }
        
        solution = middle;
    }

    return solution;
}

int main(int argc, char *argv[])
{
    vector<int> power, cost;
    int num_of_servers = read_input(power, cost);

    double solution = solve(num_of_servers, power, cost);

    print_output(solution);
    return 0;
}