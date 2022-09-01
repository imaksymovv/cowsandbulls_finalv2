#include <iostream>

struct CowsAndBullsAnswer {
    unsigned int cows;
    unsigned int bulls;
    unsigned int result[4];
};

class IAskNumber {
public:
    virtual CowsAndBullsAnswer Ask(unsigned int number[4]) const = 0;
};

class CowsAndBullsPlayer {
    CowsAndBullsPlayer() = delete;
protected:
    explicit CowsAndBullsPlayer(unsigned int n[4]) :
        number{ n[0], n[1], n[2], n[3] } {}
    unsigned int operator[](size_t index) const {
        return number[index];
    }
private:
    unsigned int number[4];
};

class CowsAndBullsComputerPlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsComputerPlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {}

    CowsAndBullsAnswer Ask(unsigned int number[4]) const override {
        CowsAndBullsAnswer counter = { };
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (number[i] == this->operator[](j)) {
                    counter.cows++;
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            if (number[i] == this->operator[](i)) {
                counter.bulls++;
            }
        }
        return counter;
    }
    unsigned int operator[](size_t index) const {
        return CowsAndBullsPlayer::operator[](index);
    }
};

class CowsAndBullsLivePlayer : private CowsAndBullsPlayer, public IAskNumber {
public:
    CowsAndBullsLivePlayer(unsigned int n[4]) : CowsAndBullsPlayer(n) {}

    CowsAndBullsAnswer Ask(unsigned int number[4]) const override {
        CowsAndBullsAnswer l = {};
        l.result;
        if (number[3] == this->operator[](3)) {
            l.result[3] = number[3];
        }

        if (number[2] == this->operator[](2)) {
            l.result[2] = number[2];
        }

        if (number[1] == this->operator[](1)) {
            l.result[1] = number[1];
        }

        if (number[0] == this->operator[](0)) {
            l.result[0] = number[0];
        }
        return l;
    }
};

int main() {
    srand(time(NULL));

    unsigned int n[4];

    for (int i = 0; i < 4; ++i) {
        n[i] = 1 + rand() % 9;
        for (int j = 0; j < i; j++) {
            if (n[j] == n[i]) {
                do {
                    n[i] = 1 + rand() % 9;
                } while (n[i] == n[j]);
            }
        }
    }
    CowsAndBullsComputerPlayer p1(n);
    std::cout << p1[0] << p1[1] << p1[2] << p1[3] << std::endl;

    std::cout << "try to guess computer number" << std::endl;
    bool exit = false;
    do {
        for (int i = 0; i < 4; i++) {
            std::cin >> n[i];
        }

        auto answer = p1.Ask(n);
        answer.cows = answer.cows - answer.bulls;
        std::cout << "cows: " << answer.cows << " bulls: " << answer.bulls << std::endl;
        if (answer.bulls != 4) {
            answer.cows = 0;
            answer.bulls = 0;
        }
        else {
            exit = true;
        }
    } while (exit == false);
    std::cout << "you guessed it! now its computer's turn to guess" << std::endl;

    std::cout << "Enter your number" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cin >> n[i];
    }
    CowsAndBullsLivePlayer p2(n);
    exit = false;
    unsigned int turns_counter = 0;

    do {
        for (int i = 0; i < 4; ++i) {
            n[i] = 1 + rand() % 9;
        }
        auto computer_answer = p2.Ask(n);
        turns_counter++;
        if (computer_answer.result[0] == n[0] && computer_answer.result[1] == n[1] && computer_answer.result[2] == n[2] && computer_answer.result[3] == n[3]) {
            std::cout << "computer guessed ur number! it is:" << std::endl;
            for (int i = 0; i < 4; ++i) {
                std::cout << computer_answer.result[i];
            }
            std::cout << "\n";
            std::cout << turns_counter << " turns used to guess" << std::endl;
            exit = true;
        }
        else {

        }
    } while (exit == false);
    return 0;
}