#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>

#define matrix_width  100  //6000
#define matrix_height 100 //4000

#define numberChar 2

#define decode_size 2*matrix_height*matrix_width+1

using namespace std::chrono;
using namespace std;

char image[matrix_height][matrix_width];
char letters[] = "ab";


// Function to generate random Input Data
void generateRandomImage()
{
    srand(time(NULL));

    for(int i=0 ; i<matrix_height ; i++)
    {
        for(int j=0 ; j<matrix_width ; j++)
        {
            image[i][j] = letters[rand() % numberChar]; // modify to match the size of letters
        }
    }
}

// Function to save the random generated matrix in input_data.txt
void exportInputData() // to modify cout with ofstream
{
    ofstream myfile;
    myfile.open("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\input_data.txt");

    for(int i=0; i<matrix_height;i++)
    {
        for(int j=0;j<matrix_width;j++)
        {
            myfile<<image[i][j];
        }
        myfile<<endl;
    }
    myfile.close();
}

// The encoding function, saves data in encoded_data.txt
void encodeRLE()
{
    ofstream myfile;
    myfile.open ("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\encoded_data.txt");

    #pragma omp single
    for(int i=0 ; i<matrix_height ; i++)
    {
        for(int j=0 ; j<matrix_width ; j++)
        {
            int count = 1;
			
			while(j<matrix_width-1 && image[i][j] == image[i][j+1])
			{
				count++;
				j++;
			}
			
			if(count == 1) myfile<<image[i][j];
			else myfile<<image[i][j]<<count;
        }
        myfile<<endl;
    }
    myfile.close();
}

void decodeRLE(){
    char txt[decode_size];
    ifstream readFile = ifstream("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\encoded_data.txt", ios_base::in);

    if(readFile.is_open() == true)
    {
		#pragma omp critical
        {
			char c;
			int i = 0;
			while (readFile.get(c))
			{
				txt[i] = c;
				i++;
			}
			
			readFile.close();
			readFile.close();
			txt[i] = '\0';
		}
    }

    ofstream writeFile;
    writeFile.open("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\decoded_data.txt");

    int st_index = 0;
	
	#pragma omp single
    for (int j = 0; j < strlen(txt);) {
        int x = 0;
		
        while (j < strlen(txt) && isdigit(txt[j])) {
            x = (x * 10) + (txt[j] - '0');
            j++;
        }
        x--;
        while (x > 0) {
            writeFile << txt[st_index];
            x--;
        }
		
		#pragma omp critical
		{
			if (j < strlen(txt)) {
				writeFile << txt[j];
				st_index = j;
				j++;
			}
		}

		#pragma omp critical
		{
			if (txt[j] == '\n') {
				j++;
				writeFile << endl;
			}
		}
    }
    writeFile.close();
}

int main()
{
    // Generate the input data
    generateRandomImage();
    exportInputData();

    ifstream in_file("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\input_data.txt", ios::binary);
    in_file.seekg(0, ios::end);
    int in_size = in_file.tellg();
    cout<<"Size of the input file is"<<" "<< in_size<<" "<<"bytes"<<endl<<endl;
    in_file.close();


    // ENCODE
    auto start_encode = std::chrono::high_resolution_clock::now();
    encodeRLE();
    auto stop_encode = std::chrono::high_resolution_clock::now();
    cout<<"Encode computing done in "<< duration_cast<std::chrono::milliseconds>(stop_encode-start_encode).count()<<" ms"<<endl;

    ifstream encoded_file("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\encoded_data.txt", ios::binary);
    encoded_file.seekg(0, ios::end);
    int encoded_size = encoded_file.tellg();
    cout<<"Size of the encoded file is"<<" "<< encoded_size<<" "<<"bytes"<<endl<<endl;
    encoded_file.close();

    //DECODE
    auto start_decode = std::chrono::high_resolution_clock::now();
    decodeRLE();
    auto stop_decode = std::chrono::high_resolution_clock::now();
    cout<<"Decode computing done in "<< duration_cast<std::chrono::milliseconds>(stop_decode-start_decode).count()<<" ms"<<endl;

    ifstream decoded_file("C:\\Users\\razva\\Desktop\\FACULTATE\\PAO\\RLE_data_compression\\decoded_data.txt", ios::binary);
    decoded_file.seekg(0, ios::end);
    int decoded_size = decoded_file.tellg();
    cout<<"Size of the decoded file is"<<" "<< decoded_size<<" "<<"bytes"<<endl;
    decoded_file.close();

    return 0;}