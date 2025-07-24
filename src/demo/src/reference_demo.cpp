//
// Created by ryan on 5/14/24.
//

#include <iostream>

using namespace std;

void print_int(int value) {
    cout << "[copy] value is: " << value << "\n";
}

void print_int(int& value) {
    cout << "[reference] value is: " << value << "\n";
}

int main() {
    int x = 10;
    int& ref = x;
//    print_int(x);
    return 0;
}