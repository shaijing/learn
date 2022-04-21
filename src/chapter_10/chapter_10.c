#include "chapter_10/chapter_10.h"
void drive(void) {
    FRPTC *pt;
    pt = test_2;
    char(*str)[5] = pt(4);
    for (int i = 0; i < 4; i++) {
        printf("%s\n", *(str + i));
    }
    free(str);
}
char (*test())[5] {
    cr5* str = malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; ++i) {
        (*str)[i] = 'a';
    }
    (*str)[4] = '\0';
    return str;
}

cr5* test_1() {
    cr5* str = malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; ++i) {
        (*str)[i] = 'a';
    }
    (*str)[4] = '\0';
    return str;
}

char (*test_2(int size))[5] {
    cr5* str = malloc(sizeof(char) * 5 * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 4; j++) {
            (*(str + i))[j] = '0';
        }
        (*(str + i))[5] = '\0';
    }

    return str;
}