/*
  This code was a snippet used years ago tobe implemented in a FPGA. The problem
  back then was, given a setup with N detectors we wanted simultaneously read the
  signal from M<N detectors. Since keep a table of all possible combinations in
  the FPGA was not possible the best solution was iterate over all permutations.

  2015-10-12
*/

#include <stdio.h>
#include <stdlib.h>


void permutations(const int detectors, const int coincidences);
uint64_t next(uint64_t pattern);


int main(int argc, char **argv) {
    int num_detectors, num_coincidences;

    if (argc != 3) {
        printf("Usage: bit_permut num_detectors num_coincidences\n");
        exit(1);
    }

    num_detectors = atoi(argv[1]);
    num_coincidences = atoi(argv[2]);

    if (num_coincidences > num_detectors) {
        printf("num_coincidences cannot exceed the number of detectors.\n");
        exit(1);
    }

    permutations(num_detectors, num_coincidences);

    return 0;
}


void permutations(const int detectors, const int coincidences) {
    void print_bits(uint64_t n, const int length); // debug only
    uint64_t bit_pattern, final_pattern;

    bit_pattern = (1ULL << coincidences) - 1;
    final_pattern = bit_pattern << (detectors - coincidences);

    print_bits(bit_pattern, detectors);
    while (bit_pattern != final_pattern) {
        bit_pattern = next(bit_pattern);
        print_bits(bit_pattern, detectors);
    }
}


uint64_t next(uint64_t pattern) {
    // Algorithm found in: http://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation by Sean Eron Anderson
    uint64_t aux;
    aux = pattern | (pattern - 1);
    aux = (aux + 1) | (((~aux  & -~aux) - 1) >> (__builtin_ctzll(pattern) + 1));
    return aux;
}


void print_bits(uint64_t n, const int length) {
    for (int i = 0; i < length; i++) {
        (n & 1ULL) ? printf("1") : printf("0");
        n >>= 1;
    }
    printf("\n");
}
