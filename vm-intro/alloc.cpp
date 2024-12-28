#include <iostream>
#include <cstdlib>
#include <unistd.h>

int MEGABYTE = 2 << 20;

int main(int argc, char* argv[]) {
    // Check for command line arguments
    if (argc > 1) {
        std::cout << "Arguments passed:" << std::endl;
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << std::endl;
        }
    } else {
        std::cout << "No arguments passed." << std::endl;
        return 0;
    }

    std::cout << "PID: " << getpid() << std::endl;

    // Your application logic here
    int n = std::atoi(argv[1]);
    int sz = n * MEGABYTE;
    int* arr = (int*)malloc(sz);

    while (true) {
        for(int i = 0; i < (sz / sizeof(int)); i++) {
            arr[i] = i;
        }
    }

    return 0;
}