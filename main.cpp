#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // for exit(0)

#define FILE_LEN 4 

uint32_t read_hex(char* filename)
{
	// open file
	FILE *fp;
	fp = fopen(filename, "rb");

	if(fp == NULL) {
		printf("failed to open file %s..\n", filename);
		exit(0);
	}

	// read file size
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	if(size != 4) {
		printf("file size is not 4 bytes..\n");
		exit(0);
	}

	// rewind
	fseek(fp, 0, SEEK_SET);
	
	// read file
	uint8_t buf[FILE_LEN];
	fread(buf, sizeof(uint8_t), FILE_LEN, fp);

	fclose(fp);

	// calc number
	uint32_t result = 0;
	for(int i = 0 ; i < FILE_LEN ; i ++) {
		result = result << 8;
		result = result + buf[i];
	}

	return result;
}


int main(int argc, char* argv[]) {

	// usage
	if(argc != 3) {
		printf("usage : ./add-nbo [thousand.bin] [five-hundred.bin] \n");
		return -1;
	}
	
	// get two numbers
	uint32_t n1 = read_hex(argv[1]);
	uint32_t n2 = read_hex(argv[2]);

	// print result
	printf("%d(0x%04x) + %d(0x%04x) = %d(0x%04x)\n", n1, n1, n2, n2, n1 + n2, n1 + n2);

	return 0;
}
