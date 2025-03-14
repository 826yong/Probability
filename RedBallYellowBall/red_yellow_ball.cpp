#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

struct Ball {
    char which;
    char color[10]; 
};

vector<Ball> bag[5] = {
    {{'A', {'R', 'R', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}}},
    {{'B', {'R', 'R', 'R', 'R', 'R', 'Y', 'Y', 'Y', 'Y', 'Y'}}},
    {{'C', {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'Y', 'Y', 'Y'}}},
    {{'D', {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'Y'}}},
    {{'E', {'R', 'R', 'R', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}}}
};

vector<int> bags_num = {0, 1, 2, 3, 4};
void random_bags_order() {
    random_device rd;
    mt19937 g(rd());
    shuffle(bags_num.begin(), bags_num.end(), g);
}

vector<string> random_get() {
    vector<string> random_ball(5, "");

    for (int j = 0; j < 5; j++) {
        int idx = bags_num[j];
        random_ball[j] += bag[idx][0].which;
        for (int i = 0; i < 100; i++) {
            int rand_num = rand() % 10;
            random_ball[j] += bag[idx][0].color[rand_num];
        }
        random_ball[j] += " ";
    }

    return random_ball;
}

int main() {

    srand(time(0));
    random_bags_order();

    cout << "-- These are the actual number of balls in the bags --" << endl;
    cout << "A:  Red: 2,  Yellow: 8" << endl;
    cout << "B:  Red: 5,  Yellow: 5" << endl;
    cout << "C:  Red: 7,  Yellow: 3" << endl;
    cout << "D:  Red: 9,  Yellow: 1" << endl;
    cout << "E:  Red: 3,  Yellow: 7" << endl;

    int red_num[5] = {0};
    int yellow_num[5] = {0}; 
    string order = "";
    int times = 1;
    
    while (true) {
        vector<string> colors = random_get();
        
        for (int j = 0; j < 5; j++) {

            order += bag[bags_num[j]][0].which;
            
            int red_count = 0;
            int yellow_count = 0;
            for (int i = 1; i < colors[j].size(); i++) {
                if (colors[j][i] == 'R') {
                    red_count++;
                } else {
                    yellow_count++;
                }
            }

            red_num[j] += red_count;
            yellow_num[j] += yellow_count;
        }

        cout << "\n\n" << "-- This is " << times << " times draw balls --" << endl;

        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ":  Red: " << red_num[i] << ",  Yellow: " << yellow_num[i] << endl;
        }

        string guess = "";
        cout << "\n" << "Guess the sequence of the bags (e.g., ABCDE): " << endl;
        cout << "-- if you want to exit the game, please enter \"EXIT\" --" << endl;
        cin >> guess;
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (guess == "EXIT") {
            return 0;
        }


        if (guess == order) {
            cout << "\nYou guess the correct order of bags!" << endl;
            break;
        } else {
            cout << "\nThat's not right. Try again." << endl;
        }
        
        times++;
    }


    return 0;
}