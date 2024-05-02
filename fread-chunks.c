#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define HCAP (4096)
#define BUFSIZE ((1 << 20) * 64)
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
    return strcmp(((struct City *) ptr_a)->city, ((struct City *) ptr_b)->city);
}


/**
 * @description print_results - Prints the results of the city measurement.
 * @results: Pointer to an array of City structs.
 * @nresults: Number of City structs in the array.
 * @param results
 * @param nresults
 */
void print_results(struct City results[], int nresults) {
    char buf[1024 * 16];
    char *b = buf;
    for (int i = 0; i < nresults; i++) {
        b += sprintf(b, "%s=%.1f/%.1f/%.1f%s", results[i].city, results[i].min,
                     results[i].sum / results[i].count, results[i].max,
                     i < nresults - 1 ? ", " : "");
    }
    *b = 0x0;
    puts(buf);
}


/**
 * @description parse_city - Parses a city name from a string.
 * @city: Pointer to a buffer where the city name will be stored.
 * @results: Pointer to an array of City structs.
 * @resultCount: Number of City structs in the array.
 * @param city
 * @param results
 * @param resultCount
 * @return int
 */
static int parseCity(const char *city, struct City results[], int resultCount) {
    for (int i = 0; i < resultCount; i++) {
        if (strcmp(results[i].city, city) == 0) {
            return i;
        }
    }

    return -1;
}

/**
 * parse_double - Parses a string into a double value.
 * @dest: Pointer to a double where the parsed value will be stored.
 * @s: Pointer to the string to be parsed.
 *
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
        *dest = (((double) s[0] + (double) s[2] / 10.0) - 1.1 * '0') * mod;
        return s + 4;
    }

    *dest =
            ((double) ((s[0]) * 10 + s[1]) + (double) s[3] / 10.0 - 11.1 * '0') * mod;
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
    int nresults = 0;
    char *buf = malloc(BUFSIZE);
    if (buf == NULL || buf == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }
    int map[HCAP];
    memset(map, -1, HCAP * sizeof(int));

    const char *start;
    char *pos;
    double measurement;
    unsigned int h;
    int cityIdx;
    int keylen;

    while (1) {
        size_t nread = fread(buf, 1, BUFSIZE, fh);
        if (nread <= 0) {
            break;
        }

        const char *s = buf;
        long rewind = 0;
        while (buf[nread - 1] != '\n') {
            rewind--;
            nread--;
        }
        fseek(fh, rewind, SEEK_CUR);

        while (s < &buf[nread]) {
            start = s;
            pos = strchr(s, ';');
            keylen = (int) (pos - start);
            s = parse_double(&measurement, pos + 1);

            // find index of group by key through hash with linear probing
            h = hash((unsigned char *) start, keylen) & (HCAP - 1);
            cityIdx = map[h];
            while (cityIdx != NO_CITY &&
                   memcmp(results[cityIdx].city, start, (size_t) keylen) != 0) {
                h = (h + 1) & (HCAP - 1);
                cityIdx = map[h];
            }

            if (cityIdx < 0) {
                memcpy(results[nresults].city, start, (size_t) keylen);
                results[nresults].city[keylen] = '\0';
                results[nresults].sum = measurement;
                results[nresults].max = measurement;
                results[nresults].min = measurement;
                results[nresults].count = 1;
                map[h] = nresults;
                nresults++;
            } else {
                results[cityIdx].sum += measurement;
                results[cityIdx].count += 1;
                if (results[cityIdx].min > measurement) {
                    results[cityIdx].min = measurement;
                } else if (results[cityIdx].max < measurement) {
                    results[cityIdx].max = measurement;
                }
            }
        }
    }

    qsort(results, (size_t) nresults, sizeof(*results), compareStr);

    print_results(results, nresults);
    fclose(fh);
}
