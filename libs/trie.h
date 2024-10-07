/**
 * @defgroup trie_h trie.
 *
 * @brief A datatype responsible for building the trie for huffman encoding and decoding.
 *
 * Has operations for initializing the values before building the trie. Also builds the trie, and fills the
 * huffman table with the encoded bits from the trie. Can also deallocate the memory in the trie built.
 *
 * @author  Ludwig Fallström
 * @since   2021-08-20
 *
 * @{
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bit_buffer.h"
#include "pqueue.h"
#include "freq_analysis.h"
#include "table.h"

/**
 * @brief                           A structure containing a node that the trie is built of.
 *
 * @elem left_child                 A pointer that holds the memory of another node.
 * @elem right_child                A pointer that holds the memory of another node.
 * @elem label                      The value that the node contains.
 * @elem weight                     The weight of the node.
 */
typedef struct trie_node{
    struct trie_node *left_child;
    struct trie_node *right_child;
    int label;
    int weight;
} Trie_node;

//prints values contained in a Trie_node.
void printfunk(void *value);

/**
 * @brief                           Checks if a node is a leaf.
 *
 * @param node                      The node to be checked.
 * @return                          True if the node is a leaf, otherwise false.
 */
bool node_is_leaf(Trie_node *node);

/**
 * @brief                           Deallocates the memory of the nodes in the trie.
 *
 * @param trie                      The trie that will be deallocated.
 * @return                          -
 */
void kill_trie(Trie_node *trie);

/**
 * @brief                           Fills the structure of the trie with it's initializing values.
 *
 *                                  Takes the values from the frequency analysis table and puts them
 *                                  as start values in the priority queue that the trie is built upon.
 *
 *                                  Also allocates memory for each node, so make sure to use kill_trie when
 *                                  done.
 *
 * @param table                     The table that holds the frequency analysis.
 * @return                          A pointer to the priority queue containing the nodes.
 */
void *initialize_trie_start_values(Table *table);

/**
 * @brief                           Builds a trie from the nodes in the priority queue.
 *
 * @param pq                        The priority queue that the trie will be built upon.
 * @return                          Changes the priority queue to only contain the root as an element.
 */
void build_trie(void *pq);


/**
 * @brief                           Traverses the trie and fills the huffman table with encoded bits.
 *
 * @param pq                        Priority queue that holds the root of the trie as an element.
 * @param h_table                   The huffman table to be filled with bit sequences.
 */
void fill_h_table(void *pq, Table *h_table);


/**
 * @}
 */


#endif /* TRIE */
