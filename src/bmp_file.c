#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bmp_file.h"
#include "bitmap.h"
#include "bmp_header.h"
#include "bmp_info.h"


int init_bmp(bmp_t **bmp)
{
	*bmp = calloc(1, sizeof(bmp_t));
	if (!*bmp)
	{
		return 0;
	}
	(*bmp)->header = init_header();
	(*bmp)->info = init_info();
	(*bmp)->bitmap = NULL;
	return 1;
}


void free_bmp(bmp_t *bmp)
{
	if (!bmp)
	{
		return;
	}
	free_header(get_header_bmp(bmp));
	free_info(get_info_bmp(bmp));
	free_bitmap(get_bitmap_bmp(bmp));
	memset(bmp, 0, sizeof(bmp_t));
	free(bmp);
}


int read_bmp(bmp_t *bmp, char *filename)
{
	if (!bmp || !filename)
	{
		return 0;
	}
	FILE *f = fopen(filename, "rb");
	if (!f)
	{
		return 0;
	}
	int rc = fread_bmp_header(get_header_bmp(bmp), f);
	if (rc)
	{
		rc = fread_bmp_info(get_info_bmp(bmp), f);
		if (rc)
		{
			recalc_bmp_sizes(bmp, f);
			bmp_info_t *info = get_info_bmp(bmp);
			set_bitmap_bmp(bmp, init_bitmap(
				get_width_info(info),
				get_height_info(info),
				get_bit_count_info(info))
			);
			rc = fread_bitmap(get_bitmap_bmp(bmp), f);
		}
	}
	fclose(f);
	return rc;
}


int write_bmp(bmp_t *bmp, char *filename)
{
	FILE *f = fopen(filename, "wb");
	if (!f)
	{
		return 0;
	}
	fwrite_bmp_header(get_header_bmp(bmp), f);
	fwrite_bmp_info(get_info_bmp(bmp), f);
	fwrite_bitmap(get_bitmap_bmp(bmp), f);
	fclose(f);
	return 1;
}


int recalc_bmp_sizes(bmp_t *bmp, FILE *f)
{
	bmp_header_t *head = get_header_bmp(bmp);
	bmp_info_t *info = get_info_bmp(bmp);
	int32_t offset = get_off_bits_header(head);
	fseek(f, offset, SEEK_SET);
	int32_t new_offset = offset + sizeof(bmp_info_t) - get_b_size_info(info);
	int32_t fsize = get_file_size_header(head);
	int32_t new_fsize = fsize + sizeof(bmp_info_t) - get_b_size_info(info);
	set_off_bits_header(head, new_offset);
	set_b_size_info(info, sizeof(bmp_info_t));
	set_file_size_header(head, new_fsize);
	return 1;
}


bmp_header_t *get_header_bmp(bmp_t *bmp)
{
	return bmp->header;
}


bmp_info_t *get_info_bmp(bmp_t *bmp)
{
	return bmp->info;
}


bitmap_t *get_bitmap_bmp(bmp_t *bmp)
{
	return bmp->bitmap;
}


void set_header_bmp(bmp_t *bmp, bmp_header_t *header)
{
	bmp->header = header;
}


void set_info_bmp(bmp_t *bmp, bmp_info_t *info)
{
	bmp->info = info;
}


void set_bitmap_bmp(bmp_t *bmp, bitmap_t *bitmap)
{
	bmp->bitmap = bitmap;
}
