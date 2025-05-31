#include "Base.h"

Base *generate(void) {
    std::srand(time(NULL));
    int random = rand() % 3;

    switch (random) {
        case 0:
            std::cout << "Generated class A" << std::endl;
            return new A();
        case 1:
            std::cout << "Generated class B" << std::endl;
            return new B();
        default:
            std::cout << "Generated class C" << std::endl;
            return new C(); // This should never happen
    }
}

void identify(Base *p) {
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void identify(Base &p) {
    try {
        A &a = dynamic_cast<A &>(p);
        (void)a;
        std::cout << "Identified as class A" << std::endl;
        return ;
    }
    catch (std::bad_cast &) {}
    try {
        B &b = dynamic_cast<B &>(p);
        (void)b;
        std::cout << "Identified as class B" << std::endl;
        return ;
    }
    catch (std::bad_cast &) {} 
    try {
        C &c = dynamic_cast<C &>(p);
        (void)c;
        std::cout << "Identified as class C" << std::endl;
        return ;
    }
    catch (std::bad_cast &) {}
    std::cout << "Unknown type" << std::endl;
}
