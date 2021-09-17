#ifndef __IMAGEMANIP_H__
#define __IMAGEMANIP_H__

#include <cmath>
#include <stdlib.h>

#define HW_COSIM

#define ROWS       100
#define COLS       100
#define OUTS       5
#define MAX_LENGTH 1250
#define TH         80
#define W          0.5

// Top level function
short int run_all(
		short int input_image[ROWS][COLS],
		short int output_image[OUTS][ROWS][COLS],
		short int out[MAX_LENGTH]);

void image_binary(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS]);

void image_average(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS]);

void image_invert(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS]);

void image_scale(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS]);

short int image_compression(
		short int input_image[ROWS][COLS],
		short int out[MAX_LENGTH]);

void image_decompress(
		short int compressed_image[MAX_LENGTH],
		short int range,
		short int output_image[ROWS][COLS]);

#endif
