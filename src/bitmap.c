#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bitmap.h"
#include "bitmap_process.h"
#include "pixel.h"


bitmap_t *init_bitmap(long width, long height, long psize)
{
	if (!width || !height)
	{
		return NULL;
	}
	bitmap_t *res = calloc(1, sizeof(bitmap_t));
	if (!res)
	{
		return NULL;
	}
	set_width_bitmap(res, width);
	set_height_bitmap(res, height);
	set_psize_bitmap(res, psize);
	set_data_bitmap(res, calloc(get_size_bitmap(res), sizeof(pixel_t)));
	if (!get_data_bitmap(res))
	{
		free_bitmap(res);
		res = NULL;
	}
	return res;
}


void free_bitmap(bitmap_t *bm)
{
	if (!bm)
	{
		return;
	}
	free(get_data_bitmap(bm));
	memset(bm, 0, sizeof(bitmap_t));
	free(bm);
}


int fread_bitmap(bitmap_t *bm, FILE *f)
{
	if (!bm || !f)
	{
		return 0;
	}
	int rc = 1;
	if (get_psize_bitmap(bm) == 24)
	{
		rc = fprocess_bitmap_by_pixel(bm, f, fread_pixel24);
	}
	else if (get_psize_bitmap(bm) == 32)
	{
		rc = fprocess_bitmap_by_pixel(bm, f, fread_pixel32);
	}
	else
	{
		rc = 0;
	}
	return rc;
}


int fwrite_bitmap(bitmap_t *bm, FILE *f)
{
	if (!bm || !f)
	{
		return 0;
	}
	int rc = 1;
	if (get_psize_bitmap(bm) == 24)
	{
		rc = fprocess_bitmap_by_pixel(bm, f, fwrite_pixel24);
	}
	else if (get_psize_bitmap(bm) == 32)
	{
		rc = fprocess_bitmap_by_pixel(bm, f, fwrite_pixel32);
	}
	else
	{
		rc = 0;
	}
	return rc;
}


pixel_t *get_pixel(bitmap_t *bm, int i, int j)
{
	if (!bm || i < 0 || j < 0)
	{
		return NULL;
	}
	long width = get_width_bitmap(bm);
	long height = get_height_bitmap(bm);
	if (i >= labs(height) || j >= labs(width))
	{
		return NULL;
	}
	if (width < 0)
	{
		width = -width;
		j = width - j - 1;
	}
	if (height < 0)
	{
		height = -height;
		i = height - i - 1;
	}
	return &(get_data_bitmap(bm)[j + width * i]);
}


pixel_t *get_pixel_safely(bitmap_t *bm, int i, int j)
{
	if (i < 0)
	{
		i = 0;
	}
	if (j < 0)
	{
		j = 0;
	}
	long width = get_width_bitmap(bm);
	long height = get_height_bitmap(bm);
	if (i >= labs(height))
	{
		i = labs(height) - 1;
	}
	if (j >= labs(width))
	{
		j = labs(width) - 1;
	}
	return get_pixel(bm, i, j);
}


int set_pixel(pixel_t *px, bitmap_t *bm, int i, int j)
{
	if (!px || !bm || i < 0 || j < 0)
	{
		return 0;
	}
	long width = labs(get_width_bitmap(bm));
	long height = labs(get_height_bitmap(bm));
	if (i > height || j > width)
	{
		return 0;
	}
	get_data_bitmap(bm)[j + width * i] = *px;
	return 1;
}


long get_size_bitmap(bitmap_t *bm)
{
	if (!bm)
	{
		return -1;
	}
	return labs(get_width_bitmap(bm) * get_height_bitmap(bm));
}


long get_width_bitmap(bitmap_t *bm)
{
	return bm->width;
}


long get_height_bitmap(bitmap_t *bm)
{
	return bm->height;
}


long get_psize_bitmap(bitmap_t *bm)
{
	return bm->psize;
}


pixel_t *get_data_bitmap(bitmap_t *bm)
{
	return bm->data;
}


void set_width_bitmap(bitmap_t *bm, long width)
{
	bm->width = width;
}


void set_height_bitmap(bitmap_t *bm, long height)
{
	bm->height = height;
}


void set_data_bitmap(bitmap_t *bm, pixel_t *data)
{
	bm->data = data;
}


void set_psize_bitmap(bitmap_t *bm, long psize)
{
	bm->psize = psize;
}
