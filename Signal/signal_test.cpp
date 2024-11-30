#include <iostream>
#include "signal.hpp"

// Define a class with member functions to connect to the signal
class MyClass
{
public:
    void memberFunction(int value)
    {
        std::cout << "Member function called with value: " << value << std::endl;
    }

    void constMemberFunction(int value) const
    {
        std::cout << "Const member function called with value: " << value << std::endl;
    }
};

// Free function to connect to the signal
void freeFunction(int value)
{
    std::cout << "Free function called with value: " << value << std::endl;
}

int main()
{
    // Create a signal that takes an int argument
    Signal<int> signal;

    // Create an instance of MyClass
    MyClass myObject;

    // Connect member functions
    int memberFuncID = signal.connect(&myObject, &MyClass::memberFunction);
    int constMemberFuncID = signal.connect(&myObject, &MyClass::constMemberFunction);

    // Connect a free function
    int freeFuncID = signal.connect(freeFunction);

    // Connect a lambda function
    int lambdaID = signal.connect([](int value) {
        std::cout << "Lambda function called with value: " << value << std::endl;
        });

    // Emit the signal with a value
    signal.emit(42);

    // Disconnect the free function
    signal.disconnect(freeFuncID);

    // Emit the signal again
    signal.emit(84);

    return 0;
}
