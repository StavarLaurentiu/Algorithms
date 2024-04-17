#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <numeric>

using namespace std;

#define INPUT_FILE "compresie.in"
#define OUTPUT_FILE "compresie.out"

void read_input(vector<int> &a, vector<int> &b) {
    ifstream fin(INPUT_FILE);

    // Read the first array -- Resize the vector and read the elements
    int n;
    fin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    // Read the second array -- Resize the vector and read the elements
    int m = 0;
    fin >> m;
    b.resize(m);
    for (int i = 0; i < m; i++) {
        fin >> b[i];
    }

    fin.close();
}

void print_output(int result) {
    ofstream fout(OUTPUT_FILE);
    fout << result;
    fout.close();
}

int solve(vector<int> a, vector<int> b) {
    // Check if the sum of the elements in the two arrays is the same
    int sum_a = accumulate(a.begin(), a.end(), 0);
    int sum_b = accumulate(b.begin(), b.end(), 0);

    // If the sum of the elements in the two arrays is different
    // then there is no solution
    if (sum_a != sum_b) {
        return -1;
    }

    int solution = 0, index_in_a = 0, index_in_b = 0;
    while (index_in_a < a.size()) {
        if (a[index_in_a] > b[index_in_b]) {
            // Compress B
            index_in_b++;
            b[index_in_b] += b[index_in_b - 1];
        } else if (a[index_in_a] < b[index_in_b]) {
            // Compress A
            index_in_a++;
            a[index_in_a] += a[index_in_a - 1];
        } else {
            // If the elements are equal,
            // jump to the next element in the solution array
            index_in_a++;
            index_in_b++;

            // New character in the solution found
            solution++;
        }
    }

    return solution;
}

int main() {
    vector<int> a, b;
    read_input(a, b);

    int result = solve(a, b);

    print_output(result);
}
