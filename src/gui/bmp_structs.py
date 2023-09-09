from ctypes import *


class PIXEL(Structure):
	_fields_ = [("b", c_ubyte),
				("g", c_ubyte),
				("r", c_ubyte),
				("a", c_ubyte)]


class HEADER(Structure):
	_fields_ = [("type", c_int),
				("file_size", c_int),
				("reserved", c_int),
				("off_bits", c_int)]


class INFO(Structure):
	_fields_ = [("b_size", c_int),
				("width", c_int),
				("height", c_int),
				("planes", c_int),
				("bit_count", c_int),
				("compression", c_int),
				("size_image", c_int),
				("x_pels_per_meter", c_int),
				("y_pels_per_meter", c_int),
				("clr_used", c_int),
				("clr_important", c_int)]


class BITMAP(Structure):
	_fields_ = [("data", POINTER(PIXEL)),
				("width", c_int),
				("height", c_int),
				("psize", c_int)]


class BMP_FILE(Structure):
	_fields_ = [("header", POINTER(HEADER)),
				("info", POINTER(INFO)),
				("bitmap", POINTER(BITMAP))]
