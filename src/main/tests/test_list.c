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

void menu();

int main(int argc, char *argv[]) {

    //list for holding the byte sequence, so it can be read again
    list *byte_sequence = list_empty();

    int char_arr[3] = {2, 3, 4};

    list_position pos = list_first(byte_sequence);
    pos = list_insert(byte_sequence, pos, &char_arr[0]) ;
    pos = list_insert(byte_sequence, pos, &char_arr[1]);
    list_insert(byte_sequence, pos, &char_arr[2]);

    pos = list_previous(byte_sequence, list_end(byte_sequence));
    pos = list_previous(byte_sequence, pos);
    pos = list_previous(byte_sequence, pos);
    int *value = list_inspect(byte_sequence,  pos);
    printf("%d", *value);






    return 0;

}
