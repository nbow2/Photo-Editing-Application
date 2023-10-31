/*
FCI - Programming 1 - 2023 - Assignment 3
Program Name: Photo Editing Application
Last Modification Date: 9/10/2023
Author1 and ID and Group: Ahmed dafalla mohamed Abdalla , 20210912 , nmawg22@gmail.com
Author2 and ID and Group: Omar Sayedna Ali Salih , 20210703 ,
Author3 and ID and Group: Faisal Ahmed Awad ,20210804 ,

Purpose: Perform 6 filters on gray scale photos and auto save only

Phase 2: All 12 filters and save function are ready. ان شاء الله
 */
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include "bmplib.h"
using namespace std ;

using namespace std ;
unsigned char ImageG[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];


void flip();
void blackwhite();
void blur();
void invert();
void lightorblack();
void detect();
void enlarge();
void merge();
void rotatede();
void mirror();
void shrink();
void shuffle();

////------------------------------------------------------

void loadimage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, ImageG);
}

void loadimage2(){

    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image1);
}

//_________________________________________
void saveimage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, ImageG);
}

void saveimage2(){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image1);

}
///----------------------------------------------------------

int main() {

    while (true) {
    int a;
    loadimage();
    cout << "Welcome to the photo editing program\n";
    cout << "0 for Exit \n";
    cout << "1 for Black and white Image-- \n";
    cout << "2 for Invert Image-- \n";
    cout << "3 for merge Image--\n";
    cout << "4 for flip Image-- \n";
    cout << "5 for rotate Image-- \n";
    cout << "6 for light or black image--\n";
    cout << "7 for detect image-- \n";
    cout << "8 for enlarge Image \n";
    cout << "9 for shrink Image- \n";
    cout << "10 for mirror Image-- \n";
    cout << "11 for shuffle Image--\n";

    cin >> a;

    switch (a) {
        case 0:
            exit(true);
            break;
        case 1:

            blackwhite();
            saveimage();
            break;
        case 2:

            invert();
            saveimage();
            break;
        case 3:

            merge();
            saveimage();
            break;
        case 4:

            flip();
            saveimage2();
            break;
        case 5:

            rotatede();
            saveimage2();
            break;
        case 6:

            lightorblack();
            saveimage();
            break;
        case 7:

            detect();
            saveimage2();
            break;
        case 8:

            enlarge();
            saveimage();
            break;
        case 9:

            shrink();
            saveimage2();
            break;
        case 10:

            mirror();
            saveimage2();
            break;
        case 11:

            shuffle();
            saveimage2();
            break;


        default:
            break;

    }
}
    return 0;
}

