#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "bmp_file.h"


bmp_info_t *init_info(void)
{
	return calloc(1, sizeof(bmp_info_t));
}


void free_info(bmp_info_t *info)
{
	if (!info)
	{
		return;
	}
	memset(info, 0, sizeof(bmp_info_t));
	free(info);
}


int fread_bmp_info(bmp_info_t *info, FILE *f)
{
	if (!info || !f)
	{
		return 0;
	}
	return fread(info, sizeof(bmp_info_t), 1, f) == 1;
}


int fwrite_bmp_info(bmp_info_t *info, FILE *f)
{
	if (!info || !f)
	{
		return 0;
	}
	size_t size = sizeof(bmp_info_t);
	return fwrite(info, size, 1, f) == 1;
}


int32_t get_b_size_info(bmp_info_t *info)
{
	return info->b_size;
}


int32_t get_width_info(bmp_info_t *info)
{
	return info->width;
}


int32_t get_height_info(bmp_info_t *info)
{
	return info->height;
}


int16_t get_bit_count_info(bmp_info_t *info)
{
	return info->bit_count;
}


void set_b_size_info(bmp_info_t *info, int32_t b_size)
{
	info->b_size = b_size;
}


void set_width_info(bmp_info_t *info, int32_t width)
{
	info->width = width;
}


void set_height_info(bmp_info_t *info, int32_t height)
{
	info->height = height;
}


void set_bit_count_info(bmp_info_t *info, int16_t bit_count)
{
	info->bit_count = bit_count;
}
