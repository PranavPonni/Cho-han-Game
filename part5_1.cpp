#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> 

class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

class ResultCalculator {
public:
    bool isEven(int num) {
        return num % 2 == 0;
    }
};

class UserInput {
public:
    char getChoice() {
        char choice;
        std::cout << "Enter your choice (0 for Even / 1 for Odd / X to exit): ";
        std::cin >> choice;
        return choice;
    }

    int getBetAmount(int money) {
        int betAmount;
        std::cout << "Enter the amount you want to bet (current balance: " << money << "): ";
        std::cin >> betAmount;
        return betAmount;
    }
};

class OutputResult {
public:
    void showResult(bool isCorrect) {
        if (isCorrect) {
            std::cout << "Congratulations! You guessed correctly.\n";
        } else {
            std::cout << "Oops! Your guess was incorrect.\n";
        }
    }

    void showInvalidInput() {
        std::cout << "Please input a correct choice (0 for Even / 1 for Odd / X to exit).\n";
    }
};

int main() {
    srand(time(0));
    int money = 10000; 
    Dice dice;
    ResultCalculator calculator;
    UserInput userInput;
    OutputResult outputResult;
    std::cout << "Starting Cash: " << money << "\n";
    while (money > 0) {
        char userChoice = userInput.getChoice(); 
        if (userChoice == 'x') { 
            break; 
        } else if (userChoice != '0' && userChoice != '1') {
            outputResult.showInvalidInput();
            continue;
        }

        int betAmount = userInput.getBetAmount(money);
        if (betAmount <= 0 || betAmount > money) {
            std::cout << "Invalid bet amount. Please bet between 1 and " << money << ".\n";
            continue;
        }

        int dice1 = dice.roll();
        int dice2 = dice.roll();
        int sum = dice1 + dice2;

        bool isUserChoiceEven = calculator.isEven(userChoice - '0'); 
        bool isSumEven = calculator.isEven(sum);
        bool isCorrect = (isUserChoiceEven && isSumEven) || (!isUserChoiceEven && !isSumEven);
        std::cout << "Dice Total: " << sum << "\n";
        outputResult.showResult(isCorrect);
        if (isCorrect) {
            money += betAmount; 
        } else {
            money -= betAmount;
        }
        std::cout << "Current balance: " << money << "\n\n";
    }
    std::cout << "Remaining cash: " << money << "\n";
    if (money <= 0) {
        std::cout << "You're out of money. Game over.\n";
    }
    return 0;
}
