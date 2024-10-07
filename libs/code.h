/**
 * @defgroup code_h encoding / decoding
 *
 * @brief A data type responsible for the encoding and decoding part in huffman encoding.
 *
 * This datatype is responsible for writing the encoded bits from a huffman-table that corresponds to it's
 * byte value in the input file, to a file.
 * It is also responsible for decoding that same file to get the original byte values.
 *
 * @author  Ludwig Fallström
 * @since   2021-08-20
 *
 * @{
 */

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "freq_analysis.h"
#include "trie.h"
#include "list.h"
#include "code.h"

/**
 * @brief                       Responsible for writing the encoded bits stored in the huffman table
 *                              to a file.
 *
 * @param h_table               The huffman table that the bit_sequences is stored in.
 * @param input_file            The file to be encoded.
 * @param output_file           The file that the huffman encoding will be stored on.
 * @param input_file_name       Name of the input file.
 */
void encode(Table *h_table, FILE *input_file, FILE *output_file, char *input_file_name);

/**
 * @brief                       Responsible for decoding the file that the huffman encoding is stored on.
 *
 * @param trie                  The trie that will be traversed to find the original byte values.
 * @param input_file            The encoded file that will be decoded.
 * @param output_file           The file that will store the decoded bytes.
 * @return                      -
 */
void decode(Trie_node *trie, FILE *input_file, FILE *output_file);

/**
 * @}
 */

#endif /* CODE_H */
