#ifndef PIXEL_H
#define PIXEL_H

#include <stdio.h>

typedef struct pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
} pixel_t;


int fread_pixel24(pixel_t *px, FILE *f);
int fwrite_pixel24(pixel_t *px, FILE *f);
int fread_pixel32(pixel_t *px, FILE *f);
int fwrite_pixel32(pixel_t *px, FILE *f);
int make_grey(pixel_t *px);
int filter_pixel(pixel_t *px, int treshold);
int squared_pixel(pixel_t *px, pixel_t *a_px, pixel_t *b_px);

unsigned char get_pixel_b(pixel_t *px);
unsigned char get_pixel_g(pixel_t *px);
unsigned char get_pixel_r(pixel_t *px);
unsigned char get_pixel_a(pixel_t *px);
void set_pixel_b(pixel_t *px, int b);
void set_pixel_g(pixel_t *px, int g);
void set_pixel_r(pixel_t *px, int r);
void set_pixel_a(pixel_t *px, int a);

#endif