void blackwhite(){
    long avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg = (ImageG[i][j][0] + ImageG[i][j][1] + ImageG[i][j][2])/3;
            for (int k =0; k< RGB; k++){
                ImageG[i][j][k] =avg;
                if (ImageG[i][j][k] > 127)
                    ImageG[i][j][k] = 255;
                else
                    ImageG[i][j][k] = 0;
            }
        }
    }
}
void invert(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                ImageG[i][j][k] = 255 - ImageG[i][j][k];
            }
        }
    }
}
void merge() {

    loadimage2();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                ImageG[i][j][k] = (ImageG[i][j][k] + image1[i][j][k]) / 2;
            }
        }
    }
}
void flip(){

    int x = 255;
    int y= 255;
    bool isChoiceVH {true};
    string h_v;

    while (isChoiceVH) {

        // Get choice between Vertical and Horizontal
        cout << "Choose Vertical Flip filter or Horizontal Flip filter.\n"
             << "Input v for Vertical Flip filter.\n" << "Input h for Horizontal Flip filter.\n"
             << "Flip of choice: \n";
        cin >> h_v;

        // Flip image vertically
        if (h_v == "v"){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for(int k=0; k<RGB;k++){
                        image1[x][j][k] = ImageG[i][j][k];
                    }
                }
                x--;
            }

            isChoiceVH = false;
        }

            // Flip image horizontally
        else if (h_v == "h") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for(int k = 0; k < RGB; k++){
                        image1[i][y][k]= ImageG[i][j][k];
                    }
                    y--;
                    if (y == 0)
                        y+= SIZE;
                }
            }

            isChoiceVH = false;
        } else {
            cout << setfill('-') << setw(10) << " "
                 << "Wrong input, please try again"
                 << setfill('-') << setw(10) << "\n";
        }
    }
}
void rotatede() {

    string degrees;
    bool isChoiceDeg{true};

    while (isChoiceDeg) {

        //Get the rotation degree of the image
        cout << "Choose (90) degrees, (180) degrees or (270) degrees filter.\n"
             << "input 90 or 180 or 270 to choose degrees: \n";
        cin >> degrees;

        //Rotate 90 Degrees
        if (degrees == "90") {
            for (int i = 0; i < SIZE; i++){
                for (int j = 255; j > 0; j--){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[j][-i][k];
                    }
                }
            }

            isChoiceDeg = false;
        }

            //Rotate 180 Degrees
        else if (degrees == "180") {
            int x = 255;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < RGB; k++){
                        image1[x][j][k]= ImageG[i][-j][k];
                    }
                }
                x--;
            }

            isChoiceDeg = false;
        }

            //Rotate 270 Degrees
        else if (degrees == "270") {
            for (int i = 0; i < SIZE; i++){
                for (int j = 255; j > 0; j--){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[255 - j][i - 255][k];
                    }
                }
            }

            isChoiceDeg = false;
        } else {
            cout << setfill( '-' ) << setw( 10) << " "
                 <<"Wrong input, please try again"
                 <<setfill( '-' ) << setw( 10) << "\n" ;
        }
    }
}
void lightorblack() {
    string darkOrLight;
    bool isDarkOrLight {true};

    while (isDarkOrLight) {
        cout << "Choose Darken filter or Lighten filter.\n"
             << "Input d for Darken filter\n" << "Input l for Lighten filter\n"
             << "Brightness of choice:\n";
        cin >> darkOrLight;

        // darken image by 50%
        if (darkOrLight == "d") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        ImageG[i][j][k] = (ImageG[i][j][k])/2;
                    }
                }
            }
            isDarkOrLight = false;
        }
            // lighten image by 50%
        else if (darkOrLight == "l") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        ImageG[i][j][k] = (ImageG[i][j][k])/2 + 127;
                    }
                }
            }
            isDarkOrLight = false;
        } else {
            cout << setfill( '-' ) << setw( 10) << " "
                 <<"Wrong input, please try again"
                 <<setfill( '-' ) << setw( 10) << "\n" ;
        }
    }
}
void detect(){

    long avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg = (ImageG[i][j][0] + ImageG[i][j][1] + ImageG[i][j][2])/3;
            for (int k =0; k< RGB; k++){
                ImageG[i][j][k] =avg;
                if (ImageG[i][j][k] > 127)
                    ImageG[i][j][k] = 255;
                else
                    ImageG[i][j][k] = 0;
            }
        }
    }
    for(int i=0 ; i<SIZE ;i++){
        for(int j=0 ;j<SIZE ;j++){
            for (int k = 0; k < RGB; ++k) {
                image1[i][j][k] = ImageG[i+1][j][k] + ImageG[i][j+1][k] + ImageG[i-1][j][k] +
                                     ImageG[i][j-1][k] - 4*(ImageG[i][j][k]);
            }
        }
    }

}


void enlarge() {

    bool isChoiceEnlarge{true};
    int qrt;

    while (isChoiceEnlarge) {

        cout << "Choose Quarter:\n"
             << "For top left quarter input 1\n"
             << "For top right quarter input 2\n"
             << "For down left quarter input 3\n"
             << "For down right quarter input 4\n"
             << "Please enter quarter of choice:\n";
        cin >> qrt;
        if (qrt == 1) {
            for (int i = 0; i < 128; i++){
                for (int j = 0; j < 128; j++){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[2 * i][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i][2 * j + 1][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j + 1][k];
                    }
                }
            }

            isChoiceEnlarge = false;
        } else if (qrt == 2) {
            for (int i = 0; i < 128; i++){
                for (int j = 128; j < 256; j++){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[2 * i][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i][2 * j + 1][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j + 1][k];
                    }
                }
            }

            isChoiceEnlarge = false;
        } else if (qrt == 3) {
            for (int i = 128; i < 256; i++){
                for (int j = 0; j < 128; j++){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[2 * i][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i][2 * j + 1][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j + 1][k];
                    }
                }
            }

            isChoiceEnlarge = false;
        } else if (qrt == 4) {
            for (int i = 127; i < 256; i++){
                for (int j = 128; j < 256; j++){
                    for (int k = 0; k < RGB; k++){
                        image1[i][j][k] = ImageG[2 * i][2 * j][k] ;
                        image1[i][j][k] = ImageG[2 * i][2 * j + 1][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j][k];
                        image1[i][j][k] = ImageG[2 * i + 1][2 * j + 1][k];
                    }
                }
            }

            isChoiceEnlarge = false;
        } else {
            cout << setfill( '-' ) << setw( 10) << " "
                 <<"Wrong input, please try again"
                 <<setfill( '-' ) << setw( 10) << "\n" ;
        }
    }
}

