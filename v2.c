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

// hash returns a simple (but fast) hash for the first n bytes of data
static unsigned int hash(const unsigned char *data, int n) {
    unsigned int hash = 0;

    for (int i = 0; i < n; i++) {
        hash = (hash * 31) + data[i];
    }

    return hash;
}

static int compareStr(const void *ptr_a, const void *ptr_b) {
    return strcmp(((struct City *)ptr_a)->city, ((struct City *)ptr_b)->city);
}


void printResults(const struct City *results, const int *resultCount) {
    for (int i = 0; i < resultCount; i++) {
        printf("%s=%.1f/%.1f/%.1f%s", results[i].city, results[i].min,
               results[i].sum / results[i].count, results[i].max,
               i < resultCount? ", " : "");
    }
    puts("\n");
}


static int parseCity(const char *city, struct City results[], int resultCount) {
    for (int i = 0; i < resultCount; i++) {
        if (strcmp(results[i].city, city) == 0) {
            return i;
        }
    }

    return -1;
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

    while (fgets(buf, 1 << 10, fh)) {
        char *pos = strchr(buf, ';');
        *pos = 0x0;
        double measurement = strtod(pos + 1, NULL);

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

    qsort(results, (size_t)resultCount, sizeof(*results), compareStr);


    printResults(results, &resultCount);

    fclose(fh);
}
