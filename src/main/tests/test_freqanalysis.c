#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <assert.h>

#include "freq_analysis.h"

void menu();

int main(int argc, char *argv[]) {

    //skapar array av filpekare
    FILE *file_arr[3];

    //open files
    // file 0
    file_arr[0] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/freqTable_file0.txt", "w");
    // file 1
    file_arr[1] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/balen.txt", "rb");
    //file 2
    file_arr[2] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/out_file2.txt", "a");

    Table *f_table = frequency_analysis(1, file_arr[0], file_arr[1]);

    print_table(f_table);

    return 0;
}





