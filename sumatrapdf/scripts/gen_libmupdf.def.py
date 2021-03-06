#!/usr/bin/env python

"""
Generates a list of all exports from libmupdf.dll from the function lists
contained in the mupdf/*/*.h headers (only MuPDF and MuXPS are included).
"""

import os, re, util2

def generateExports(header, exclude=[]):
	data = open(header, "r").read()
	data = re.sub(r"(?sm)^#ifndef NDEBUG\s.*?^#endif", "", data, 0)
	data = re.sub(r"(?sm)^#ifdef ARCH_ARM\s.*?^#endif", "", data, 0)
	data = re.sub(r"(?sm)^#ifdef FITZ_DEBUG_LOCKING\s.*?^#endif", "", data, 0)
	data = data.replace(" FZ_NORETURN;", ";")
	functions = re.findall(r"(?sm)^\w+ (?:\w+ )?\*?(\w+)\(.*?\);", data)
	exports = "\n".join(["\t" + name for name in functions if name not in exclude])
	return exports

def collectFunctions(file):
	data = open(file, "r").read()
	return re.findall(r"(?sm)^\w+(?: \*\n|\n| \*| )(fz_\w+)\(", data)

LIBMUPDF_DEF = """\
; This file is auto-generated by gen_libmupdf.def.py

LIBRARY libmupdf
EXPORTS

; Fitz exports

%(fitz_exports)s

; MuPDF exports

%(mupdf_exports)s

; MuXPS exports

%(muxps_exports)s

; jpeg exports (required for libdjvu)

	jpeg_resync_to_restart
	jpeg_finish_decompress
	jpeg_read_scanlines
	jpeg_start_decompress
	jpeg_read_header
	jpeg_CreateDecompress
	jpeg_destroy_decompress
	jpeg_std_error

; zlib exports (required for ZipUtil, PsEngine, LzmaSimpleArchive)

	gzerror
	gzprintf
	gzopen
	gzopen_w
	gzseek
	gztell
	gzread
	gzclose
	inflateInit_
	inflateInit2_
	inflate
	inflateEnd
	deflateInit_
	deflateInit2_
	deflate
	deflateEnd
	compress
	compressBound
	crc32
"""

def main():
	util2.chdir_top()
	os.chdir("mupdf")
	
	# don't include/export doc_* functions, mucbz.h and muimage.h functions and svg and pwg functions
	doc_exports = collectFunctions("fitz/doc_document.c") + collectFunctions("fitz/doc_interactive.c")
	more_formats = collectFunctions("fitz/dev_svg.c") + collectFunctions("fitz/res_pwg.c")
	ignore_exports = doc_exports + more_formats + ["fz_init_ui_pointer_event", "fz_access_submit_event"]
	
	fitz_exports = generateExports("fitz/fitz.h", ignore_exports) + "\n\n" + generateExports("fitz/fitz-internal.h", ignore_exports)
	mupdf_exports = generateExports("pdf/mupdf.h") + "\n\n" + generateExports("pdf/mupdf-internal.h", ["pdf_crypt_buffer", "pdf_open_compressed_stream"])
	muxps_exports = generateExports("xps/muxps.h") + "\n\n" + generateExports("xps/muxps-internal.h", ["xps_parse_solid_color_brush", "xps_print_path"])
	
	list = LIBMUPDF_DEF % locals()
	open("../src/libmupdf.def", "wb").write(list.replace("\n", "\r\n"))

if __name__ == "__main__":
	main()
