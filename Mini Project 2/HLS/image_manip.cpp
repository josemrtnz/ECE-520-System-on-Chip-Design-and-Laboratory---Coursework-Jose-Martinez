
#include "image_manip.h"

short int run_all(
		short int input_image[ROWS][COLS],
		short int output_image[OUTS][ROWS][COLS],
		short int out[MAX_LENGTH])
{
	image_binary(input_image, output_image[0]);
	image_average(input_image, output_image[1]);
	image_invert(input_image, output_image[2]);
	image_scale(input_image, output_image[3]);
	short int tmp = image_compression(input_image, out);
	image_decompress( out, tmp, output_image[4]);
	return tmp;
}

void image_binary(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS])
{
	// Iterate over the rows
	Bin_Row: for(int i = 0; i < ROWS; i++) {
	      // Iterate over the columns
	      Bin_Col: for(int j = 0; j < COLS; j++) {
	         if(input_image[i][j] < TH) output_image[i][j] = 0;
	         else output_image[i][j] = 255;
	      }
	   }
}

void image_average(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS])
{
	// Iterate over the rows
	Ave_Row: for(int i = 0; i < ROWS; i++) {
	      // Iterate over the columns
	      Ave_Col: for(int j = 0; j < COLS; j++) {
	    	  switch(j) {
	    	  case 0:
	    		  if(i == 0) output_image[i][j] = (input_image[i][j] + input_image[i][j+1] + input_image[i+1][j] + input_image[i+1][j+1])/4;
	    		  else if (i == ROWS-1) output_image[i][j] = (input_image[i][j] + input_image[i][j+1] + input_image[i-1][j] + input_image[i-1][j+1])/4;
	    		  else output_image[i][j] = (input_image[i][j] + input_image[i+1][j] + + input_image[i-1][j] + input_image[i][j+1]
											 + input_image[i-1][j+1] + input_image[i+1][j+1])/6;
	    		  break;
	    	  case COLS-1:
	    		  if(i == 0) output_image[i][j] = (input_image[i][j] + input_image[i][j-1] + input_image[i+1][j] + input_image[i+1][j-1])/4;
	    		  else if (i == ROWS-1) output_image[i][j] = (input_image[i][j] + input_image[i][j-1] + input_image[i-1][j] + input_image[i-1][j-1])/4;
	    		  else output_image[i][j] = (input_image[i][j] + input_image[i+1][j] + + input_image[i-1][j] + input_image[i][j-1]
	    		  							 + input_image[i-1][j-1] + input_image[i+1][j-1])/6;
	    		  break;
	    	  default:
	    		  if(i == 0) output_image[i][j] = (input_image[i][j] + input_image[i+1][j] + input_image[i+1][j+1] + input_image[i+1][j-1]
												   + input_image[i][j+1] + input_image[i][j-1])/6;
	    		  else if(i == ROWS-1) output_image[i][j] = (input_image[i][j] + input_image[i-1][j] + input_image[i-1][j+1] + input_image[i-1][j-1]
													     + input_image[i][j+1] + input_image[i][j-1])/6;
	    		  else output_image[i][j] = (input_image[i][j] + input_image[i+1][j] + input_image[i][j+1] + input_image[i+1][j+1] + input_image[i+1][j-1]
									         + input_image[i-1][j] + input_image[i][j-1] + input_image[i-1][j-1] + input_image[i-1][j+1])/9;
	    		  break;
	    	  }
	      }
	   }
}

void image_invert(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS])
{
	// Iterate over the rows
		Inv_Row: for(int i = 0; i < ROWS; i++) {
		      // Iterate over the columns
		      Inv_Col: for(int j = 0; j < COLS; j++) {
		         output_image[i][j] = 255 - input_image[i][j];
		      }
		   }
}

void image_scale(
		short int input_image[ROWS][COLS],
		short int output_image[ROWS][COLS])
{
	// Iterate over the rows
		Scl_Row: for(int i = 0; i < ROWS; i++) {
		      // Iterate over the columns
		      Scl_Col: for(int j = 0; j < COLS; j++) {
		         output_image[i][j] = W * input_image[i][j];
		      }
		   }
}

short int image_compression(
		short int input_image[ROWS][COLS],
		short int out[MAX_LENGTH])
{
	short int prev = 0;
	short int count = 1;
	short int curr = 0;
	Comp_Row: for(int i = 0; i < ROWS; i++) {
			      // Iterate over the columns
			      Comp_Col: for(int j = 0; j < COLS; j++) {
			    	  if(ROWS == 0 && COLS == 0) prev = input_image[i][j];
			    	  else {
			    		  if(prev == input_image[i][j]) count++;
			    		  else {
			    			  out[curr] = prev;
			    			  out[curr+1] = count;
			    			  curr = curr + 2;
			    			  prev = input_image[i][j];
			    			  count = 1;
			    		  }
			    	  }
			      }
			      out[curr] = prev;
			      out[curr+1] = count;
	}
	return curr;
}

void image_decompress(
		short int compressed_image[MAX_LENGTH],
		short int range,
		short int output_image[ROWS][COLS])
{
	short int cycle = 0;
	short int pos = 2;
	short int currN = 0;
	Scl_Row: for(int i = 0; i < ROWS; i++) {
			      // Iterate over the columns
			      Scl_Col: for(int j = 0; j < COLS; j++) {
			    	  if(!cycle){
			    		  currN = compressed_image[pos];
			    		  cycle = compressed_image[pos+1];
			    		  pos = pos + 2;
			    	  }
			          output_image[i][j] = currN;
			          cycle = cycle - 1;
			      }
			   }
}
