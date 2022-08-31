#include "RLE_decoder.h"
#include "RLE_encoder.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//========================================================
struct ENC
{
	char encData[200];
	int encLen;
};

//========================================================
struct DEC
{
	char decData[200];
	int decLen;
};
//========================================================
struct ENCDEC
{
	int encL;
	int decL;
	char encD[200];
	char decD[200];
};

// MAIN FUNCTION==========================================================================
struct ENCDEC RLE_encoder_decoder(int matrix_height, int matrix_width, char inputData[5][10])
{

    //#pragma HLS ARRAY_PARTITION variable=matrix_width  dim=0
    //#pragma HLS ARRAY_PARTITION variable=matrix_height dim=0
    #pragma HLS ARRAY_PARTITION variable=inputData     dim=2

	//Initialize structures===============================================================
	struct ENC    encResult;
	struct DEC    decResult;
	struct ENCDEC edResult;

	int i;

	// Call RLE_encoder and RLE_decoder=====================================================
	encResult = RLE_encoder(matrix_height, matrix_width, inputData);
	decResult = RLE_decoder(encResult.encData, encResult.encLen);

	// Store encoded and decoded length in the main structure
	edResult.encL = encResult.encLen;
	edResult.decL = decResult.decLen;


	// Copy encoded data to output==========================================================
	for(i=0 ; i<edResult.encL ; i++)
	{
		#pragma HLS pipeline II=1
		edResult.encD[i] = encResult.encData[i];
	}


	// Copy decoded data to output==========================================================
	for(i=0 ; i<edResult.encL ; i++)
	{
		#pragma HLS pipeline II=1
		edResult.decD[i] = decResult.decData[i];
	}

	// Return output========================================================================
	return edResult;

}
