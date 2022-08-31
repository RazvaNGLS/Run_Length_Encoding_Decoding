#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Define encoding structure=========================================================
struct ENC
{
	char encData[200];
	int encLen;
};

// MAIN ENCODING FUNTION=============================================================
struct ENC RLE_encoder(int matrix_height, int matrix_width ,char inputData[5][10])
{
	// Initialize structure
	struct ENC enc;

	// Define variables
	int count;
	int i;
	int j;
	int k = 0;

	//#pragma HLS ARRAY_PARTITION variable=matrix_width  dim=0
	//#pragma HLS ARRAY_PARTITION variable=matrix_height dim=0
	#pragma HLS ARRAY_PARTITION variable=inputData     dim=2


	// Encoding algorithm
	for(i=0 ; i<matrix_height ; i++)
	{
		#pragma HLS pipeline II=1
		for(j=0 ; j<matrix_width ; j++)
		{
			#pragma HLS pipeline II=1
			count = 1;
			while(j < matrix_width-1 && inputData[i][j] == inputData[i][j+1])
			{
				count++;
				j++;
			}


				enc.encData[k] = inputData[i][j]; //save letter in char array

				enc.encData[k+1] = 48 + count; // save number (to replace with loop for numbers bigger than 9)
				k += 2;


		}

		enc.encData[k] = '\n';
		k++;
	}

	enc.encLen = k; //length of encoded data

	return enc;
}

