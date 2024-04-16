#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;

#define INPUT_FILE "criptat.in"
#define OUTPUT_FILE "criptat.out"

int read_input(vector<string> &words) {
    ifstream fin(INPUT_FILE);

    // Read the number of words
    int num_of_words;
    fin >> num_of_words;

    // Resize the vector of words
    words.resize(num_of_words);

    // Read all the words
    for (int i = 0; i < num_of_words; i++) {
        fin >> words[i];
    }

    fin.close();
    return num_of_words;
}

void print_output(int solution) {
    ofstream fout(OUTPUT_FILE);
    fout << solution;
    fout.close();
}

int compute_priority(string word, vector<int> alphabet, char dominant_letter) {
    int priority = 0;

    for (char c : word) {
        if (c == dominant_letter) {
            priority += alphabet[c - 'a'];
        } else {
            priority -= alphabet[c - 'a'];
        }
    }

    return priority;
}

void my_sort(vector<string> &words, int num_of_words, vector<int> alphabet, char dominant_letter) {
    vector<int> priority(num_of_words, 0);

    for (int i = 0; i < num_of_words; i++) {
        priority[i] = compute_priority(words[i], alphabet, dominant_letter);
    }

    
}

int solve(int num_of_words, vector<string> words) {
    // Take the alphabet as a freq vector
    vector<int> alphabet(26, 0);
    for (int i = 0; i < num_of_words; i++) {
        for (char c : words[i]) {
            alphabet[c - 'a']++;
        }
    }

    // For every letter in the alphabet
    for (int i = 0; i < 26; i++) {
        // If the letter is not in the alphabet than skip it
        if (alphabet[i] == 0) {
            continue;
        }

        char letter = i + 'a';

        // Sort the list of words, based on current dominant letter
        my_sort(words, num_of_words, alphabet, letter);
    }
}

int main(int argc, char *argv[])
{   
    vector<string> words;
    int num_of_words = read_input(words);

    int solution = solve(num_of_words, words);

    print_output(solution);
    return 0;
}