// Run-Length encoder and decoder - Test Bench
#include "RLE_encoder_decoder.h"
#include "RLE_encoder.h"
#include "RLE_decoder.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct ENC
{
	char encData[200];
	int encLen;
};

struct DEC
{
	char decData[200];
	int decLen;
};

struct ENCDEC
{
	int encL;
	int decL;
	char encD[200];
	char decD[200];
};


int main()
{
	//Constants=======================================================================
	
	// Declare input size
	int matrix_width = 10;
	int matrix_height = 5;
	
	//Initialize input data
	char inputData[matrix_height][matrix_width];
	char encodedData[200];
	char decodedData[200];
	
	int i, j;
	int encoded_length = 0;
	int decoded_length = 0;
	
	
	// File pointers===================================================================
	FILE *input_file; 
	FILE *encoded_file;
	FILE *decoded_file;
	
	// Function result variable========================================================
	struct ENCDEC encdecResult;

	// Generate input data=============================================================
	inputData[0][0] = 'a'; inputData[0][1] = 'a'; inputData[0][2] = 'a'; inputData[0][3] = 'a'; inputData[0][4] = 'a'; inputData[0][5] = 'a'; inputData[0][6] = 'a'; inputData[0][7] = 'a'; inputData[0][8] = 'a'; inputData[0][9] = 'b';
	inputData[1][0] = 'a'; inputData[1][1] = 'a'; inputData[1][2] = 'a'; inputData[1][3] = 'a'; inputData[1][4] = 'a'; inputData[1][5] = 'b'; inputData[1][6] = 'b'; inputData[1][7] = 'b'; inputData[1][8] = 'b'; inputData[1][9] = 'b';  
	inputData[2][0] = 'a'; inputData[2][1] = 'a'; inputData[2][2] = 'b'; inputData[2][3] = 'b'; inputData[2][4] = 'b'; inputData[2][5] = 'a'; inputData[2][6] = 'a'; inputData[2][7] = 'a'; inputData[2][8] = 'b'; inputData[2][9] = 'a';  
	inputData[3][0] = 'a'; inputData[3][1] = 'b'; inputData[3][2] = 'a'; inputData[3][3] = 'b'; inputData[3][4] = 'a'; inputData[3][5] = 'b'; inputData[3][6] = 'a'; inputData[3][7] = 'b'; inputData[3][8] = 'a'; inputData[3][9] = 'b';  
	inputData[4][0] = 'a'; inputData[4][1] = 'a'; inputData[4][2] = 'b'; inputData[4][3] = 'c'; inputData[4][4] = 'a'; inputData[4][5] = 'b'; inputData[4][6] = 'b'; inputData[4][7] = 'd'; inputData[4][8] = 'e'; inputData[4][9] = 'b';  

	// Print inputData in input.dat====================================================
	input_file = fopen("input.dat", "w"); // file to save input data
	
	for(i=0 ; i<matrix_height ; i++)
	{
		for(j=0 ; j< matrix_width ; j++)
		{
			fprintf(input_file, "%c", inputData[i][j]);
		}
		
		fprintf(input_file, "\n");
	}
	
	fclose(input_file); // close input.dat
	
	
	// Call function=========================================================================
	encdecResult = RLE_encoder_decoder(matrix_height, matrix_width, inputData);

	// Save encodedData in encoded.dat=======================================================
	encoded_file = fopen("encoded.dat", "w"); // file to save encodedData

	for(i=0 ; i<encdecResult.encL ; i++)
	{
		fprintf(encoded_file, "%c", encdecResult.encD[i]);
	}

	fclose(encoded_file);


	// Save decodedData in decoded.dat=======================================================
	decoded_file = fopen("decoded.dat", "w"); // file to save decodedData

	for(i=0 ; i<encdecResult.decL ; i++)
	{
		fprintf(decoded_file, "%c", encdecResult.decD[i]);
	}

	fclose(decoded_file);
	

	// Display in console if the test result is identical with the golden model result==============

	printf ("Comparing against golden model:\n");
	// Compare input data
    if (system("diff -w input.dat input.gold.dat"))
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "FAIL: INPUT_DATA DOES NOT match the golden INPUT_DATA\n");
    	fprintf(stdout, "*******************************************\n");
    }
    else
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "PASS: INPUT_DATA matches the golden INPUT_DATA!\n");
    	fprintf(stdout, "*******************************************\n");
    }
	// Compare encoded data
	if (system("diff -w encoded.dat encoded.gold.dat"))
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "FAIL: ENCODED_DATA DOES NOT match the golden ENCODED_DATA\n");
    	fprintf(stdout, "*******************************************\n");
    }
    else
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "PASS: ENCODED_DATA matches the golden ENCODED_DATA!\n");
    	fprintf(stdout, "*******************************************\n");
    }
	// Compare decoded data
	if (system("diff -w decoded.dat decoded.gold.dat"))
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "FAIL: DECODED_DATA DOES NOT match the golden DECODED_DATA\n");
    	fprintf(stdout, "*******************************************\n");

    }
    else
    {
    	fprintf(stdout, "*******************************************\n");
    	fprintf(stdout, "PASS: DECODED_DATA matches the golden DECODED_DATA!\n");
    	fprintf(stdout, "*******************************************\n");

    }

}
