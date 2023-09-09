#ifndef BITMAP_PROCESS_H
#define BITMAP_PROCESS_H

#include <stdio.h>
#include "bitmap.h"
#include "kernel.h"

int grayscale_bitmap(bitmap_t *bm);
int sobelian_bitmap(bitmap_t *bm);
int set_sobel_bitmap(bitmap_t *bm, bitmap_t *x, bitmap_t *y);
bitmap_t *apply_kernel_bitmap(bitmap_t *bm, kernel_t *k);
pixel_t *apply_kernel_pixel(bitmap_t *bm, kernel_t *k, long i, long j);
int process_bitmap_with_kernel(bitmap_t **bm, kernel_t *(get_kernel)());
int process_bitmap_gaussian(bitmap_t **bm, long size, double deviation);
int filter_bitmap(bitmap_t *bm, int treshold);
int fprocess_bitmap_by_pixel(bitmap_t *bm, FILE *f, int (fproc_pixel)(pixel_t *, FILE *));
int process_bitmap_by_pixel(bitmap_t *bm, int (proc_pixel)(pixel_t *));
bitmap_t *apply_bitmap_median_filter(bitmap_t *bm, long r);
pixel_t *find_median_pixel(bitmap_t *bm, long r, long i, long j);
int process_bitmap_median_filter(bitmap_t **bm, long radius);
typedef unsigned char (get_color_f)(pixel_t *px);
int count_median_pixel_color(bitmap_t *bm, long r, long i, long j, get_color_f *get_color);

#endif
