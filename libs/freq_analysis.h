/**
 * @defgroup freq_analysis_h frequency analysis.
 *
 * @brief A datatype responsible for doing a frequency analysis on bytes from an input file.
 *
 * According to which option has been chosen different things will happen.
 *
 * -encode : The bytes from the input file will be counted and put into a table. The analysis will also
 * be stored in a separate file.
 *
 * -decode : The analysis that is stored in a file will be loaded to the frequency table.
 *
 * @author  Ludwig Fallström
 * @since   2021-08-20
 *
 * @{
 */

#ifndef FREQ_ANALYSIS_H
#define FREQ_ANALYSIS_H

#define BYTE_BUFFER 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bit_buffer.h"
#include "table.h"

/**
 * @brief                     Does the frequency analysis.
 *
 *                            -encode : The bytes from the input file will be counted and put into a table.
 *                            The analysis will also be stored in a separate file.
 *
 *                            -decode : The analysis that is stored in a file will be loaded to the frequency table.
 *
 *                            Also allocates memory for the table that stores the frequency table. Up to the user to
 *                            free the memory.
 *
 * @param option              1 == -encode | 0 == -decode.
 * @param f_table_file        Output file for storing the frequency analysis.
 * @param input_file          The file that the analysis will be done upon.
 * @return                    Table storing the frequency analysis.
 */
Table *frequency_analysis(int option, FILE *f_table_file, FILE *input_file);

//prints the freq_table, testing purposes only
void print_table(Table *table);


/**
 * @}
 */

#endif /* FREQ_ANALYSIS */
