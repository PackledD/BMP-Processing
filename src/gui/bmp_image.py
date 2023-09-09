from ctypes import *
from bmp_structs import *


class BMP():
	cdll.LoadLibrary("./bmp.so")
	_libc = CDLL("./bmp.so")

	_grayscale = _libc.grayscale
	_grayscale.argtypes = [POINTER(BMP_FILE)]

	_sobelian_x = _libc.sobelian_x
	_sobelian_x.argtypes = [POINTER(BMP_FILE)]

	_sobelian_y = _libc.sobelian_y
	_sobelian_y.argtypes = [POINTER(BMP_FILE)]

	_sobelian = _libc.sobelian
	_sobelian.argtypes = [POINTER(BMP_FILE)]

	_laplasian_pos = _libc.laplasian_pos
	_laplasian_pos.argtypes = [POINTER(BMP_FILE)]

	_laplasian_neg = _libc.laplasian_neg
	_laplasian_neg.argtypes = [POINTER(BMP_FILE)]

	_laplasian_diag = _libc.laplasian_diag
	_laplasian_diag.argtypes = [POINTER(BMP_FILE)]

	_gaussian = _libc.gaussian
	_gaussian.argtypes = [POINTER(BMP_FILE), c_long, c_double]

	_border_highlight = _libc.border_highlight
	_border_highlight.argtypes = [POINTER(BMP_FILE), c_int]

	_median_filter = _libc.median_filter
	_median_filter.argtypes = [POINTER(BMP_FILE), c_int]

	_init_bmp = _libc.init_bmp
	_init_bmp.argtypes = [POINTER(POINTER(BMP_FILE))]

	_read_bmp = _libc.read_bmp
	_read_bmp.argtypes = [POINTER(BMP_FILE), c_char_p]

	_write_bmp = _libc.write_bmp
	_write_bmp.argtypes = [POINTER(BMP_FILE), c_char_p]

	def __init__(self, filename):
		self.filename = c_char_p(filename.encode("utf8"))
		self.image = pointer(BMP_FILE())
		BMP._init_bmp(pointer(self.image))

	def read(self):
		return BMP._read_bmp(self.image, self.filename)

	def write(self, dst):
		return BMP._write_bmp(self.image, dst.encode("utf8"))

	def grayscale(self):
		return BMP._grayscale(self.image)

	def sobelian(self):
		return BMP._sobelian(self.image)

	def sobelian_x(self):
		return BMP._sobelian_x(self.image)

	def sobelian_y(self):
		return BMP._sobelian_y(self.image)

	def laplasian_neg(self):
		return BMP._laplasian_neg(self.image)

	def laplasian_pos(self):
		return BMP._laplasian_pos(self.image)

	def laplasian_diag(self):
		return BMP._laplasian_diag(self.image)

	def gaussian(self, radius, deviation):
		return BMP._gaussian(self.image, radius, deviation)

	def border_highlight(self, treshold):
		return BMP._border_highlight(self.image, treshold)

	def median_filter(self, radius):
		return BMP._median_filter(self.image, radius)
