#include <stdlib.h>
#include <math.h>
#include "kernel.h"


kernel_t *init_kernel(long size)
{
	kernel_t *k = calloc(1, sizeof(kernel_t));
	if (k)
	{
		set_data_kernel(k, calloc(size * size, sizeof(double)));
		set_size_kernel(k, size);
		if (!get_data_kernel(k))
		{
			free_kernel(k);
			k = NULL;
		}
	}
	return k;
}


void free_kernel(kernel_t *k)
{
	if (k)
	{
		free(get_data_kernel(k));
	}
	free(k);
}


int set_kernel_elem(kernel_t *k, long i, long j, double val)
{
	if (!k)
	{
		return 0;
	}
	long ind = j + i * get_size_kernel(k);
	get_data_kernel(k)[ind] = val;
	return 1;
}


double *get_kernel_elem(kernel_t *k, long i, long j)
{
	if (!k)
	{
		return NULL;
	}
	long ind = j + i * get_size_kernel(k);
	return &(get_data_kernel(k)[ind]);
}


long get_size_kernel(kernel_t *k)
{
	return k->size;
}


double *get_data_kernel(kernel_t *k)
{
	return k->data;
}


void set_size_kernel(kernel_t *k, long size)
{
	k->size = size;
}


void set_data_kernel(kernel_t *k, double *data)
{
	k->data = data;
}


kernel_t *get_sobel_kernel_x(void)
{
	kernel_t *k = init_kernel(3);
	if (!k)
	{
		return NULL;
	}
	set_kernel_elem(k, 0, 0, -1);
	set_kernel_elem(k, 0, 1, -2);
	set_kernel_elem(k, 0, 2, -1);
	set_kernel_elem(k, 2, 0, 1);
	set_kernel_elem(k, 2, 1, 2);
	set_kernel_elem(k, 2, 2, 1);
	return k;
}


kernel_t *get_sobel_kernel_y(void)
{
	kernel_t *k = init_kernel(3);
	if (!k)
	{
		return NULL;
	}
	set_kernel_elem(k, 0, 0, -1);
	set_kernel_elem(k, 1, 0, -2);
	set_kernel_elem(k, 2, 0, -1);
	set_kernel_elem(k, 0, 2, 1);
	set_kernel_elem(k, 1, 2, 2);
	set_kernel_elem(k, 2, 2, 1);
	return k;
}


kernel_t *get_laplas_kernel_pos(void)
{
	kernel_t *k = init_kernel(3);
	if (!k)
	{
		return NULL;
	}
	set_kernel_elem(k, 0, 1, 1);
	set_kernel_elem(k, 1, 0, 1);
	set_kernel_elem(k, 1, 1, -4);
	set_kernel_elem(k, 1, 2, 1);
	set_kernel_elem(k, 2, 1, 1);
	return k;
}


kernel_t *get_laplas_kernel_neg(void)
{
	kernel_t *k = init_kernel(3);
	if (!k)
	{
		return NULL;
	}
	set_kernel_elem(k, 0, 1, -1);
	set_kernel_elem(k, 1, 0, -1);
	set_kernel_elem(k, 1, 1, 4);
	set_kernel_elem(k, 1, 2, -1);
	set_kernel_elem(k, 2, 1, -1);
	return k;
}


kernel_t *get_laplas_kernel_diag(void)
{
	kernel_t *k = init_kernel(3);
	if (!k)
	{
		return NULL;
	}
	set_kernel_elem(k, 0, 0, 1);
	set_kernel_elem(k, 0, 1, 1);
	set_kernel_elem(k, 0, 2, 1);
	set_kernel_elem(k, 1, 0, 1);
	set_kernel_elem(k, 1, 1, -8);
	set_kernel_elem(k, 1, 2, 1);
	set_kernel_elem(k, 2, 0, 1);
	set_kernel_elem(k, 2, 1, 1);
	set_kernel_elem(k, 2, 2, 1);
	return k;
}


double gauss_func(int y, int x, double deviation)
{
	double pi = cos(-1);
	return 1 / (2 * pi * deviation * deviation) * exp(-(x * x + y * y) / (2 * deviation * deviation));
}


kernel_t *get_gauss_kernel(long size, double deviation)
{
	kernel_t *k = init_kernel(size);
	if (!k)
	{
		return NULL;
	}
	for (long i = 0; i < size; i++)
	{
		for (long j = 0; j < size; j++)
		{
			double val = gauss_func(size / 2 - i, size / 2 - j, deviation);
			set_kernel_elem(k, i, j, val);
		}
	}
	return k;
}
