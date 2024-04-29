//
// Created by Niklas on 20/03/2024.
//
#pragma once


#include <string>
#include <vector>
#include <map>


#define HCAP (4096)
#define BUFSIZE ((1 << 20) * 32)

static const char *parse_double(double *dest, const char *s);
static unsigned int hash(const unsigned char *data, int n);
static int cmp(const void *ptr_a, const void *ptr_b);
void print_results(struct result results[], int nresults);
void evaluate(const char *file);


struct result {
    char city[100];
    int count;
    double sum, min, max;
};