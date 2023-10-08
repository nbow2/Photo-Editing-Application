#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bmplib.h"
#include "unistd.h"

using namespace std;
using std::cout;
using std::cin;
using std::endl;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;

//#define BMP_BIG_ENDIAN
#define BYTE_SWAP(num) (((num>>24)&0xff) | ((num<<8)&&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

typedef struct {
  uint8    bfType1;
  uint8    bfType2;
  uint32   bfSize;
  uint16    bfReserved1;
  uint16    bfReserved2;
  uint32   bfOffBits;
  uint32   biSize;          // size of structure, in bytes
  uint32   biWidth;         // bitmap width, in pixels
  uint32   biHeight;        // bitmap height, in pixels
  uint16    biPlanes;        // see below
  uint16    biBitCount;      // see below
  uint32   biCompression;   // see below
  uint32   biSizeImage;     // see below
  uint32   biXPelsPerMeter; // see below
  uint32   biYPelsPerMeter; // see below
  uint32   biClrUsed;       // see below
  uint32   biClrImportant;  // see below
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct {
  uint8 rgbBlue;
  uint8 rgbGreen;
  uint8 rgbRed;
} RGBTRIPLE;

void write_hdr(uint8 *hdr, int *hdr_idx, uint32 data, uint32 size);


uint8 tempImage[SIZE][SIZE][RGB];
uint8 tempGSImage[SIZE][SIZE];

int readRGBBMP(const char* filename, unsigned char inputImage[][SIZE][RGB])
{
  uint8 type[2];
  int headersize = 0;

  int i,j,k;

  //BITMAPFILEHEADER bfh;

  /* file pointer */
  FILE *file;

  /* read input bmp into the data matrix */
  if (!(file=fopen(filename,"rb")))
	{
	  cout << "Cannot open file: " << filename <<endl;
	  return(1);
	}

  fread(type, sizeof(unsigned char), 0x2, file);
  if(type[0] != 'B' and type[1] != 'M'){
    cout << "Not a BMP file" << endl;
    return(1);
  }
  fseek(file, 8, SEEK_CUR);
  fread(&headersize, sizeof(uint32), 1, file);
#ifdef BMP_BIG_ENDIAN
  headersize = BYTE_SWAP(headersize);
#endif
  //cout << "Header size is " << headersize << endl;

  fseek(file, headersize, SEEK_SET);
  fread(tempImage, sizeof(uint8), SIZE*SIZE*RGB, file);
  // cout << (int)tempImage[0][0][0] << "," << (int)tempImage[0][0][1] << "," << (int)tempImage[0][0][2] << endl;
  fclose(file);

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	inputImage[SIZE-1-i][j][RGB-1-k] = tempImage[i][j][k];
	//cerr << tempImage[i][j][k] << ",";
      }
    }
	//cerr << endl;
  }
  return 0;
}


int writeRGBBMP(const char* filename, unsigned char outputImage[][SIZE][RGB])
{
  uint8 hdr[54];
  int hdr_idx = 0;

  int i,j,k;

  BITMAPFILEHEADER bfh;

  // file pointer
  FILE *file;

  bfh.bfType1 = 'B';
  bfh.bfType2 = 'M';
  bfh.bfSize = 0x36;
  bfh.bfReserved1 = 0x0;
  bfh.bfReserved2 = 0x0;
  bfh.bfOffBits = 0x36;

  bfh.biSize = 0x28;
  bfh.biWidth = SIZE;
  bfh.biHeight = SIZE;
  bfh.biPlanes = 1;
  bfh.biBitCount = 24;
  bfh.biCompression  = 0;
  bfh.biSizeImage = sizeof(RGBTRIPLE)*SIZE*SIZE;
  bfh.biXPelsPerMeter = 2400;
  bfh.biYPelsPerMeter = 2400;
  bfh.biClrUsed = 0;
  bfh.biClrImportant = 0;

  write_hdr(hdr, &hdr_idx, bfh.bfType1, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfType2, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved1, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved2, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfOffBits, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biWidth, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biHeight, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biPlanes, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biBitCount, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biCompression, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSizeImage, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biXPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biYPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrUsed, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrImportant, sizeof(uint32));

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	tempImage[SIZE-1-i][j][RGB-1-k] = outputImage[i][j][k];
      }
    }
  }

  // write result bmp file
  if (!(file=fopen(filename,"wb")))
    {
      cout << "Cannot open file: " << filename << endl;
      return(1);
    }
  fwrite(&hdr, sizeof(unsigned char), 0x36, file);
  fwrite(tempImage, sizeof(unsigned char), SIZE*SIZE*RGB, file);
  fclose(file);

  return 0;
}

