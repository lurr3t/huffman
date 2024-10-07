#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <assert.h>

#include "freq_analysis.h"
#include "trie.h"
#include "code.h"
#include "list.h"
#include "bit_buffer.h"

void menu();

int main(int argc, char *argv[]) {


    //skapar array av filpekare
    FILE *file_arr[3];

    //open files
    // file 0
    file_arr[0] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/freqTable_file0.txt", "r");
    // file 1
    file_arr[1] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/out_file2.bin", "rb");
    //file 2
    file_arr[2] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/test_file_out.txt", "wb");

    Table *f_table = frequency_analysis(0, file_arr[0], file_arr[1]);

    printf("printing freq_analysis\n");
    print_table(f_table);
    printf("--------------------\n");

    printf("printing pqueue\n");
    Trie_node *pq = initialize_trie_start_values(f_table);
    free(f_table);
    printf("--------------------\n");

    build_trie(pq);
    printf("--------------------\n");

    //pqueue_print(pq, printfunk);

    decode(pq, file_arr[1], file_arr[2]);





    return 0;

}
