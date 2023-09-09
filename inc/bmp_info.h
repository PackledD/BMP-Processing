#ifndef BMP_INFO_H
#define BMP_INFO_H

#include <stdio.h>
#include <inttypes.h>

#pragma pack(push, 1)
typedef struct bitmap_info
{
	int32_t b_size;
	int32_t width;
	int32_t height;
	int16_t planes;
	int16_t bit_count;
	int32_t compression;
	int32_t size_image;
	int32_t x_pels_per_meter;
	int32_t y_pels_per_meter;
	int32_t clr_used;
	int32_t clr_important;
} bmp_info_t;
#pragma pack(pop)


int fread_bmp_info(bmp_info_t *info, FILE *f);
int fwrite_bmp_info(bmp_info_t *info, FILE *f);
bmp_info_t *init_info(void);
void free_info(bmp_info_t *info);


int32_t get_b_size_info(bmp_info_t *info);
int32_t get_width_info(bmp_info_t *info);
int32_t get_height_info(bmp_info_t *info);
int16_t get_bit_count_info(bmp_info_t *info);
void set_b_size_info(bmp_info_t *info, int32_t b_size);
void set_width_info(bmp_info_t *info, int32_t width);
void set_height_info(bmp_info_t *info, int32_t height);
void set_bit_count_info(bmp_info_t *info, int16_t bit_count);

#endif
