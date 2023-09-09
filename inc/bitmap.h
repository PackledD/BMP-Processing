#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include "pixel.h"

#pragma pack(push, 1)
typedef struct bitmap
{
	pixel_t *data;
	long width;
	long height;
	long psize;  // pixel size
} bitmap_t;
#pragma pack(pop)


int fread_bitmap(bitmap_t *bm, FILE *f);
int fwrite_bitmap(bitmap_t *bm, FILE *f);
bitmap_t *init_bitmap(long width, long height, long psize);
void free_bitmap(bitmap_t *bm);
pixel_t *get_pixel(bitmap_t *bm, int i, int j);
pixel_t *get_pixel_safely(bitmap_t *bm, int i, int j);
int set_pixel(pixel_t *px, bitmap_t *bm, int i, int j);


long get_size_bitmap(bitmap_t *bm);
long get_width_bitmap(bitmap_t *bm);
long get_height_bitmap(bitmap_t *bm);
long get_psize_bitmap(bitmap_t *bm);
pixel_t *get_data_bitmap(bitmap_t *bm);
void set_width_bitmap(bitmap_t *bm, long width);
void set_height_bitmap(bitmap_t *bm, long height);
void set_data_bitmap(bitmap_t *bm, pixel_t *data);
void set_psize_bitmap(bitmap_t *bm, long psize);

#endif
