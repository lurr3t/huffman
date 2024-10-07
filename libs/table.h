/**
 * @defgroup table_h table.
 *
 * @brief A datatype responsible for storing either a frequency table or huffman table.
 *
 * Stores either the byte count on a frequency analysis, or a bit_sequence for a huffman table.
 * Also has operations for creating the table and removing all of the allocated memory associated
 * with the table.
 *
 * @author  Ludwig Fallström
 * @since   2021-08-20
 *
 * @{
 */

#ifndef TABLE_H
#define TABLE_H

#define BYTE_BUFFER 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bit_buffer.h"


/**
 * @brief                A structure used to represent either a frequency table or a huffman table.
 *
 * @elem count           A element that holds a count.
 * @elem bit_sequence    A pointer to a bit_buffer for holding a bit sequence.
 */
typedef struct {
    int count;
    bit_buffer *bit_sequence;
} Table;

/**
 * @brief               Creates table and allocates memory as large as the BYTE_BUFFER.
 *
 *                      User is responsibly for deallocating the memory, using table_kill.
 *
 * @return              A table that has been allocated.
 */
Table *table_create();

/**
 * @brief               Creates table and allocates memory for the bit_sequence element.
 *
 *                      Apart from table_create() it also fills each bit_sequence pointer with an empty bit_buffer.
 *                      User is responsibly for deallocating the memory, using table_kill.
 *
 * @return              A table that has been allocated.
 */
Table *table_create_bit_sequence();

/**
 * @brief               Deallocates all the memory associated to the table.
 *
 * @param table         The table to be deallocated.
 * @return              -
 */
void table_kill(Table *table);

/**
 * @}
 */

#endif /* TABLE */