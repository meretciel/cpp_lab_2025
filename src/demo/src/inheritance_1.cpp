//
// Created by ryan on 5/16/24.
//
#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {};

void foo(Base x) {
    cout << "foo Base is called\n";
}

//void foo(Derived x) {
//    cout << "foo Derived is called\n";
//}

int main() {
    Base b = Base{};
    Derived d = Derived{};

    if (auto x = 10; false) {
        cout << "if block: x=" << x << "\n";
    } else {
        cout << "else block: x="<< x << "\n";
    }

}