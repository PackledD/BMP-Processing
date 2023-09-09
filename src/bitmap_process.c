#include <stdlib.h>
#include <math.h>
#include "bitmap_process.h"
#include "bitmap.h"
#include "pixel.h"
#include "pixel_yuv.h"
#include "kernel.h"

int arr_median(int *arr, int len);
int arr_sort(int *arr, int len);


int grayscale_bitmap(bitmap_t *bm)
{
	if (!bm)
	{
		return 0;
	}
	return process_bitmap_by_pixel(bm, make_grey);
}


int sobelian_bitmap(bitmap_t *bm)
{
	bitmap_t *x = apply_kernel_bitmap(bm, get_sobel_kernel_x());
	if (!x)
	{
		return 0;
	}
	bitmap_t *y = apply_kernel_bitmap(bm, get_sobel_kernel_x());
	if (!y)
	{
		return 0;
	}

	int rc = set_sobel_bitmap(bm, x, y);
	free_bitmap(x);
	free_bitmap(y);
	return rc;
}


int set_sobel_bitmap(bitmap_t *bm, bitmap_t *x, bitmap_t *y)
{
	if (!bm || !x || !y)
	{
		return 0;
	}
	for (long i = 0; i < labs(get_height_bitmap(bm)); i++)
	{
		for (long j = 0; j < labs(get_width_bitmap(bm)); j++)
		{
			pixel_t *px_cur = get_pixel(bm, i, j);
			pixel_t *p_x = get_pixel(x, i, j);
			pixel_t *p_y = get_pixel(x, i, j);
			squared_pixel(px_cur, p_x, p_y);
			set_pixel(px_cur, bm, i, j);
		}
	}
	return 1;
}


bitmap_t *apply_kernel_bitmap(bitmap_t *bm, kernel_t *k)
{
	if (!bm)
	{
		return NULL;
	}
	bitmap_t *new_bm = init_bitmap(get_width_bitmap(bm), get_height_bitmap(bm), get_psize_bitmap(bm));
	if (!new_bm)
	{
		return NULL;
	}
	int rc = 1;
	for (long i = 0; rc && i < labs(get_height_bitmap(bm)); i++)
	{
		for (long j = 0; rc && j < labs(get_width_bitmap(bm)); j++)
		{
			pixel_t *new_px = apply_kernel_pixel(bm, k, i, j);
			if (new_px)
			{
				set_pixel(new_px, new_bm, i, j);
				free(new_px);
			}
			else
			{
				free_bitmap(new_bm);
				new_bm = NULL;
				rc = 0;
			}
		}
	}
	return new_bm;
}


pixel_t *apply_kernel_pixel(bitmap_t *bm, kernel_t *k, long i, long j)
{
	pixel_t *res = calloc(1, sizeof(pixel_t));
	if (!res)
	{
		return NULL;
	}
	int color_r = 0;
	int color_g = 0;
	int color_b = 0;
	long size = get_size_kernel(k) / 2;
	for (long i1 = -size; i1 <= size; i1++)
	{
		for (long j1 = -size; j1 <= size; j1++)
		{
			pixel_t *cur = get_pixel_safely(bm, i + i1, j + j1);
			double *k_data = get_kernel_elem(k, size + i1, size + j1);
			color_r += (int)(get_pixel_r(cur) * (*k_data));
			color_g += (int)(get_pixel_g(cur) * (*k_data));
			color_b += (int)(get_pixel_b(cur) * (*k_data));
		}
	}
	set_pixel_b(res, color_b);
	set_pixel_g(res, color_g);
	set_pixel_r(res, color_r);
	set_pixel_a(res, 255);
	return res;
}


int process_bitmap_with_kernel(bitmap_t **bm, kernel_t *(get_kernel)())
{
	if (!bm || !*bm)
	{
		return 0;
	}
	kernel_t *k = get_kernel();
	int rc = 0;
	if (k)
	{
		bitmap_t *new = apply_kernel_bitmap(*bm, k);
		free_kernel(k);
		if (new)
		{
			free_bitmap(*bm);
			*bm = new;
			rc = 1;
		}
	}
	return rc;
}


int process_bitmap_gaussian(bitmap_t **bm, long size, double deviation)
{
	if (!bm || !*bm)
	{
		return 0;
	}
	kernel_t *k = get_gauss_kernel(size, deviation);
	int rc = 0;
	if (k)
	{
		bitmap_t *new = apply_kernel_bitmap(*bm, k);
		free_kernel(k);
		if (new)
		{
			free_bitmap(*bm);
			*bm = new;
			rc = 1;
		}
	}
	return rc;
}


