#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "bmp_header.h"


bmp_header_t *init_header(void)
{
	return calloc(1, sizeof(bmp_header_t));
}


void free_header(bmp_header_t *head)
{
	if (!head)
	{
		return;
	}
	memset(head, 0, sizeof(bmp_header_t));
	free(head);
}


int fread_bmp_header(bmp_header_t *head, FILE *f)
{
	if (!head || !f)
	{
		return 0;
	}
	return fread(head, sizeof(bmp_header_t), 1, f) == 1;
}


int fwrite_bmp_header(bmp_header_t *head, FILE *f)
{
	if (!head || !f)
	{
		return 0;
	}
	size_t size = sizeof(bmp_header_t);
	return fwrite(head, size, 1, f) == 1;
}


int16_t get_type_header(bmp_header_t *head)
{
	return head->type;
}


int32_t get_file_size_header(bmp_header_t *head)
{
	return head->file_size;
}


int32_t get_reserved_header(bmp_header_t *head)
{
	return head->reserved;
}


int32_t get_off_bits_header(bmp_header_t *head)
{
	return head->off_bits;
}


void set_type_header(bmp_header_t *head, int16_t type)
{
	head->type = type;
}


void set_file_size_header(bmp_header_t *head, int32_t file_size)
{
	head->file_size = file_size;
}


void set_reserved_header(bmp_header_t *head, int32_t reserved)
{
	head->reserved = reserved;
}


void set_off_bits_header(bmp_header_t *head, int32_t off_bits)
{
	head->off_bits = off_bits;
}
