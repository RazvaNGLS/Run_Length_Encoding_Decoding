# Run_Length_Encoding_Decoding
Run-Length Encoding (RLE) is one of the oldest algorithms for data-compression available.
It compresses by looking at the data for repetitions of the same character in a row and storing the amount and the respective character as target-data.
Unfortunately, it only compresses within strict and special cases. Outside of these cases, it increases the data-size, even doubles the size in worst cases compared to the original, unprocessed data

<p align="center">
  <img width="355" height="229" src="https://iq.opengenus.org/content/images/2020/04/rleimg--1-.png">
</p>

![RLE_encode](https://iq.opengenus.org/content/images/2020/04/rleimg--1-.png)

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




