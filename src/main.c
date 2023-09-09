#include <stdio.h>
#include <stdlib.h>
#include "bmp_file.h"
#include "bmp_file_process.h"

int test(char *in, char *out);


int main(void)
{
	int rc;
	rc = test("./examples/exmp1.bmp", "test1.bmp");
	rc = test("./examples/exmp2.bmp", "test2.bmp");
	rc = test("./examples/exmp3.bmp", "test3.bmp");
	rc = test("./examples/exmp4.bmp", "test4.bmp");
	rc = test("./examples/exmp5.bmp", "test5.bmp");
	rc = test("./examples/exmp6.bmp", "test6.bmp");
	rc = test("./examples/exmp7.bmp", "test7.bmp");
	rc = test("./examples/exmp8.bmp", "test8.bmp");
	rc = test("./examples/exmp9.bmp", "test9.bmp");
	rc = test("./examples/exmp10.bmp", "test10.bmp");
	rc = test("./examples/exmp11.bmp", "test11.bmp");
	rc = test("./examples/exmp12.bmp", "test12.bmp");
	return rc;
}


int test(char *in, char *out)
{
	bmp_t *bmp;
	init_bmp(&bmp);
	int rc = read_bmp(bmp, in);
	if (rc)
	{
		// grayscale(bmp);
		// sobelian_x(bmp);
		// sobelian_y(bmp);
		// sobelian(bmp);
		// laplasian_pos(bmp);
		// laplasian_neg(bmp);
		// laplasian_diag(bmp);
		// gaussian(bmp, 2, 4);
		// border_highlight(bmp, 16);
		// median_filter(bmp, 3);
		rc = write_bmp(bmp, out);
	}
	free_bmp(bmp);
	return rc;
}
