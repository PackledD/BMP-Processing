#ifndef PIXEL_YUV_H
#define PIXEL_YUV_H

#include "pixel.h"

typedef struct pixel_yuv
{
	unsigned char y;
	unsigned char u;
	unsigned char v;
} pixel_yuv_t;


pixel_yuv_t yuv_from_rgb(pixel_t *px);
pixel_t yuv_to_rgb(pixel_yuv_t *px);


unsigned char get_pixel_y(pixel_yuv_t *px);
unsigned char get_pixel_u(pixel_yuv_t *px);
unsigned char get_pixel_v(pixel_yuv_t *px);
void set_pixel_y(pixel_yuv_t *px, unsigned char y);
void set_pixel_u(pixel_yuv_t *px, unsigned char u);
void set_pixel_v(pixel_yuv_t *px, unsigned char v);

#endif
