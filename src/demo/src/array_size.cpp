#include <iostream>
#include <iterator>

using namespace std;

int main() {
    int intArr[]{1,2,3,4,5};
    char charArr[]{"12345"};

    std::cout << "The size of the int array is " << std::size(intArr) << "\n";
    std::cout << "The size of the char array is " << std::size(charArr) << "\n";
    std::cout << "The size can be calculated with sizeof operator. For example, sizeof(charArr) / sizeof(charArr[0]) = "
        << sizeof(charArr) / sizeof(charArr[0]) << "\n";
    return 0;
}