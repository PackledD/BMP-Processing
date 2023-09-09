#include "bmp_file_process.h"
#include "bmp_file.h"
#include "bitmap_process.h"
#include "kernel.h"


int base_process_with_kernel(bmp_t *bmp, kernel_t *(get_kernel)());
int filter_bmp(bmp_t *bmp, int treshold);

int grayscale(bmp_t *bmp)
{
	if (!bmp)
	{
		return 0;
	}
	return grayscale_bitmap(get_bitmap_bmp(bmp));
}


int sobelian_x(bmp_t *bmp)
{
	return base_process_with_kernel(bmp, get_sobel_kernel_x);
}


int sobelian_y(bmp_t *bmp)
{
	return base_process_with_kernel(bmp, get_sobel_kernel_y);
}


int sobelian(bmp_t *bmp)
{
	return sobelian_bitmap(get_bitmap_bmp(bmp));
}


int laplasian_pos(bmp_t *bmp)
{
	return base_process_with_kernel(bmp, get_laplas_kernel_pos);
}


int laplasian_neg(bmp_t *bmp)
{
	return base_process_with_kernel(bmp, get_laplas_kernel_neg);
}


int laplasian_diag(bmp_t *bmp)
{
	return base_process_with_kernel(bmp, get_laplas_kernel_diag);
}


int base_process_with_kernel(bmp_t *bmp, kernel_t *(get_kernel)())
{
	if (!bmp)
	{
		return 0;
	}
	bitmap_t *bm = get_bitmap_bmp(bmp);
	int rc = process_bitmap_with_kernel(&bm, get_kernel);
	set_bitmap_bmp(bmp, bm);
	return rc;
}


int gaussian(bmp_t *bmp, long radius, double deviation)
{
	if (!bmp)
	{
		return 0;
	}
	bitmap_t *bm = get_bitmap_bmp(bmp);
	int rc = process_bitmap_gaussian(&bm, 2 * radius + 1, deviation);
	set_bitmap_bmp(bmp, bm);
	return rc;
}


int filter_bmp(bmp_t *bmp, int treshold)
{
	return filter_bitmap(get_bitmap_bmp(bmp), treshold);
}


int border_highlight(bmp_t *bmp, int treshold)
{
	grayscale(bmp);
	gaussian(bmp, 2, 4);
	laplasian_diag(bmp);
	filter_bmp(bmp, treshold);
	return 1;
}


int median_filter(bmp_t *bmp, int radius)
{
	if (!bmp)
	{
		return 0;
	}
	bitmap_t *bm = get_bitmap_bmp(bmp);
	int rc = process_bitmap_median_filter(&bm, radius);
	set_bitmap_bmp(bmp, bm);
	return rc;
}
