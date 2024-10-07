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

    //bit_buffer for holding the byte sequence from the text

    //skapar array av filpekare
    FILE *file_arr[3];

    //open files
    // file 0
    /*
    file_arr[0] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/freqTable_file0.txt", "w");
    // file 1
    file_arr[1] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/balen.txt", "rb");
    //file 2
    file_arr[2] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/out_file2.bin", "wb");
    */

    file_arr[0] = fopen("freqTable_file0.txt", "w");
    // file 1
    file_arr[1] = fopen("balen.txt", "rb");
    //file 2
    file_arr[2] = fopen("out_file2.bin", "wb");


    Table *f_table = frequency_analysis(1, file_arr[0], file_arr[1]);
    /*
    printf("printing freq_analysis\n");
    print_table(f_table);
    printf("--------------------\n");

    printf("printing pqueue\n");
    void *pq = initialize_trie_start_values(f_table);
    free(f_table);
    printf("--------------------\n");

    build_trie(pq);
    printf("--------------------\n");

    //orsakar något error
    // allokerar minne för huffmantabellen
    Table *h_table = table_create_bit_sequence();
    //fill h_table
    //fputs("test", file_arr[2]);
    //close(file_arr[2]);

    // allokerar minne för varje bit_value element i h_table
    // detta är inte en färdig implementation, ska använda bit buffer istället
    /*
    for (int i = 0; i < 256; i++) {
        h_table[i].bit_value = calloc(100, sizeof(char));
        h_table[i].bit_sequence = bit_buffer_empty();
    }
    */
    /*
    printf("traverse trie\n");
    fill_h_table(pq, h_table);
    printf("--------------------\n");

    // prints the value after traversing the trie
    printf("prints the bit value in the huffman_table");
    printf("\n");
    for (int i = 0; i < 256; i++) {
        bit_buffer_print(h_table[i].bit_sequence);
        //printf("value %d\t%s\n", i, h_table[i].bit_value);
    }
    printf("--------------------\n");

    printf("prints the encoded bits");
    //output file has to be cleared
    //!!! Detta måste så klart fixas till
    fclose(file_arr[1]);
    file_arr[1] = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/balen.txt", "r");

    encode(h_table, file_arr[1], file_arr[2], "file_name");

    printf("\n");

    */


    return 0;

}