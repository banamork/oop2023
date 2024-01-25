#include <iostream>
#include "Prog1.h"

using namespace Prog1;

// основная функция
int main() {
    CSR coord;
    try {
        coord = input();
        std::cout << "Old matrix" << std::endl;
        //made_and_print(coord);
        output(coord);
        specialfunc(coord);
        std::cout << "New matrix" << std::endl;
        //made_and_print(coord);
        output(coord);
        erase(coord);
    }
    catch (const std::bad_alloc& ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        erase(coord);
        //erase(newMatrix);
        return 1;
    }
    catch (const std::exception& e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        erase(coord);
        //erase(newMatrix);
        return 1;
    }
    return 0;
}
