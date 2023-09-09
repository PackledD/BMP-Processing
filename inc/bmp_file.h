#ifndef BMP_FILE_H
#define BMP_FILE_H

#include "bitmap.h"
#include "bmp_header.h"
#include "bmp_info.h"

typedef struct bmp_file
{
	bmp_header_t *header;
	bmp_info_t *info;
	bitmap_t *bitmap;
} bmp_t;


int read_bmp(bmp_t *bmp, char *filename);
int write_bmp(bmp_t *bmp, char *filename);
int init_bmp(bmp_t **bmp);
void free_bmp(bmp_t *bmp);
int recalc_bmp_sizes(bmp_t *bmp, FILE *f);


bmp_header_t *get_header_bmp(bmp_t *bmp);
bmp_info_t *get_info_bmp(bmp_t *bmp);
bitmap_t *get_bitmap_bmp(bmp_t *bmp);
void set_header_bmp(bmp_t *bmp, bmp_header_t *header);
void set_info_bmp(bmp_t *bmp, bmp_info_t *info);
void set_bitmap_bmp(bmp_t *bmp, bitmap_t *bitmap);

#endif
