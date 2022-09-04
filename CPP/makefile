main_function: main_1 main_2 
	 @echo "================================================================="
	 @echo "RLE Encode and Decode - Unoptimized - 2 characters - size 100x100: "
	 @./main_1
	 @echo "================================================================="
	 
	 @echo "RLE Encode and Decode - Optimized + OpenMP - 2 characters - size 100x100: "
	 @./main_2
	 @echo "================================================================="
	 
	
main_1: RLEencode.cpp
	 g++ RLEencode.cpp -o main_1
	 	 
main_2: RLEencode12.cpp
	 g++ RLEencode.cpp -O3 -fopenmp -o main_2
	 
