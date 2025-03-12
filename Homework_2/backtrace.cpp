#include <iostream>
#include <execinfo.h>
#include <cxxabi.h>
#include <cstdlib>

void stack_dump(int depth, std::ostream& os) {
    void* buffer[depth + 1];
    int nptrs = backtrace(buffer, depth + 1);
    
    char** strings = backtrace_symbols(buffer, nptrs);
    if (strings == nullptr) {
        os << "Error: backtrace_symbols\n";
        return;
    }

    for (int i = 1; i < nptrs; ++i) {
        char* mangledName = nullptr;
        char* offset = nullptr;

        for (char* p = strings[i]; *p; ++p) {
            if (*p == '(') {
                mangledName = p + 1;
            } 
            else if (*p == '+') {
                offset = p;
            } 
            else if (*p == ')' && offset) {
                *p = '\0';
                break;
            }
        }

        if (mangledName && offset) {
            *offset++ = '\0';

            int status;
            char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);

            if (status == 0) {
                os << strings[i] << " : " << demangledName << "+" << offset << std::endl;
            } else {
                os << "Demangling failed for: " << mangledName << " with status: " << status << std::endl;
                os << strings[i] << " : " << mangledName << "+" << offset << std::endl;
            }
            free(demangledName);
        } else {
            os << strings[i] << std::endl;
        }
    }

    free(strings);
}

double sum(double a, double b) {
    return a + b;
}

void UPPERCASE_FUNCTION(std::string str) {
    sum(1.5, 4.1);
}

void start() {
    UPPERCASE_FUNCTION("test");
}

int input() {
    int value;
    std::cout << "Input the size of backtraced buffer: ";

    try {
        std::cin >> value;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return -1;
    }

    return value;
}

int main() {
    start();

    stack_dump(input(), std::cout);
    return 0;
}