#include <iostream>

using std::cout;

template <typename T>
class OutsideMethodDefinition {
    public:
        OutsideMethodDefinition() {}

        void insideClassMethod();
};

/* Define insideClassMethod outside the class */
template <typename T>
void OutsideMethodDefinition<T>::insideClassMethod() {
    cout << "Method defined outside the class successfully!.\n";
}

int main() {
    OutsideMethodDefinition<int> t = OutsideMethodDefinition<int>();
    t.insideClassMethod();
}
