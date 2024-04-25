#include "calculations.h"

int main(int argc, const char **argv) {
    const char *file = "/project/measurements.txt";
    if (argc > 1) {
        file = argv[1];
    }
    evaluate(file);
}