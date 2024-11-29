#include <iostream>
#include <functional>
#include "signal_enhance.hpp"

// Free function
int add(int x, int y) {
    return x + y;
}

int main()
{
    SignalEx<int, int, int> signal; // Result = int, Args... = int, int

    // Connect free function
    signal.connect(add);

    // Emit signal
    auto results = signal.emit(3, 5);

    // Process results
    for (const auto& result : results) {
        std::cout << "Result: " << result << "\n";
    }


    return 0;
}
