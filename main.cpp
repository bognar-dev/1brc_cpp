#include "calculations.h"

int main(int argc, const char **argv) {
    const char *file = "../data/meassurements_1_000.txt";
    if (argc > 1) {
        file = argv[1];
    }
    evaluate(file);
}