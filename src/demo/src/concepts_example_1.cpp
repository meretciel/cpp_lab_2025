//
// Created by ryan on 3/29/25.
//

#include <iterator>
using namespace std;

template<forward_iterator Iter>
void advance(Iter p, int n) {
    while (n--) {
        ++p;
    }
}

int main() {



}