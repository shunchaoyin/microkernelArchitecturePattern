#include <iostream>
#include <functional>
#include "signal_enhance.hpp" // Assumes SignalEx is implemented here

// Free function
int add(int x, int y) {
    return x + y;
}

class MyClass
{
public:
    int add(int a, int b) { return a + b; }
    int multi(int a, int b) const { return a * b; }
};

int main()
{
    SignalEx<int, int, int> signal; // Result = int, Args... = int, int

    // Connect free function
    signal.connect(add);

    // Emit signal for free function
    auto results = signal.emit(3, 5);

    // Process results
    for (const auto& result : results) {
        std::cout << "Free Function Result: " << result << "\n";
    }
    // Connect member functions
    auto myclass = std::make_shared<MyClass>();
    signal.connect(myclass, &MyClass::add);
    signal.connect(myclass, &MyClass::multi);

    // Emit signal for member functions
    auto results_2 = signal.emit(3, 5);

    // Process results
    for (const auto& result : results_2) {
        std::cout << "Member Function Result: " << result << "\n";
    }
    return 0;
}
