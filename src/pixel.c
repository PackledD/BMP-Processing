#include <stdio.h>
#include <math.h>
#include "pixel.h"
#include "pixel_yuv.h"


int fread_pixel24(pixel_t *px, FILE *f)
{
	if (!px || !f)
	{
		return 0;
	}
	unsigned char b, g, r;
	int rc = 0;
	rc += fread(&b, 1, 1, f);
	rc += fread(&g, 1, 1, f);
	rc += fread(&r, 1, 1, f);
	if (rc == 3)
	{
		set_pixel_b(px, b);
		set_pixel_g(px, g);
		set_pixel_r(px, r);
		set_pixel_a(px, 255);
	}
	return rc == 3;
}


int fwrite_pixel24(pixel_t *px, FILE *f)
{
	if (!px || !f)
	{
		return 0;
	}
	unsigned char b, g, r;
	b = get_pixel_b(px);
	g = get_pixel_g(px);
	r = get_pixel_r(px);
	int rc = 0;
	rc += fwrite(&b, 1, 1, f);
	rc += fwrite(&g, 1, 1, f);
	rc += fwrite(&r, 1, 1, f);
	return rc == 3;
}


int fread_pixel32(pixel_t *px, FILE *f)
{
	if (!px || !f)
	{
		return 0;
	}
	return fread(px, sizeof(pixel_t), 1, f) == 1;
}


int fwrite_pixel32(pixel_t *px, FILE *f)
{
	if (!px || !f)
	{
		return 0;
	}
	return fwrite(px, sizeof(pixel_t), 1, f) == 1;
}


int make_grey(pixel_t *px)
{
	if (!px)
	{
		return 0;
	}
	pixel_yuv_t new_px = yuv_from_rgb(px);
	set_pixel_b(px, get_pixel_y(&new_px));
	set_pixel_g(px, get_pixel_y(&new_px));
	set_pixel_r(px, get_pixel_y(&new_px));
	return 1;
}


int filter_pixel(pixel_t *px, int treshold)
{
	if (!px)
	{
		return 0;
	}
	pixel_yuv_t yuv = yuv_from_rgb(px);
	int color = 0;
	if (get_pixel_y(&yuv) > treshold)
	{
		color = 255;
	}
	set_pixel_b(px, color);
	set_pixel_g(px, color);
	set_pixel_r(px, color);
	return 1;
}


int squared_pixel(pixel_t *px, pixel_t *a_px, pixel_t *b_px)
{
	if (!px || !a_px || !b_px)
	{
		return 0;
	}
	int b, g, r;
	b = (int)sqrt(get_pixel_b(a_px) * get_pixel_b(a_px) + get_pixel_b(b_px) * get_pixel_b(b_px));
	g = (int)sqrt(get_pixel_g(a_px) * get_pixel_g(a_px) + get_pixel_g(b_px) * get_pixel_g(b_px));
	r = (int)sqrt(get_pixel_r(a_px) * get_pixel_r(a_px) + get_pixel_r(b_px) * get_pixel_r(b_px));
	set_pixel_b(px, b);
	set_pixel_g(px, g);
	set_pixel_r(px, r);
	return 1;
}


unsigned char get_pixel_b(pixel_t *px)
{
	return px->b;
}


unsigned char get_pixel_g(pixel_t *px)
{
	return px->g;
}


unsigned char get_pixel_r(pixel_t *px)
{
	return px->r;
}


unsigned char get_pixel_a(pixel_t *px)
{
	return px->a;
}


void set_pixel_b(pixel_t *px, int b)
{
	if (b > 255)
	{
		b = 255;
	}
	else if (b < 0)
	{
		b = 0;
	}
	px->b = b;
}


void set_pixel_g(pixel_t *px, int g)
{
	if (g > 255)
	{
		g = 255;
	}
	else if (g < 0)
	{
		g = 0;
	}
	px->g = g;
}


void set_pixel_r(pixel_t *px, int r)
{
	if (r > 255)
	{
		r = 255;
	}
	else if (r < 0)
	{
		r = 0;
	}
	px->r = r;
}


void set_pixel_a(pixel_t *px, int a)
{
	if (a > 255)
	{
		a = 255;
	}
	else if (a < 0)
	{
		a = 0;
	}
	px->a = a;
}
