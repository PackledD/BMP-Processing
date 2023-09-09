#ifndef KERNEL_H
#define KERNEL_H

typedef struct kernel
{
	double *data;
	long size;
} kernel_t;

kernel_t *init_kernel(long size);
void free_kernel(kernel_t *k);
int set_kernel_elem(kernel_t *k, long i, long j, double val);
double *get_kernel_elem(kernel_t *k, long i, long j);

kernel_t *get_sobel_kernel_x(void);
kernel_t *get_sobel_kernel_y(void);

kernel_t *get_laplas_kernel_pos(void);
kernel_t *get_laplas_kernel_neg(void);
kernel_t *get_laplas_kernel_diag(void);

double gauss_func(int y, int x, double deviation);
kernel_t *get_gauss_kernel(long size, double deviation);


long get_size_kernel(kernel_t *k);
double *get_data_kernel(kernel_t *k);
void set_size_kernel(kernel_t *k, long size);
void set_data_kernel(kernel_t *k, double *data);

#endif