int filter_bitmap(bitmap_t *bm, int treshold)
{
	int rc = 1;
	for (long i = 0; rc && i < labs(get_height_bitmap(bm)); i++)
	{
		for (long j = 0; rc && j < labs(get_width_bitmap(bm)); j++)
		{
			rc = filter_pixel(get_pixel(bm, i, j), treshold);
		}
	}
	return rc;
}


int fprocess_bitmap_by_pixel(bitmap_t *bm, FILE *f, int (fproc_pixel)(pixel_t *, FILE *))
{
	int rc = 1;
	for (long i = 0; rc && i < labs(get_height_bitmap(bm)); i++)
	{
		long beg = ftell(f);
		for (long j = 0; rc && j < labs(get_width_bitmap(bm)); j++)
		{
			rc = fproc_pixel(get_pixel(bm, i, j), f);
		}
		long end = ftell(f);
		long diff = (end - beg) % 4;
		if (diff)
		{
			fseek(f, 4 - diff, SEEK_CUR);
		}
	}
	return rc;
}


int process_bitmap_by_pixel(bitmap_t *bm, int (proc_pixel)(pixel_t *))
{
	int rc = 1;
	for (long i = 0; rc && i < labs(get_height_bitmap(bm)); i++)
	{
		for (long j = 0; rc && j < labs(get_width_bitmap(bm)); j++)
		{
			rc = proc_pixel(get_pixel(bm, i, j));
		}
	}
	return rc;
}


int process_bitmap_median_filter(bitmap_t **bm, long radius)
{
	if (!bm || !*bm)
	{
		return 0;
	}
	int rc = 0;
	bitmap_t *new = apply_bitmap_median_filter(*bm, radius);
	if (new)
	{
		free_bitmap(*bm);
		*bm = new;
		rc = 1;
	}
	return rc;
}


bitmap_t *apply_bitmap_median_filter(bitmap_t *bm, long radius)
{
	if (!bm)
	{
		return 0;
	}
	bitmap_t *new_bm = init_bitmap(get_width_bitmap(bm), get_height_bitmap(bm), get_psize_bitmap(bm));
	if (!new_bm)
	{
		return NULL;
	}
	int rc = 1;
	for (long i = 0; rc && i < labs(get_height_bitmap(bm)); i++)
	{
		for (long j = 0; rc && j < labs(get_width_bitmap(bm)); j++)
		{
			pixel_t *new_px = find_median_pixel(bm, radius, i, j);
			if (new_px)
			{
				set_pixel(new_px, new_bm, i, j);
				free(new_px);
			}
			else
			{
				free_bitmap(new_bm);
				new_bm = NULL;
				rc = 0;
			}
		}
	}
	return new_bm;
}


pixel_t *find_median_pixel(bitmap_t *bm, long radius, long i, long j)
{
	pixel_t *res = calloc(1, sizeof(pixel_t));
	if (!res)
	{
		return NULL;
	}
	set_pixel_b(res, count_median_pixel_color(bm, radius, i, j, get_pixel_b));
	set_pixel_g(res, count_median_pixel_color(bm, radius, i, j, get_pixel_g));
	set_pixel_r(res, count_median_pixel_color(bm, radius, i, j, get_pixel_r));
	return res;
}


int count_median_pixel_color(bitmap_t *bm, long radius, long i, long j, get_color_f *get_color)
{
	if (!bm || !get_color)
	{
		return 0;
	}
	int size = (2 * radius + 1) * (2 * radius + 1);
	int *colors = calloc(size, sizeof(int));
	if (!colors)
	{
		return 0;
	}
	int c = 0;
	for (long i1 = -radius; i1 <= radius; i1++)
	{
		for (long j1 = -radius; j1 <= radius; j1++)
		{
			pixel_t *cur = get_pixel_safely(bm, i + i1, j + j1);
			colors[c++] = get_color(cur);
		}
	}
	return arr_median(colors, size);
}


int arr_sort(int *arr, int len)
{
	if (!arr)
	{
		return 0;
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (arr[i] > arr[j])
			{
				int buff = arr[i];
				arr[i] = arr[j];
				arr[j] = buff;
			}
		}
	}
	return 1;
}


int arr_median(int *arr, int len)
{
	arr_sort(arr, len);
	if (len % 2 == 1)
		return arr[len / 2];
	else
		return (arr[len / 2] + arr[len / 2 - 1]) / 2;
}
