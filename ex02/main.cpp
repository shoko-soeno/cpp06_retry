#include "Base.h"
#include <iostream>
#include <unistd.h> // For sleep function

int main()
{
    // int countA = 0, countB = 0, countC = 0;
    // for (int i = 0; i < 30; ++i) {
    //     Base* b = generate();
    //     if (dynamic_cast<A*>(b)) countA++;
    //     else if (dynamic_cast<B*>(b)) countB++;
    //     else if (dynamic_cast<C*>(b)) countC++;
    //     delete b;
    //     sleep(1); // Sleep for 1 second to avoid too fast generation
    // }
    // std::cout << "A: " << countA << ", B: " << countB << ", C: " << countC << std::endl;

    Base *base = generate();
    std::cout << "Identifying using pointer: ";
    identify(base);
    std::cout << "Identifying using reference: ";
    identify(*base);
    delete base;

    std::cout << "\nTesting explicit types:" << std::endl;
    Base *a = new A();
    std::cout << "Type A - Pointer identification: ";
    identify(a);
    std::cout << "Type A - Reference identification: ";
    identify(*a);
    delete a;

    Base *b = new B();
    std::cout << "Type B - Pointer identification: ";
    identify(b);
    std::cout << "Type B - Reference identification: ";
    identify(*b);
    delete b;

    Base *c = new C();
    std::cout << "Type C - Pointer identification: ";
    identify(c);
    std::cout << "Type C - Reference identification: ";
    identify(*c);
    delete c;

    std::cout << "\nTesting invalid types:" << std::endl;
    Base *invalid = new Base();
    std::cout << "Invalid type - Pointer identification: ";
    identify(invalid);
    std::cout << "Invalid type - Reference identification: ";
    identify(*invalid);
    delete invalid;

    return 0;
}
