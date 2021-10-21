#include <type_traits>
#include <iostream>
#include <vector>

struct bigint {
    template <class RHS, typename std::enable_if<is_bigvalue<RHS>::value>::type* = nullptr>
    bigint &operator =(const RHS &rhs)
    {
        return *this;
    }
};

int main() {
    // your code goes here
    bigint A;
//    A = 1;    // error!
    return 0;
}