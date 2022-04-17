#ifndef C_CHAPTER_10_H
#define C_CHAPTER_10_H
#include<stdio.h>
#include<stdlib.h>
void drive_10(void);
/**
 * @Brief :
 * 把FRPTC声明为一个函数类型，
 * 该函数返回一个指针，
 * 该指针指向内含5个char类型元素的数组
 * @return char *
 */
typedef char (*FRPTC())[5];

typedef char cr5[5];

/**
 * @Brief : 效果与FRPTC一样
 * @return cr5*
 */
cr5* (*FRPTC_1)();


char (*test())[5];


typedef char (*FRPTC_2(int))[5];
char (*test_2(int))[5];
#endif  // C_CHAPTER_10_H