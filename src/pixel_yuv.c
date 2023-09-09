#include "pixel_yuv.h"
#include "pixel.h"


pixel_yuv_t yuv_from_rgb(pixel_t *px)
{
	unsigned char y, u, v;
	double Kr = 0.299, Kb = 0.114;
	y = (int)(Kr * get_pixel_r(px) + (1 - Kb - Kr) * get_pixel_g(px) + Kb * get_pixel_b(px));
	u = get_pixel_b(px) - y;
	v = get_pixel_r(px) - y;
	pixel_yuv_t res;
	set_pixel_y(&res, y);
	set_pixel_u(&res, u);
	set_pixel_v(&res, v);
	return res;
}


pixel_t yuv_to_rgb(pixel_yuv_t *px)
{
	unsigned char r, g, b;
	double Kr = 0.299, Kb = 0.114;
	r = get_pixel_y(px) + get_pixel_v(px);
	g = get_pixel_y(px) - (int)((Kr * get_pixel_v(px) + Kb * get_pixel_u(px)) / (1 - Kb - Kr));
	b = get_pixel_y(px) + get_pixel_u(px);
	pixel_t res;
	set_pixel_r(&res, r);
	set_pixel_g(&res, g);
	set_pixel_b(&res, b);
	return res;
}


unsigned char get_pixel_y(pixel_yuv_t *px)
{
	return px->y;
}


unsigned char get_pixel_u(pixel_yuv_t *px)
{
	return px->u;
}


unsigned char get_pixel_v(pixel_yuv_t *px)
{
	return px->v;
}


void set_pixel_y(pixel_yuv_t *px, unsigned char y)
{
	px->y = y;
}


void set_pixel_u(pixel_yuv_t *px, unsigned char u)
{
	px->u = u;
}


void set_pixel_v(pixel_yuv_t *px, unsigned char v)
{
	px->v = v;
}
