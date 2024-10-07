/**
 *
 * @brief A program for doing a huffman encoding on a file that has the UTF-8 encoding.
 *
 * Lets the user encode a file and thereby compressing it. Also has an option for decoding that same file, with
 * the help of a file that stores the frequency analysis done before.
 *
 * USAGE:
 * huffman [OPTION] [FILE0] [FILE1] [FILE2]
 * -encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2
 * -decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2
 *
 * @author  Ludwig Fallström
 * @since   2021-08-20
 *
 * @{
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freq_analysis.h"
#include "trie.h"
#include "code.h"

void file_validation(int argc, FILE *file_arr[], char *argv[]);

int option_string_to_int(char *argv);

void menu();

int main(int argc, char *argv[]) {

    //creates an array that holds the files pointers to the program
    FILE *file_arr[3];

    //validerar och öppnar filerna beroende på option
    file_validation(argc, file_arr, argv);

    /*
     * converts from string to int
     * encode = 1
     * decode = 0
     */
    int option = option_string_to_int(argv[1]);

    //does the frequency analysis and stores the values in f_table
    Table *f_table = frequency_analysis(option, file_arr[0], file_arr[1]);
    //stores the values of the frequency analysis in a p_queue
    Trie_node *pq = initialize_trie_start_values(f_table);
    table_kill(f_table);
    build_trie(pq);

    //encode
    if (option) {
        Table *h_table = table_create_bit_sequence();

        fill_h_table(pq, h_table);

        //resets the file so it can be read again
        fclose(file_arr[1]);
        file_arr[1] = fopen( argv[3], "r");

        encode(h_table, file_arr[1], file_arr[2], argv[3]);

        table_kill(h_table);

    }
    //decode
    else {
        decode(pq, file_arr[1], file_arr[2]);
    }

    kill_trie(pqueue_inspect_first((const pqueue *) pq));
    pqueue_kill((void*)pq);

    //closes file pointers
    for( int i = 0; i < 3; i++) { fclose(file_arr[i]); }

    return 0;
}



/**
 * @brief                     Validates and opens the program parameter files.
 *
 * @param argc                Stores the amount of program parameters.
 * @param file_arr            Array that will store the file pointers to the opened files.
 * @param argv                Name of the program parameters.
 * @return                    -
 */
void file_validation(int argc, FILE *file_arr[], char *argv[]) {

    char *file_option;

    //parameter count validation
    if (argc != 5) {
        menu();
        exit(1);
    }

    //option handler
    if ( strcmp(argv[1], "-encode") == 0) {
        file_option = "w";
    } else if (strcmp(argv[1], "-decode") == 0) {
        file_option = "r";
    } else { menu(); exit(1); }

    //open files
    file_arr[0] = fopen(argv[2], file_option);
    file_arr[1] = fopen(argv[3], "rb");
    file_arr[2] = fopen(argv[4], "wb");

    //file validation
    for (int i = 0; i < 3; i++) {
        if (file_arr[i] == NULL) {
            fprintf(stderr, "\nFILE %d outputs an ERROR!\n\n", i);
            menu();
            exit(1);
        }
    }

}


/**
 * @brief                    Prints the menu
 */
void menu() {
    printf("USAGE:\n");
    printf("huffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
    printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
}

/**
 * @brief                   Converts the option as strings to int values
 *
 *                          -encode = 1
 *                          -decode = 0
 *
 * @param argv              Name of the program parameters.
 * @return                  Returns the option as an int value.
 */
int option_string_to_int(char *argv) {
    int option;
    if ( strcmp(argv, "-encode") == 0) {
        option = 1;
    } else if (strcmp(argv, "-decode") == 0) {
        option = 0;
    } else { menu(); exit(1); }
    return option;
}