void write_hdr(uint8 *hdr, int *hdr_idx, uint32 data, uint32 size)
{
  if(size == 1){
    hdr[*hdr_idx] = (uint8) data;
    (*hdr_idx) += 1;
  }
  else if(size == 2){
    hdr[*hdr_idx] = (uint8) (data & 0x00ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0xff00) >> 8);
    (*hdr_idx) += 1;
  }
  else if(size == 4){
    hdr[*hdr_idx] = (uint8) (data & 0x000000ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0x0000ff00) >> 8);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0x00ff0000) >> 16);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (uint8) ((data & 0xff000000) >> 24);
    (*hdr_idx) += 1;
  }
  else {
    printf("Illegal size in write_hdr...consult your instructor\n");
  }
}

int readGSBMP(const char* filename, unsigned char inputImage[][SIZE])
{
  uint8 type[2];
  int headersize = 0;

  int i,j;

  //BITMAPFILEHEADER bfh;

  /* file pointer */
  FILE *file;

  /* read input bmp into the data matrix */
  if (!(file=fopen(filename,"rb")))
	{
	  cout << "Cannot open file: " << filename <<endl;
	  return(1);
	}

  fread(type, sizeof(unsigned char), 0x2, file);
  if(type[0] != 'B' and type[1] != 'M'){
    cout << "Not a BMP file" << endl;
    return(1);
  }
  fseek(file, 8, SEEK_CUR);
  fread(&headersize, sizeof(uint32), 1, file);
#ifdef BMP_BIG_ENDIAN
  headersize = BYTE_SWAP(headersize);
#endif
  //cout << "Header size is " << headersize << endl;

  fseek(file, headersize, SEEK_SET);
  fread(tempGSImage, sizeof(uint8), SIZE*SIZE, file);
  //  cout << (int)tempGSImage[0][0][0] << "," << (int)tempGSImage[0][0][1] << "," << (int)tempGSImage[0][0][2] << endl;
  fclose(file);

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
	inputImage[SIZE-1-i][j] = tempGSImage[i][j];
	//	inputImage[SIZE-1-i][SIZE-1-j] = tempGSImage[i][j];
	//cerr << tempGSImage[i][j][k] << ",";
    }
	//cerr << endl;
  }
  return 0;
}


int writeGSBMP(const char* filename, unsigned char outputImage[][SIZE])
{
  uint8 hdr[54];
  int hdr_idx = 0;

  int i,j;

  BITMAPFILEHEADER bfh;

  // file pointer
  FILE *file;

  bfh.bfType1 = 'B';
  bfh.bfType2 = 'M';
  // 0x10436 = 2^16 + 1024 for color def + 0x36 for header
  bfh.bfSize = 0x010436; //0x36;

  bfh.bfReserved1 = 0x0;
  bfh.bfReserved2 = 0x0;
  // 0x0436
  bfh.bfOffBits = 0x436; //0x36;

  bfh.biSize = 0x28;
  bfh.biWidth = SIZE;
  bfh.biHeight = SIZE;
  bfh.biPlanes = 1;
  bfh.biBitCount = 8;
  bfh.biCompression  = 0;
  bfh.biSizeImage = SIZE*SIZE;
  bfh.biXPelsPerMeter = 0; //2400;
  bfh.biYPelsPerMeter = 0; //2400;
  bfh.biClrUsed = SIZE; // 0;
  bfh.biClrImportant = SIZE; // 0;

  write_hdr(hdr, &hdr_idx, bfh.bfType1, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfType2, sizeof(uint8));
  write_hdr(hdr, &hdr_idx, bfh.bfSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved1, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved2, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.bfOffBits, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSize, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biWidth, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biHeight, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biPlanes, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biBitCount, sizeof(uint16));
  write_hdr(hdr, &hdr_idx, bfh.biCompression, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biSizeImage, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biXPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biYPelsPerMeter, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrUsed, sizeof(uint32));
  write_hdr(hdr, &hdr_idx, bfh.biClrImportant, sizeof(uint32));


  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      //tempGSImage[SIZE-1-i][SIZE-1-j] = outputImage[i][j];
	tempGSImage[SIZE-1-i][j] = outputImage[i][j];
    }
  }

  // write result bmp file
  if (!(file=fopen(filename,"wb")))
    {
      cout << "Cannot open file: " << filename << endl;
      return(1);
    }
  uint8 z = 0;
  fwrite(&hdr, sizeof(unsigned char), 0x36, file);
  for(i=0; i < SIZE; i++){
     uint8 x = (uint8) i;
    //cout << (int)x << endl;
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&x, sizeof(uint8), 0x01, file);
    fwrite(&z, sizeof(uint8), 0x01, file);

  }
  fwrite(tempGSImage, sizeof(unsigned char), SIZE*SIZE, file);
  fclose(file);

  return 0;
}



int shows = 0;

void show() {
    string command = "\\tmp\\bmplib.bmp";
    char cwd[PATH_MAX];
    system(strcat(getcwd(cwd, sizeof(cwd)), command.c_str()));
    usleep(200000);
    shows++;
}


void showRGBBMP(unsigned char inputImage[][SIZE][RGB]) {
  writeRGBBMP("./tmp/bmplib.bmp", inputImage);
  show();
}

void showGSBMP(unsigned char inputImage[][SIZE]) {
  writeGSBMP("./tmp/bmplib.bmp", inputImage);
  show();
}
