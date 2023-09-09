#ifndef BMP_FILE_PROCESS_H
#define BMP_FILE_PROCESS_H

#include "bmp_file.h"

int grayscale(bmp_t *bmp);
int sobelian_x(bmp_t *bmp);
int sobelian_y(bmp_t *bmp);
int sobelian(bmp_t *bmp);
int laplasian_pos(bmp_t *bmp);
int laplasian_neg(bmp_t *bmp);
int laplasian_diag(bmp_t *bmp);
int gaussian(bmp_t *bmp, long radius, double deviation);
int border_highlight(bmp_t *bmp, int treshold);
int median_filter(bmp_t *bmp, int radius);

#endif
