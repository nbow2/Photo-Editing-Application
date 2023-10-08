/*
FCI - Programming 1 - 2022 - Assignment 3
Program Name: Photo Editing Application
Last Modification Date: 9/10/2022
Author1 and ID and Group: Ahmed dafalla mohamed Abdalla , 20210912
Author2 and ID and Group: Omar Sayedna Ali Salih , 20210703
Author3 and ID and Group:

Purpose: Perform 6 filters on gray scale photos only

Phase 2: All 12 filters are ready. ان شاء الله
 */
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include "bmplib.h"

using namespace std ;
unsigned char ImageG[SIZE][SIZE] ;
unsigned char ImageRG[SIZE][SIZE][RGB];
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
bool isvalid(string& str, int no_of_choices) {                     ////////////////////////////
    bool con = false;                                             ////////////////////////////
    int range_checker;                                            ////////////////////////////
    if (no_of_choices == 14) {                                    ////////////////////////////
        regex isvalid("[0-9]+");                               ////////////////////////////
        if ((regex_match(str, isvalid))) {
            range_checker = stoi(str);
            if (range_checker <= 14 and range_checker > 0)
                con = true;
        }
    } else if (no_of_choices == 2) {
        regex isvalid("[1-2]");
        con = regex_match(str, isvalid);
    } else if (no_of_choices == 3) {
        regex isvalid("[1-3]");
        con = regex_match(str, isvalid);
    } else if (no_of_choices == 4) {
        regex isvalid("[1-4]");
        con = regex_match(str, isvalid);
    } else if (no_of_choices == 0) {
        regex isvalid("[0-9]+");
        con = regex_match(str, isvalid);                        ////////////////////////////
    }                                                                 ////////////////////////////
    return con;                                                      ////////////////////////////
}                                                                   ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

static void fFliter(unsigned char image[][SIZE]) {
    unsigned char temp[SIZE][SIZE];
    unsigned char tempImage[SIZE][SIZE];
    int width = SIZE;
    int height = SIZE;

    int Ae ;
    cout<<"1 for Flip Image   \n";
    cout<<"2 for Blur image \n";
    cout<<"3 for invert image \n";
    cout<<"4 for light or black Image \n";
    cout<<"5 for detect image edges \n";
    cout<<"6 for Enlarge Image \n";
    cin>> Ae;

    switch (Ae) {
        case 1 :
            ///////////////////////////////////////////
            //////////for flip image /////////////////
            cout<<"1 for vertical 2 for Horizontal \n ";
            int s ;
            cin>> s;
            if (s == 1 ) {


                for (int row = 0; row < height; row++) {
                    for (int col = 0; col < width; col++) {
                        temp[col][row] = image[row][width - col - 1];
                    }
                }

                // Copy the flipped image back to the original image buffer
                for (int row = 0; row < height; row++) {
                    for (int col = 0; col < width; col++) {
                        image[col][row] = temp[row][col];
                    }
                }
            }
            if (s == 2 ){
                for (int row = 0; row < height; row++) {
                    for (int col = 0; col < width; col++) {
                        temp[row][col] = image[height - row - 1][col];
                    }
                }

                // Copy the flipped image back to the original image buffer
                for (int row = 0; row < height; row++) {
                    for (int col = 0; col < width; col++) {
                        image[row][col] = temp[row][col];
                    }
                }
            }
            else{
                cout<<" pls Enter 1 or 2 \n";
            }
            break;

        case 2:

            //////////////////////////////////////////
            ////////for BLur image///////////////////

            // Iterate through the image pixels
            for (int y = 1; y < height - 1; ++y) {
                for (int x = 1; x < width - 1; ++x) {
// Calculate the average grayscale value of the pixel and its surrounding pixels (3x3 neighborhood)
                    unsigned int sum = 0;
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            sum += image[y + i][x + j];
                        }
                    }
                    unsigned char avgValue = static_cast<unsigned char>(sum / 9);

// Store the averaged value in the temporary image
                    tempImage[y][x] = avgValue;
                }
            }