void shrink(){

    bool isChoiceShrink{true};
    int sizeOfShrink;

    while (isChoiceShrink) {
        int x = 0;
        int y = 0;
        cout << "Choose Shrink size\n"
             << "Shrink to 1/2 input 1\n"
             << "Shrink to 1/3 input 2\n"
             << "Shrink to 1/4 input 3\n"
             << "Please enter shrink size of choice:\n";
        cin >> sizeOfShrink;

        if (sizeOfShrink == 1 ) {
            for (int i = 0 ; i < SIZE/2 ; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    for (int k = 0; k < RGB; k++) {
                        image1[i][j][k - 2] = ImageG[y][x][k - 2];
                        image1[i][j][k - 1] = ImageG[y][x][k - 1];
                        image1[i][j][k] = ImageG[y][x][k];
                    }
                    x += 2;
                }
                y += 2;
            }

            isChoiceShrink = false;
        } else if (sizeOfShrink == 2 ) {
            for (int i = 0 ; i < SIZE/3 ; i++){
                for (int j = 0 ; j < SIZE/3 ; j++){
                    for (int k = 0 ; k < RGB ; k++){
                        image1[i][j][k-2] = ImageG[y][x][k-2];
                        image1[i][j][k-1] = ImageG[y][x][k-1];
                        image1[i][j][k] = ImageG[y][x][k];
                    }
                    y += 3;
                }
                x += 3;
            }

            isChoiceShrink = false;
        } else if (sizeOfShrink == 3 ) {
            for (int i = 0 ; i < SIZE/4 ; i++){
                for (int j = 0 ; j < SIZE/4 ; j++){
                    for (int k = 0 ; k < RGB ; k++){
                        image1[i][j][k-2] = ImageG[y][x][k-2];
                        image1[i][j][k-1] = ImageG[y][x][k-1];
                        image1[i][j][k] = ImageG[y][x][k];
                    }
                    y += 4;
                }
                x += 4;
            }

            isChoiceShrink = false;
        } else {
            cout << setfill( '-' ) << setw( 10) << " "
                 <<"Wrong input, please try again"
                 <<setfill( '-' ) << setw( 10) << "\n" ;
        }
    }
}

