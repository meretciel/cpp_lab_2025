//
// Created by ryan on 12/5/23.
//

#include "MyClass.h"
#include <iostream>

MyClass::MyClass(int value) {
    this->value = value;
}

int main(int argc, char* argv[]) {
    MyClass obj{20};
    std::cout << "Value: " << obj.value << "\n";
}