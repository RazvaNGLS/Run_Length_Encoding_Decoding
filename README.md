# Run_Length_Encoding_Decoding
Run-Length Encoding (RLE) is one of the oldest algorithms for data-compression available.
It compresses by looking at the data for repetitions of the same character in a row and storing the amount and the respective character as target-data.
Unfortunately, it only compresses within strict and special cases. Outside of these cases, it increases the data-size, even doubles the size in worst cases compared to the original, unprocessed data

<p align="center">
  <img width="600" height="400" src="https://iq.opengenus.org/content/images/2020/04/rleimg--1-.png">
</p>

In order to implement this algorithm, the following steps should be considered:

## Declare the INPUT DATA:
>* Matrix width (integer)
>* Matrix height (integer)
>* Number of different characters (integer)
>* The used letters (char array)

## Generate random INPUT DATA to be ENCODED:
>* Create a random matrix (Matrix width * Matrix height values), that will be used as input data
>* Save the input data in a text file (input_data.txt)

## ENCODE function:
>* Function looks at the data for repetitions of the same character in a row and stores the number of repetitions and the respective character
>* Write the encoded data in a text file (encoded_data.txt)

## DECODE function
>* Function that extracts the characters from the encoded file (encoded_data.txt) and save them in a char array.
>* Transform an array of consecutive char digits (‘1’,’2’,’3’) in an integer number (123)
>* Write the decoded data in a text file (decoded_data.txt)

## PERFORMANCE ANALYSIS
>* Check the execution time of encoding and decoding for unoptimized and optimized code
>* Check the size of input data, encoded data and decoded data

## Usage


## Contributiong