void mirror() {

    int mirrorSide;
    int x = 255;
    bool isChoiceMirrorSide{true};
    while (isChoiceMirrorSide) {
        cout << "Choose half to mirror:\n"
             << "for Left 1\n"
             << "for Right 2 \n"
             << "for Up 3 \n"
             << "for Down 4 \n"
             << "Which half would you like to mirror:\n";
        cin >> mirrorSide;
        if (mirrorSide == 1) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < (SIZE/2); j++) {
                    for (int k =0; k< RGB; k++){
                        image1[i][j][k]= ImageG[i][j][k];
                        image1[i][x][k]= ImageG[i][j][k];
                    }
                    x--;
                    if (x==127)
                        x+=(SIZE/2);
                }
            }

            isChoiceMirrorSide = false;
        } else if (mirrorSide == 2) {
            int y = (SIZE/2);
            for (int i = 0; i < SIZE; i++) {
                for (int j = (SIZE/2); j <SIZE; j++) {
                    for (int k =0; k< RGB; k++){
                        image1[i][j][k]= ImageG[i][j][k];
                        image1[i][y][k]= ImageG[i][j][k];
                    }
                    y--;
                    if (y==0)
                        y+=(SIZE/2);
                }
            }

            isChoiceMirrorSide = false;
        } else if (mirrorSide == 3) {
            for (int i = 0; i < (SIZE/2); i++){
                for (int j = 0; j < SIZE; j++){
                    for (int k =0; k< RGB; k++){
                        image1[i][j][k]= ImageG[i][j][k];
                        image1[x][j][k]= ImageG[i][j][k];
                    }
                }
                x--;
            }

            isChoiceMirrorSide = false;
        } else if (mirrorSide == 4 ) {
            int z =127;
            for (int i = (SIZE/2); i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k =0; k< RGB; k++){
                        image1[i][j][k]= ImageG[i][j][k];
                        image1[z][j][k]= ImageG[i][j][k];
                    }
                }
                z--;
            }

            isChoiceMirrorSide = false;
        } else {
            cout<< setfill( '-' ) << setw( 10) << " "
                <<"Wrong input, please try again"
                <<setfill( '-' ) << setw( 10) << "\n" ;
        }
    }
}
void shuffle() {
    unsigned char first_qrt[SIZE/2][SIZE/2][RGB];
    unsigned char second_qrt[SIZE/2][SIZE/2][RGB];
    unsigned char third_qrt[SIZE/2][SIZE/2][RGB];
    unsigned char fourth_qrt[SIZE/2][SIZE/2][RGB];

    for (int i = 0; i < SIZE/2; i++){
        for (int j = 0; j < SIZE/2; j++){
            for (int k = 0; k < RGB; k++){
                first_qrt[i][j][k] = ImageG[i][j][k];
            }
        }
    }
    for (int i = 0, x = 0; i < SIZE/2; i++, x++){
        for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
            for (int k = 0; k < RGB; k++){
                second_qrt[x][y][k] = ImageG[i][j][k];
            }
        }
    }
    for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
        for (int j = 0, y = 0; j < SIZE/2; j++, y++){
            for (int k = 0; k < RGB; k++){
                third_qrt[x][y][k] = ImageG[i][j][k];
            }
        }
    }
    for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
        for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
            for (int k = 0; k < RGB; k++){
                fourth_qrt[x][y][k] = ImageG[i][j][k];
            }
        }
    }

    int qrt1_pos, qrt2_pos, qrt3_pos, qrt4_pos;

    cout<<"for 1 to 4 \n";
    cout << "First Quarter Position: ";
    cin >> qrt1_pos;

    cout << "Second Quarter Position: ";
    cin >> qrt2_pos;

    cout << "Third Quarter Position: ";
    cin >> qrt3_pos;

    cout << "Fourth Quarter Position: ";
    cin >> qrt4_pos;

    if (qrt1_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = first_qrt[x][y][k];
                }
            }
        }
    }else if (qrt1_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = first_qrt[x][y][k];
                }
            }
        }
    }else if (qrt1_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = first_qrt[x][y][k];
                }
            }
        }
    }else if (qrt1_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = first_qrt[x][y][k];
                }
            }
        }
    }

    if (qrt2_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = second_qrt[x][y][k];
                }
            }
        }
    }else if (qrt2_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = second_qrt[x][y][k];
                }
            }
        }
    }else if (qrt2_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = second_qrt[x][y][k];
                }
            }
        }
    }else if (qrt2_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = second_qrt[x][y][k];
                }
            }
        }
    }

    if (qrt3_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = third_qrt[x][y][k];
                }
            }
        }
    }else if (qrt3_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = third_qrt[x][y][k];
                }
            }
        }
    }else if (qrt3_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = third_qrt[x][y][k];
                }
            }
        }
    }else if (qrt3_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = third_qrt[x][y][k];
                }
            }
        }
    }

    if (qrt4_pos == 1){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = fourth_qrt[x][y][k];
                }
            }
        }
    }else if (qrt4_pos == 2){
        for (int i = 0, x = 0; i < SIZE/2; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = fourth_qrt[x][y][k];
                }
            }
        }
    }else if (qrt4_pos == 3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = 0, y = 0; j < SIZE/2; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = fourth_qrt[x][y][k];
                }
            }
        }
    }else if (qrt4_pos == 4){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x++){
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y++){
                for (int k = 0; k < RGB; k++){
                    image1[i][j][k] = fourth_qrt[x][y][k];
                }
            }
        }
    }

}



