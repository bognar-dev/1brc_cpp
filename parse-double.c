#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HCAP (4096)
#define BUFSIZE (1 << 10)
#define NO_CITY (-1)

struct City {
    char city[100];
    int count;
    double sum, min, max;
};

/**
 * @description: hash - Returns a simple (but fast) hash for the first n bytes of data.
 * @data: Pointer to the data to be hashed.
 * @n: Number of bytes to hash.
 * @param data
 * @param n
 * @return hash
 */
static unsigned int hash(const unsigned char *data, int n) {
    unsigned int hash = 0;

    for (int i = 0; i < n; i++) {
        hash = (hash * 31) + data[i];
    }

    return hash;
}


/**
 * @description compareGroup - Compares two cities by their name.
 * @param ptr_a
 * @param ptr_b
 * @return bool
 */
static int compareStr(const void *ptr_a, const void *ptr_b) {
    return strcmp(((struct City *)ptr_a)->city, ((struct City *)ptr_b)->city);
}



/**
 * @description printResults - Prints the results of the parsing.
 * @param results
 * @param resultCount
 */
void printResults(const struct City *results, const int *resultCount) {
    for (int i = 0; i < resultCount; i++) {
        printf("%s=%.1f/%.1f/%.1f%s", results[i].city, results[i].min,
               results[i].sum / results[i].count, results[i].max,
               i < resultCount? ", " : "");
    }
    puts("\n");
}

/**
 * parse_double - Parses a string into a double value.
 * @dest: Pointer to a double where the parsed value will be stored.
 * @s: Pointer to the string to be parsed.
 * @example:
 * The function first checks if the first character of the string is a minus sign (-).
 * If it is, it sets mod to -1.0 and increments the string pointer s to point to the next character.
 * If the first character is not a minus sign, mod is set to 1.0.
 * The function then checks if the second character of the string is a decimal point (.).
 * If it is, it calculates the double value as the sum of the first character and the third character divided by 10.0,
 * subtracts 1.1 * '0' to adjust for the ASCII value of '0', and multiplies the result by mod to account for a possible negative sign.
 * The pointer s is then incremented by 4 to point to the character following the last character used in the conversion.
 * If the second character is not a decimal point,
 * the function calculates the double value as the sum of the first two characters times 10 plus the fourth character divided by 10.0,
 * subtracts 11.1 * '0' to adjust for the ASCII value of '0', and multiplies the result by mod to account for a possible negative sign.
 * The pointer s is then incremented by 5 to point to the character following the last character used in the conversion.
 *
 */
static const char *parse_double(double *dest, const char *s) {
    double mod;
    if (*s == '-') {
        mod = -1.0;
        s++;
    } else {
        mod = 1.0;
    }

    if (s[1] == '.') {
        *dest = (((double)s[0] + (double)s[2] / 10.0) - 1.1 * '0') * mod;
        return s + 4;
    }

    *dest =
            ((double)((s[0]) * 10 + s[1]) + (double)s[3] / 10.0 - 11.1 * '0') * mod;
    return s + 5;
}




int main(int argc, const char **argv) {
    const char *file = "../data/measurements.txt";
    if (argc > 1) {
        file = argv[1];
    }

    FILE *fh = fopen(file, "r");
    if (!fh) {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    struct City results[450];
    int resultCount= 0;
    char buf[BUFSIZE];
    int map[HCAP];
    memset(map, NO_CITY, HCAP * sizeof(int));

    while (fgets(buf, BUFSIZE, fh)) {
        char *pos = strchr(buf, ';');
        *pos = 0x0;
        double measurement;
        parse_double(&measurement, pos + 1);

        // find index of group by key through hash with linear probing
        int h = hash((unsigned char *)buf, pos - buf) & (HCAP - 1);
        while (map[h] != NO_CITY && strcmp(results[map[h]].city, buf) != 0) {
            h = (h + 1) & (HCAP - 1);
        }
        int c = map[h];

        if (c < 0) {
            strcpy(results[resultCount].city, buf);
            results[resultCount].sum = measurement;
            results[resultCount].max = measurement;
            results[resultCount].min = measurement;
            results[resultCount].count = 1;
            map[h] = resultCount;
            resultCount++;
        } else {
            results[c].sum += measurement;
            results[c].count += 1;
            if (results[c].min > measurement) {
                results[c].min = measurement;
            }
            if (results[c].max < measurement) {
                results[c].max = measurement;
            }
        }
    }

    qsort(results, (size_t) resultCount, sizeof(*results), compareStr);


    printResults(results, &resultCount);

    fclose(fh);
}
