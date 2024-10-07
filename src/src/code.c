/*
 * A data type for encoding and decoding in huffman.
 *
 * For more information see the corresponding .h-file.
 *
 * @author  Ludwig Fallström
 * @since   2020-08-20
 *
 */

#include <wchar.h>
#include <locale.h>
#include "code.h"


void concat_bit_sequence(int index, Table *h_table, bit_buffer *complete_bit_sequence);

void encode(Table *h_table, FILE *input_file, FILE *output_file, char *input_file_name) {

    //for printing the amount of bytes before encoding
    bit_buffer *original_bytes = bit_buffer_empty();
    bit_buffer *complete_bit_sequence = bit_buffer_empty();

    //reads from file and and fills complete_bit_sequence
    wint_t ch;
    while ((ch = fgetwc(input_file)) != WEOF) {
        //bit_buffer_print(h_table[ch].bit_sequence);
        bit_buffer_insert_byte(original_bytes, ch);
        concat_bit_sequence(ch, h_table, complete_bit_sequence);

    }

    //add eot
    //bit_buffer_insert_byte(complete_bit_sequence, 4);


    //bit_buffer_print(complete_bit_sequence);

    char *byte_array = bit_buffer_to_byte_array(complete_bit_sequence);

    fwrite(byte_array, bit_buffer_size(complete_bit_sequence) / 8, 1, output_file);
    printf("%d bytes read from %s.\n", (bit_buffer_size(original_bytes) / 8), input_file_name);
    printf("%d bytes used in encoded form.\n", bit_buffer_size(complete_bit_sequence) / 8);
    free(byte_array);
    bit_buffer_free(complete_bit_sequence);
    bit_buffer_free(original_bytes);
}

void decode(Trie_node *trie, FILE *input_file, FILE *output_file) {

    bit_buffer *complete_bit_sequence = bit_buffer_empty();

    //reads from file
    wint_t byte;
    while ((byte = fgetwc(input_file)) != WEOF) {
        bit_buffer_insert_byte(complete_bit_sequence, byte);
    }

    //bit_buffer_print(complete_bit_sequence);

    //gets the only element from the queue
    Trie_node *root = pqueue_inspect_first((void*)trie);

    Trie_node *current_node = root;

    //traverses trie for finding the leafs labels, holding the original byte
    while (bit_buffer_size(complete_bit_sequence) > 0) {

        if (node_is_leaf(current_node)) {
            fputc(current_node->label, output_file);
            current_node = root;
        }

        if (bit_buffer_remove_bit(complete_bit_sequence) == 1) {
            //makes sure that the child isn't null
            if (current_node->right_child != NULL) {
                current_node = current_node->right_child;
            }
        } else {
            if (current_node->left_child != NULL) {
                current_node = current_node->left_child;
            }
        }


    }
    printf("File decoded succesfully.");
}


/**
 * @brief                           Takes bit sequences from the huffman table and adds them together.
 *
 * @param index                     Used to access a specific index in the huffman table.
 * @param h_table                   Huffman table storing bit sequences.
 * @param complete_bit_sequence     The bit sequence that will hold the complete encoded bit sequence.
 */
void concat_bit_sequence(int index, Table *h_table, bit_buffer *complete_bit_sequence) {

    bit_buffer *bit_sequence = h_table[index].bit_sequence;

    int size_of_buffer = bit_buffer_size(bit_sequence);
    //goes through the amount of bits stored in the bit_buffer, and is added to the complete_bit_sequence
    for (int i = 0; i < size_of_buffer; i++) {
        int bit = bit_buffer_inspect_bit(bit_sequence, i);
        bit_buffer_insert_bit(complete_bit_sequence, bit);
    }

}

