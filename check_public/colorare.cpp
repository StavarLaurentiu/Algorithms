#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;

#define INPUT_FILE "colorare.in"
#define OUTPUT_FILE "colorare.out"

#define EMPTY_PAINTING 'E'
#define HORIZONTAL 'H'
#define VERTICAL 'V'

#define MOD 1000000007

void print_output(long long solution) {
    ofstream fout(OUTPUT_FILE);
    fout << solution;
    fout.close();
}

// Computes (base ^ exponent) % mod in O(log exponent)
// TOOK IT FROM THE LAB1 SOLUTION PROVIDED ON TEAMS
int fast_pow(int base, int exponent, int mod) {
    if (exponent == 0) {
       return 1;
    }

    int remaining = 1;
    while (exponent != 1) {
        if (exponent % 2 == 0) {
            exponent /= 2;
            base = (1LL * base * base) % mod;
        } else {
            exponent--;
            remaining = (1LL * remaining * base) % mod;
        }
    }

    return (1LL * remaining * base) % mod;
}

int main(int argc, char *argv[])
{   
    // Declare input file
    ifstream fin(INPUT_FILE);

    // Read the number of zones and iterate trough each one
    int zones;
    fin >> zones;

    // Final solution
    long long solution = 0;

    // Type of the previous zone added to the painting
    // Initiated with a special "EMPTY_PAINTING" value
    char prev_zone_type = EMPTY_PAINTING;

    for (int i = 0; i < zones; i++) {
        // Read the number of rectangles in the current zone
        int rectangles;
        fin >> rectangles;

        // Read the zone type
        char zone_type;
        fin >> zone_type;

        // Append the first rectangle to the painting
        switch (prev_zone_type)
        {
        // If's the first rectangle in the painting initiate the solution properly
        case EMPTY_PAINTING:
            if (zone_type == HORIZONTAL) {
                solution = 6;
            } else {
                solution = 3;
            }
            break;
        
        // If the previous zone was a HORIZONTAL one then update the solution properly
        case HORIZONTAL:
            if (zone_type == HORIZONTAL) {
                solution = (solution * 3) % MOD;
            }
            break;

        // If the previous zone was a VERTICAL one then update the solution properly
        case VERTICAL:
            solution = (solution * 2) % MOD;
            break;

        default:
            break;
        }

        // Update prev_zone_type and the number of rectangles
        prev_zone_type = zone_type;
        rectangles--;

        // Append the rest of the rectangles to painting
        if (zone_type == HORIZONTAL) {
            solution = (solution * fast_pow(3, rectangles, MOD)) % MOD;
        } else {
            solution = (solution * fast_pow(2, rectangles, MOD)) % MOD;
        }
    }

    print_output(solution);

    fin.close();
    return 0;
}