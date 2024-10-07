#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>


int main(void) {

    //setlocale(LC_ALL, "en_US.utf8");

    /* If your native locale doesn't use UTF-8 encoding
    * you need to replace the empty string with a
    * locale like "en_US.utf8"
    */
    //char *locale = setlocale(LC_ALL, "en_US.utf8");
    FILE *in = fopen("/Users/ludwigfallstrom/Documents/Programmering/DV2/huffman/files/utf_test.txt", "r");

    wint_t c;
    while ((c = fgetwc(in)) != WEOF) {
        //putwchar(c);
        printf("%d \n", c);
    }

    fclose(in);

    //return EXIT_SUCCESS;


}


