#include <fstream>
#include <iomanip>

using namespace std;

#define INPUT_FILE "oferta.in"
#define OUTPUT_FILE "oferta.out"

int read_input(vector<int> &prices, int &n) {
    ifstream fin(INPUT_FILE);

    // Read the number of products
    fin >> n;
    prices.resize(n);

    // Read the constant k
    int k;
    fin >> k;

    // Read the prices of the products
    for (int i = 0; i < n; i++) {
        fin >> prices[i];
    }

    fin.close();
    return k;
}

void print_output(double solution) {
    ofstream fout(OUTPUT_FILE);
    fout << fixed << setprecision(1) << solution << "\n";
    fout.close();
}

double solve(int n, vector<int> prices) {
    // dp[i] = the minimum amount of money needed to buy the first i products
    vector<double> dp(n + 1);

    // Base cases
    dp[1] = prices[0];
    dp[2] = min(prices[0], prices[1]) / 2.0 + max(prices[0], prices[1]);
    dp[3] = min(min(dp[1] + prices[1] + prices[2] -
                        min(prices[0], min(prices[1], prices[2])),
                    dp[1] + min(prices[1], prices[2]) / 2.0 +
                        max(prices[1], prices[2])),
                dp[2] + prices[2]);

    // Compute the minimum amount of money needed to buy the first i products
    for (int i = 4; i <= n; i++) {
        dp[i] = min(min(dp[i - 1] + prices[i - 1],
                        dp[i - 2] + min(prices[i - 1], prices[i - 2]) / 2.0 +
                            max(prices[i - 1], prices[i - 2])),
                    dp[i - 3] + prices[i - 3] + prices[i - 2] + prices[i - 1] -
                        min(prices[i - 3], min(prices[i - 2], prices[i - 1])));
    }

    return dp[n];
}

int main(int argc, char *argv[]) {
    int n;
    vector<int> prices;
    int k = read_input(prices, n);

    double solution = solve(n, prices);

    print_output(solution);
    return 0;
}