// Copy the blurred result back to the original image
            for (int y = 1; y < height - 1; ++y) {
                for (int x = 1; x < width - 1; ++x) {
                    image[y][x] = tempImage[y][x];
                }
            }
            break;
        case 3:

            //////////////////////////////////
            ///////for invert image//////////

            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[j][i] = 255 - image[j][i];
                }
            }
            break;
        case 4:
            cout<<"1 for black 2 for Light \n";
            int a ;
            cin>>a;
            ////////////////////////////////////
            //////for light or black Image/////
            if (a == 1){
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++){


                    if (image [i][j] >=206){
                        image [i][j] = 200;
                    }
                    else image [i][j] +=50;
                }
            }} else
            {
                for (int i =0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){


                        if (image [i][j] <= 50){
                            image [i][j] = 0;

                        }
                        else image [i][j] -= 50 ;

                    }
                }
            }
            break;
        case 5:

            ///////////////////////////////////
            ////// for detect image edges/////
            /////////       90%      ////////
            for (int i = 0; i < 255; i++) {
                for (int j =0; j < 256; j++) {
                    if (abs(image[i][j]- image[i][j+1] > 24)){
                        image[i][j] = 0;
                    }
                    else {

                        image[i][j] = 255;
                    }
                }
            }
            break;
        case 6:

            ///////////////////////////////
            ///////for Enlarge Image//////
            int no_of_choices = 4, choice;
            string choices;
            unsigned char chosenQuarter[SIZE][SIZE];

            while (true)
            {
                cout << "Which quarter of the image would you like to enlarge:\n";
                cout << "1- First Quarter\n2- Second Quarter\n3- Third Quarter\n4- Fourth Quarter\n";
                cout << "Please enter your choice, either 1 or 2 or 3 or 4\n>>";
                getline(cin, choices);
                if (isvalid(choices, no_of_choices))
                {
                    choice = stoi(choices);
                    break;
                }
                else
                    cout << "Invalid Input\n";
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {

                    switch (choice) {
                        case 1:
                        {
                            chosenQuarter[i][j] = image[(i / 2)][(j / 2) - SIZE / 2]; //first quartile
                            break;
                        }
                        case 2:
                        {
                            chosenQuarter[i][j] = image[i / 2][j / 2 - SIZE]; //second quartile
                            break;
                        }
                        case 3:
                        {
                            chosenQuarter[255 - i][255 - j] = image[SIZE - i / 2][SIZE - j / 2]; //third quartile
                            break;
                        }
                        case 4:
                        {
                            chosenQuarter[SIZE - i][j - SIZE] = image[SIZE - i / 2][j / 2];// forth quartile
                            break;
                        }
                    }

                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    image[i][j] = chosenQuarter[i][j];
                }
            }

            break;

    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    std::cout << "Hello, World!" << std::endl;
   //it gave my the path for image
   // cout<<getcwd(cwd,sizeof (cwd)) ;

    string imageName , path = "\\image\\";
    cout<<"Enter image Name :\n";
    cin>>imageName;
    path += imageName ; //imageName mario.bmp
    char cwd [PATH_MAX];

    int num ;
    cout<<"Is the image ( 1 for Gray) or( 2 for RBG ) \n";
    cin>>num;


    switch (num) {
        case  1 :
            // for Gray images
            readGSBMP( strcat(getcwd(cwd, sizeof(cwd)), path.c_str()),ImageG);
            fFliter(ImageG);
           // convertToBW(ImageG);
            showGSBMP(ImageG);

            break;
        case 2:
            // for RBG images
            readRGBBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()),ImageRG);
            showRGBBMP(ImageRG);
            break;
        default:
            cout<<"pls Enter 1 or 2 \n";
            break;
    }
    return 0;
}


