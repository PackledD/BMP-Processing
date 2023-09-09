#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <stdio.h>
#include <inttypes.h>

#pragma pack(push, 1)
typedef struct bitmap_file_header
{
	int16_t type;
	int32_t file_size;
	int32_t reserved;
	int32_t off_bits;
} bmp_header_t;
#pragma pack(pop)


int fread_bmp_header(bmp_header_t *head, FILE *f);
int fwrite_bmp_header(bmp_header_t *head, FILE *f);
bmp_header_t *init_header(void);
void free_header(bmp_header_t *head);


int16_t get_type_header(bmp_header_t *head);
int32_t get_file_size_header(bmp_header_t *head);
int32_t get_reserved_header(bmp_header_t *head);
int32_t get_off_bits_header(bmp_header_t *head);
void set_type_header(bmp_header_t *head, int16_t type);
void set_file_size_header(bmp_header_t *head, int32_t file_size);
void set_reserved_header(bmp_header_t *head, int32_t reserved);
void set_off_bits_header(bmp_header_t *head, int32_t off_bits);

#endif
