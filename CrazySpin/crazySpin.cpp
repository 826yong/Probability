#include <iostream>
#include <random>
using namespace std;

int main() {
    int your_chips = 10000;

    while (true) {
        cout << "\n\n--- Your have " << your_chips << " chips ---" << endl;

        int bet_num;
        cout << "\n-- Please choose a factor of 36 --" << endl;
        cout << "Enter your bet number: ";
        cin >> bet_num;

        while (36 % bet_num) {
            cout << "\nThe number isn't a fator of 36" << endl;
            cout << "-- Please choose a factor of 36 --" << endl;
            cout << "Enter your bet number: ";
            cin >> bet_num;
        }

        int bet_amount;
        cout << "\n-- Please decide your bet amount --" << endl;
        cout << "Enter your bet amount: ";
        cin >> bet_amount;

        string choice;
        while ((your_chips - bet_amount) < 0) {
            cout << "\nYou don't have so many chips" << endl;
            cout << "Do you want to continue the game? [Y]yes [N]no  " ;
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                cout << "\nEnter your bet amount again: ";
                cin >> bet_amount;
            }
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 36);
        int random_num = dist(gen);

        bool correct;
        
        if (!(random_num % bet_num)) {
            your_chips += (bet_num - 1) * bet_amount;
            correct = true;
        } else {
            your_chips -= bet_amount;
            correct = false;
        }

        cout << "\nThe turntable result is " << random_num << endl;
         
        if (correct == true) {
            cout << "\n---- Congratulation! You win, you can get " << (bet_num - 1) * bet_amount << " chips ----" << endl;
        } else {
            cout << "\n---- Huh? You lose, you lose " << bet_amount << " chips ----" << endl;
        }

        cout << "\nDo you want to play again? [Y]yes [N]no  ";
        cin >> choice;

        if (choice == "N" || choice == "n") {
            return 0;
        }
    }
    return 0;
}