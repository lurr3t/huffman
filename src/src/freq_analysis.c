/*
 * A data type for doing a frequency analysis.
 *
 * For more information see the corresponding .h-file.
 *
 * @author  Ludwig Fallström
 * @since   2020-08-20
 *
 */

#include <wchar.h>
#include <locale.h>

#include "freq_analysis.h"


static Table *encode_option(Table *table, FILE *f_table_file, FILE *input_file);
static Table *decode_option(Table *table, FILE *f_table_file);


Table *frequency_analysis(int option, FILE *f_table_file, FILE *input_file) {

    Table *table = table_create();

    if (option) {
        table = encode_option(table, f_table_file, input_file);
    } else {
        table = decode_option(table, f_table_file);
    }
    return table;

}

/**
 * @brief                      Does a frequency analysis on the input file.
 *
 *                             Does frequency analysis and stores it in a file and
 *                             a table.
 *
 * @param table                The table that the analysis will be stored in.
 * @param f_table_file         The file that the analysis will be stored in.
 * @param input_file           The file that the analysis will be done upon.
 * @return                     A table containing the frequency analysis.
 */
static Table *encode_option(Table *table, FILE *f_table_file, FILE *input_file) {

    wint_t ch;
    while ((ch = fgetwc(input_file)) != WEOF) {
        //printf("%d\n", ch);
        table[(size_t)ch].count++;

    }

    //skriver frekvenstabellen till fil 0
    for (int i = 0; i < BYTE_BUFFER; i++) {
        fprintf(f_table_file, "%d\n", table[i].count);
    }

    return table;
}

/**
 * @brief                      Loads the frequency analysis from a file to a table.
 *
 * @param table                The table that the analysis will be stored in.
 * @param f_table_file         The file that the analysis will be stored in.
 * @return                     A table containing the frequency analysis.
 */
static Table *decode_option(Table *table, FILE *f_table_file) {

    for (int i = 0; i < BYTE_BUFFER; i++) {
        fscanf(f_table_file, "%d", &table[i].count);
    }

    return table;
}


// only for testing purposes
void print_table(Table *table) {

    //ch only prints ascii,
    for (int i = 0; i < BYTE_BUFFER; i++) {
        printf("ch: %c val: %d\tcount: %d\n", i, i, table[i].count);
    }

}
