#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct DEC
{
	char decData[200];
	int decLen;
};
	
struct DEC RLE_decoder(char encodedData[200], int encoded_length)
{

	struct DEC dec;

	int j;
	int k = 0;

	int st_index = 0;
	int x;

	#pragma HLS ARRAY_PARTITION variable=encodedData     dim=0
	//#pragma HLS ARRAY_PARTITION variable=encoded_length  dim=0

	for(j = 0; j < encoded_length ; j = j+0)
		{
			x = 0;
			while (j < encoded_length && (encodedData[j] >= 48 && encodedData[j] <= 57 )) {
	            x = (x * 10) + (encodedData[j] - '0');
	            j++;
	        }
	        x--;
	        while (x > 0) {
				#pragma HLS pipeline II=1
				dec.decData[k] = encodedData[st_index];
	        	k++;
	            x--;
	        }

	        if (j < encoded_length) {
	        	dec.decData[k] = encodedData[j];
	        	k++;
	            st_index = j;
	            j++;
	        }

	        if (encodedData[j] == '\n') {                    // write new line
	            j++;
	            dec.decData[k] = '\n';
	            k++;
	        }
		}

	dec.decLen = k;

	return dec;
}
