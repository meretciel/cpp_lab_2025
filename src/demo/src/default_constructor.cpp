//
// Created by ryan on 5/13/24.
//

#include <iostream>
using namespace std;

struct StructWithoutConstructor {
    int value;
};

struct StructWithConstructor {
    int value;

    explicit StructWithConstructor(int value) {
        cout << "StructWithConstructor(int value) is called.\n";
        this->value = value;
    }
};


int main() {
    StructWithoutConstructor a1{}; // This will initialize the fields to default value
                                   // See https://en.cppreference.com/w/cpp/language/zero_initialization
                                   //   => value initialization; aggregates; members of aggregates (like arrays and structs)
    StructWithoutConstructor a2; // This works. But the auto-generated constructor is called and it's a no op.
                                 // This means the value field is not initialized.

    StructWithConstructor b(20);
    // StructWithConstructor c; // <---- this line does not compile because StructWithConstructor does not have a defualt constructor
}