#include <iostream>
#include <execinfo.h>
#include <cxxabi.h>
#include <cstdlib>

int input() {
    int value;
    do {
        std::cout << "Input the size of backtraced buffer: ";

        try {
            std::cin >> value;
            if (value <= 0) {
                std::cerr << "Error: The size must be greater than 0." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            value = -1;
        }
        catch (...) {
            std::cerr << "Unknown exception occurred." << std::endl;
            value = -1;
        }
    } while (value <= 0);

    return value;
}


void stack_dump(int depth, std::ostream& os) {
    void* buffer[depth];
    int nptrs = backtrace(buffer, depth);
    
    char** strings = backtrace_symbols(buffer, nptrs);
    if (strings == nullptr) {
        os << "Error: backtrace_symbols\n";
        return;
    }

    for (int i = 1; i < nptrs; ++i) {
        std::string symbol(strings[i]);
        size_t begin = symbol.find('(');
        size_t end = symbol.find('+');
        size_t offset_end = symbol.find(')');


        if ((begin != std::string::npos) && (end != std::string::npos) && (offset_end != std::string::npos)) {
            std::string mangledName = symbol.substr(begin + 1, end - begin - 1);
            std::string offset = symbol.substr(end + 1, offset_end - end - 1);

            int status;
            char* demangledName = abi::__cxa_demangle(mangledName.c_str(), nullptr, nullptr, &status);

            if (status == 0) {
                os << symbol.substr(0, begin) << " :  " << demangledName << "+" << offset << std::endl;
            } else {
                os << "Demangling failed for: " << symbol.substr(0, begin) << mangledName << " with status: " << status << std::endl;
            }
            free(demangledName);
        } else {
            os << symbol << std::endl;
        }
    }

    free(strings);
}

double sum(double a, double b) {
    stack_dump(input(), std::cout);

    return a + b;
}

void stringFoo(std::string str) {
    sum(1.5, 4.1);
}

void start() {
    stringFoo("test");
}



int main() { 
    // int size = input();
    start();
    // stack_dump(size, std::cout);
    return 0;
}