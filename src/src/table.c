/*
 * A data type for storing either a frequency table or huffman table.
 *
 * For more information see the corresponding .h-file.
 *
 * @author  Ludwig Fallström
 * @since   2020-08-20
 *
 */

#include "table.h"


Table *table_create() {
    return calloc(BYTE_BUFFER, sizeof(Table));
}

Table *table_create_bit_sequence() {

    Table *table = table_create();
    for (int i = 0; i < BYTE_BUFFER; i++) {
        table[i].bit_sequence = bit_buffer_empty();
    }
    return table;
}

void table_kill(Table *table) {
    for (int i = 0; i < BYTE_BUFFER; i++) {
        if (table[i].bit_sequence != NULL) {
            bit_buffer_free(table[i].bit_sequence);
        }
    }
    free(table);
}




