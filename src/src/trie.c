/*
 * A data type responsible for building a trie, and a huffman table from it. Also operations relevant.
 *
 * For more information see the corresponding .h-file.
 *
 * @author  Ludwig Fallström
 * @since   2020-08-20
 *
 */


#include "trie.h"


void traverse_trie(Trie_node *trie, Table *h_table, bit_buffer *counter);

/**
 * @brief                  Function used for the sorting direction of a priority queue.
 *
 */
int cmp_func(void *val1, void *val2) {
    Trie_node *temp_value1 = (Trie_node*)val1;
    Trie_node *temp_value2 = (Trie_node*)val2;
    return temp_value1->weight - temp_value2->weight;
}

/*
 * print function, used for printing the p_queue.
 * only used for debugging purposes.
 *
 */
void printfunk(void *value) {

    Trie_node *node = (Trie_node*)value;
    printf("%d %d\n", node->label, node->weight);
}


bool node_is_leaf(Trie_node *node) {
    return ( (node->right_child == NULL) && (node->left_child == NULL) );
}


void kill_trie(Trie_node *trie) {

    if (!node_is_leaf(trie)) {
        kill_trie(trie->left_child);
        kill_trie(trie->right_child);
    }
    free(trie);
}


void *initialize_trie_start_values(Table *table) {

    pqueue *priority_queue = pqueue_empty(cmp_func);
    Trie_node *node;
    for(int i = 0; i < BYTE_BUFFER; i++) {
        node = malloc(sizeof(Trie_node));

        node->left_child = NULL;
        node->right_child = NULL;
        node->label = i;
        node->weight = table[i].count;

        //removes all with the count 0
        if (table[i].count != 0) {
            pqueue_insert(priority_queue, node);
        }


    }
    //pqueue_print(priority_queue, printfunk);
    return priority_queue;

}


void build_trie(void *pq) {

     Trie_node *node_holder_for_first_node = pqueue_inspect_first(pq);
    //deletes first node
    pqueue_delete_first(pq);


    if (pqueue_is_empty(pq)) {
        pqueue_insert(pq, node_holder_for_first_node);
    }
    else {
        //allocates memory for the new node
        Trie_node *sum_of_first_and_second_node = malloc(sizeof(Trie_node));

        Trie_node *node_holder_for_second_node = pqueue_inspect_first(pq);

        //deletes second node
        pqueue_delete_first(pq);
        //sums weight
        sum_of_first_and_second_node->weight =
        node_holder_for_first_node->weight + node_holder_for_second_node->weight;

        if (node_holder_for_first_node->weight <= node_holder_for_second_node->weight) {
            sum_of_first_and_second_node->left_child = node_holder_for_first_node;
            sum_of_first_and_second_node->right_child = node_holder_for_second_node;
        }
        else {
            sum_of_first_and_second_node->left_child = node_holder_for_second_node;
            sum_of_first_and_second_node->right_child = node_holder_for_first_node;
        }
        pqueue_insert(pq, sum_of_first_and_second_node);
        //printf("\n");
        //pqueue_print(pq, printfunk);
        //printf("\n");
        build_trie(pq);
    }


}


void fill_h_table(void *pq, Table *h_table) {

    Trie_node *trie = pqueue_inspect_first(pq);

    //place holder
    bit_buffer *place_holder_counter = bit_buffer_empty();
    traverse_trie(trie, h_table, place_holder_counter);
    free(place_holder_counter);
}


/**
 * @brief                  Traverses the trie to find the huffman code for a leaf.
 *
 *                         The trie is traverses recursively to find the huffman code for each leaf.
 *                         The code is than stored as a bit sequence in a huffman table.
 *
 * @param trie             The root for the current trie.
 * @param h_table          The table that the bit sequence will be stored in.
 * @param counter          Temporary bit buffer for storing the code to each leaf.
 */
void traverse_trie(Trie_node *trie, Table *h_table, bit_buffer *counter) {

    if (node_is_leaf(trie)) {
        //copys the counter to the h_table
        h_table[trie->label].bit_sequence = bit_buffer_copy(counter);
        //printf("%d\t", trie->label);
        //printf("%d\t", trie->weight);
        //printf("%s\n\n", counter);
        //bit_buffer_print(counter);
    }
    else {
        bit_buffer *internal_counter = bit_buffer_copy(counter);
        //right
        bit_buffer_insert_bit(internal_counter, 1);
        traverse_trie(trie->right_child, h_table, internal_counter);
        //left
        bit_buffer_insert_bit(counter, 0);
        traverse_trie(trie->left_child, h_table, counter);
    }

}
