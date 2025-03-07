#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>  
#include <set>        
#include <iomanip>    
using namespace std;

// to generate the final number (two digits)
string gen_random_digit() {
    srand(time(0));
    int digit1 = rand() % 10;
    int digit2 = rand() % 10;

    while (digit2 == digit1) {
        digit2 = rand() % 10;
    }

    stringstream ss;
    ss << digit1 << digit2;

    return ss.str();
}


// to check the guess number is confirm or not
pair<int, int> check_conform(const string &guess, const string &answer) {
    int A = 0, B = 0;

    for (int i = 0; i < 2; i++) {
        if (guess[i] == answer[i]) A++;
        else if (answer.find(guess[i]) != string::npos) B++;
    }
    return make_pair(A, B);
}

// filter possible number combinations
vector<string> filter_combinations(const vector<string> possible_num, const string &guess, pair<int, int> feedback) {
    vector<string> new_possible_num;
    for (const string &num : possible_num) {
        if (check_conform(num, guess) == feedback) {
            new_possible_num.push_back(num);
        }
    }

    return new_possible_num;
}


int main() {

    // to find all possible combinations
    vector<string> all_values;
    for (char i = '0'; i <= '9'; i++) {
        for (char j = i; j <= '9'; j++) {
            if (i != j) {
                all_values.push_back(string(1, i) + string(1, j));
                all_values.push_back(string(1, j) + string(1, i));
            }
        }
    }

    string final_answer = gen_random_digit();

    string gusee_digits;
    set<string> already_guess;
    vector<string> possible_num = all_values;
    cout << "Game Start! Guess two different numbers!" << endl;

    while (true) {
        cout << "Guess: ";
        cin >> gusee_digits;

        if (find(all_values.begin(), all_values.end(), gusee_digits) == all_values.end()) {
            cout << "Please input valid numbers (no repeat)" << endl;
            continue;
        }
        if (already_guess.find(gusee_digits) != already_guess.end()) {
            cout << "This combination has been guessed. Try another!" << endl;
            continue;
        }
        already_guess.insert(gusee_digits);

        pair<int, int> check = check_conform(gusee_digits, final_answer);
        int A = check.first;
        int B = check.second;
        cout << A << "A" << B << "B" << endl;

        if (A == 2) {
            cout << "Correct! You guess the answer!" << endl;
            break;
        }

        possible_num = filter_combinations(possible_num, gusee_digits, check);

        int remaining_count = possible_num.size();
        double probability = (1.0 / remaining_count) * 100;

        cout << "Probability of guessing right: " << fixed << setprecision(2) << probability << "%" 
            << " (possible cases: " << remaining_count << ")" << endl;   
    }

    return 0;
}