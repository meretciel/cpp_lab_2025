//
// Created by ryan on 12/17/23.
//
#include <memory>
#include <string>

class MyClass {
public:
    std::string value;
    MyClass(std::string name) {
        this->value = name;
    }
};


int main(int argc, char **argv)
{
    auto p = std::make_shared<MyClass>("test");
}