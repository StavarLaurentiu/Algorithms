#include <fstream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#define INPUT_FILE "criptat.in"
#define OUTPUT_FILE "criptat.out"

// A class to store the details of a word
class Details {
 public:
    string word;
    int num_of_dominant_chars;
    int length;
    double ratio;

    Details(string word, int num_of_dominant_chars) {
        this->word = word;
        this->num_of_dominant_chars = num_of_dominant_chars;
        this->length = word.length();
        this->ratio = num_of_dominant_chars / (double)length;
    }
};

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

// Get the alphabet from the words -- all the unique characters
void get_alphabet(int num_of_words, vector<string> words, set<char> &alphabet) {
    for (int i = 0; i < num_of_words; i++) {
        for (char c : words[i]) {
            alphabet.insert(c);
        }
    }
}

// Compute the number of dominant characters for each word
void compute_num_of_dominant_chars(int num_of_words, vector<string> words,
                    char dominant_char, vector<int> &num_of_dominant_chars) {
    for (int i = 0; i < num_of_words; i++) {
        for (char c : words[i]) {
            if (c == dominant_char) {
                num_of_dominant_chars[i]++;
            }
        }
    }
}

// Compare function for sorting the words
// by the ratio of (dominant characters / length)
bool compare_func(Details a, Details b) {
    if (a.ratio == b.ratio) {
        return a.length > b.length;
    }

    return a.ratio > b.ratio;
}

int solve(int num_of_words, vector<string> words) {
    // Take the alphabet from words -- all the unique characters
    set<char> alphabet;
    get_alphabet(num_of_words, words, alphabet);

    // For each character in the alphabet,
    // we will consider it the dominant character
    int max_length = INT_MIN;
    for (char dominant_char : alphabet) {
        // Compute the number of dominant characters for each word
        vector<int> num_of_dominant_chars(num_of_words, 0);
        compute_num_of_dominant_chars(num_of_words, words, dominant_char,
                                      num_of_dominant_chars);

        // Populate the vector of word details
        vector<Details> words_details(num_of_words, Details("", 0));
        for (int i = 0; i < num_of_words; i++) {
            words_details[i] = Details(words[i], num_of_dominant_chars[i]);
        }

        // Sort the words by the ratio of (dominant characters / length)
        sort(words_details.begin(), words_details.end(), compare_func);

        // Compute the maximum length of the password that can be formed
        // by concatenating the words in the order given by the sorted
        // vector, choosing the words that keep true the condition
        // num_of_dominant_chars > length / 2
        int current_length = 0;
        int current_num_of_dominant_chars = 0;
        for (int i = 0; i < num_of_words; i++) {
            int possible_length = current_length + words_details[i].length;
            int possible_num_of_dominant_chars =
                current_num_of_dominant_chars +
                words_details[i].num_of_dominant_chars;

            // If the condition is still true,
            // we can add the word to the password
            if (possible_num_of_dominant_chars > possible_length / 2) {
                current_length = possible_length;
                current_num_of_dominant_chars = possible_num_of_dominant_chars;
            }
        }

        // Update the maximum length
        max_length = max(max_length, current_length);
    }

    return max_length;
}

int main() {
    vector<string> words;
    int num_of_words = read_input(words);

    int solution = solve(num_of_words, words);

    print_output(solution);
    return 0;
}
