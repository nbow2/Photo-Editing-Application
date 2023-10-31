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
unsigned char ImageG[SIZE][SIZE] ;
unsigned char image1[SIZE][SIZE];


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
void Shuffle();
void crop();
void skew();

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
bool valid(string& str, int no_of_choices) {                     ////////////////////////////
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

void load_image2()
{
    char filename[100] ;
    cout << "Please Enter Your File Name: " ;
    cin >> filename ;
    strcat (filename, ".bmp") ;
    readGSBMP(filename,image1) ;
}


void loadimage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, ImageG);
    readGSBMP(imageFileName, image1);
}

//_________________________________________
void saveimage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, ImageG);
}

void saveimage2(){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image1);

}





/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    loadimage();
    int a;

    while (true) {
    cout << "Welcome to the photo editing program\n";
    cout << "0 for Exit \n";
    cout << "1 for Back and White Image  --\n";
    cout << "2 for Flip Image  --\n";
    cout << "3 for Blur Image -- \n";
    cout << "4 for invert Image --\n";
    cout << "5 for light or Darken Image --\n";
    cout << "6 for detect Image --\n";
    cout << "7 for enlarge Image --\n";
    cout << "8 for merge Image --\n";
    cout << "9 for rotate image -- \n";
    cout << "10 for shrink Image --\n";
    cout << "11 for Mirror Image --\n";
    cout << "12 for Shuffle Image -- \n";
    cout << "13 for crop Image  \n";
    cout << "14 for Skew Image --\n";
    cout << "15 for save Image --\n";

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

            flip();
            saveimage();
            break;
        case 3:

            blur();
            saveimage();
            break;
        case 4:

            invert();
            saveimage();
            break;
        case 5:

            lightorblack();
            saveimage();
            break;
        case 6:

            detect();
            saveimage();
            break;
        case 7:

            enlarge();
            saveimage();
            break;
        case 8:
            load_image2();
            merge();
            saveimage();
            break;
        case 9:

            rotatede();
            saveimage2();
            break;
        case 10:

            shrink();
            saveimage2();
            break;
        case 11:

            mirror();
            saveimage2();
            break;
        case 12:

            Shuffle();
            saveimage2();
            break;
        case 13:

            crop();
            saveimage();
            break;
        case 14:

            skew();
            saveimage();
            break;


        default:
            break;

    }
}

    return 0;
}


void blackwhite(){
    cout << " This Black white filter" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(ImageG[i][j] > 127) {
                ImageG[i][j] = 255;
            }
            else {
                ImageG[i][j] = 0;
            }
        }
    }
}
void flip (){
    unsigned char temp[SIZE][SIZE];
    int width = SIZE;
    int height = SIZE;
    cout<<"1 for vertical 2 for Horizontal \n ";
    int s ;
    cin>> s;

    ///////////////////////////////////////////
    ////////////for vertical image////////////
    if (s == 1 ) {


        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                temp[col][row] = ImageG[row][width - col - 1];
            }
        }

        // Copy the flipped image back to the original image buffer
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                ImageG[col][row] = temp[row][col];
            }
        }
    }
    ///////////////////////////////////////////////
    ////////for horizontal image//////////////////
    if (s == 2 ){
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                temp[row][col] = ImageG[height - row - 1][col];
            }
        }

        // Copy the flipped image back to the original image buffer
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                ImageG[row][col] = temp[row][col];
            }
        }
    }
    else{
        cout<<" pls Enter 1 or 2 \n";
    }
}
void blur (){
    int width = SIZE;
    int height = SIZE;
    unsigned char tempImage[SIZE][SIZE];
    unsigned char avgValue ;

    // Iterate through the image pixels
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
// Calculate the average grayscale value of the pixel and its surrounding pixels (3x3 neighborhood)
            unsigned int sum = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    sum += ImageG[y + i][x + j];
                }
            }
             avgValue = static_cast<unsigned char>(sum / 9);

// Store the averaged value in the temporary image
            tempImage[y][x] = avgValue;
        }
    }
// Copy the blurred result back to the original image
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            ImageG[y][x] = tempImage[y][x];
        }
    }


}
void invert(){

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (ImageG[i][j] == 255)
            {
                ImageG[i][j] = 0 ;
            }
            else if (ImageG[i][j] == 0 )
            {
                ImageG[i][j] = 255 ;
            }
            else
            {
                ImageG[i][j] = 255 - ImageG[i][j];
            }

        }
    }


}
void lightorblack(){

    cout<<"1 for Light 2 for Black \n";
    int a ;
    cin>>a;
    ////////////////////////////////////
    //////for light or black Image/////
    if (a == 1){

        ///////////////////////////////////
        /////////for light image /////////
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){


                if (ImageG [i][j] >=206){
                    ImageG [i][j] = 200;
                }
                else ImageG [i][j] +=50;
            }
            /////////////////////////////
            //////////for black Image////
        }
    }
    if (a == 2 )
    {
        for (int i =0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){


                if (ImageG [i][j] <= 50){
                    ImageG [i][j] = 0;

                }
                else ImageG [i][j] -= 50 ;
            }
        }
    }
    else {cout<<" pls Enter 1 or 2  \n"; cin>>a;}

}
void detect (){

    for (int i = 0; i < 255; i++) {
        for (int j =0; j < 256; j++) {
            if (abs(ImageG[i][j]- ImageG[i][j+1] > 24)){
                ImageG[i][j] = 0;
            }
            else {

                ImageG[i][j] = 255;
            }
        }
    }

}
void enlarge(){
    int no_of_choices = 4, choice;
    string choices;
    unsigned char chosenQuarter[SIZE][SIZE];

    while (true)
    {
        cout << "Which quarter of the image would you like to enlarge:\n";
        cout << "1 for First Quarter\n2 for Second Quarter\n3 for Third Quarter\n4 for Fourth Quarter\n";
        cout << "Please enter your choice, either 1 or 2 or 3 or 4\n>>";
        getline(cin, choices);
        if (valid(choices, no_of_choices))
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
                    chosenQuarter[i][j] = ImageG[(i / 2)][(j / 2) - SIZE / 2]; //first quartile
                    break;
                }
                case 2:
                {
                    chosenQuarter[i][j] = ImageG[i / 2][j / 2 - SIZE]; //second quartile
                    break;
                }
                case 3:
                {
                    chosenQuarter[255 - i][255 - j] = ImageG[SIZE - i / 2][SIZE - j / 2]; //third quartile
                    break;
                }
                case 4:
                {
                    chosenQuarter[SIZE - i][j - SIZE] = ImageG[SIZE - i / 2][j / 2];// forth quartile
                    break;
                }
                default:
                    break;
            }

        }
    }
}
void merge() {

    for (int i = 0 ; i < SIZE ; i ++)
    {
        for (int j = 0 ; j < SIZE ; j ++)
        {
            ImageG[i][j] = (ImageG[i][j]+image1[i][j]) / 2 ;
        }
    }
}
void rotatede() {
    using namespace std;

    int choice;
    cout << "would you like to :\n"
         << "1_Rotate (90)  degrees \n"
         << "2_Rotate (180) degrees \n"
         << "3_Rotate (270) degrees \n";
    cin >> choice;
    if (choice == 1) {
        ////////////////////////////////////
        /////////// Rotate 90 /////////////
        for (int i = 0 ; i < SIZE ; i ++)
        {
            for (int j = 0 ; j < SIZE ; j ++)
            {

                image1[i][j] = ImageG[j][SIZE-i]  ;

            }
        }


    } else if (choice == 2) {
        ////////////////////////////////////
        /////////// Rotate 180 /////////////

        for (int i = 0 ; i < SIZE ; i ++)
        {
            for (int j = 0 ; j < SIZE ; j ++)
            {
                image1[i][j] =ImageG[SIZE-i-1][SIZE-j-1] ;


            }
        }

    } else if (choice == 3) {

        ////////////////////////////////////
        /////////// Rotate 270 /////////////
        for (int i = 0 ; i < SIZE ; i ++)
        {
            for (int j = 0 ; j < SIZE ; j ++)
            {

                image1[i][j]=ImageG[SIZE-j][i];


            }
        }


    }

}
void shrink()
{
    int skiprow = 0 , skipcolumn = 0 ;
    int shrink_value  , new_size ;

    cout << "enter shrinking value: \n pls Enter (2) or (3) of (4)\n" ;
    cin >> shrink_value ;

    new_size = SIZE /shrink_value ;
    for (int i = 0; i < new_size ; i ++)
    {

        for (int j = 0 ; j < new_size ; j ++)
        {
            image1[i][j] = ImageG[skiprow][skipcolumn] ;
            skipcolumn += shrink_value ;
        }
        skipcolumn = 0 ;
        skiprow += shrink_value ;



    }


}
void mirror(){

    int choice;
    cout << "Mirror left,or right,or upper,or down side?\n"
         <<"1 for Mirror left  \n"
         <<"2 for Mirror right \n"
         <<"3 for Mirror upper \n"
         <<"4 for Mirror down  \n";
    cin>>choice;
    if (choice == 1){
        ////////////////////////////
        ///// for Mirror left//////
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image1[i][j] = ImageG[i][j];
            }
        }
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE / 2; j < SIZE; j++) {
            image1[i][j] = ImageG[i][255 - j];
        }
    }

    }
    else if (choice ==2)
    {
        //////////////////////////
        ////for Mirror right/////
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image1[i][j] = ImageG[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image1[i][j] = ImageG[i][255 - j];
            }
        }

    }
    else if (choice ==3)
    {
        ///////////////////////////
        //////Mirror upper////////
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = ImageG[i][j];
            }
        }
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = ImageG[255 - i][j];
            }
        }

    }
    else if (choice ==4)
    {
     //////////////////////////////
     //////for Mirror Down////////
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1 [i][j] = ImageG[i][j];
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                image1[i][j] = ImageG[255 - i][j];
            }
        }

    }
}
void Shuffle(){

    bool check=true;
    int q1,q2,q3,q4;
    cout<<"Please enter the order of quarters you want: \n form 1 to 4 \n";
    cin>>q1;
    if(q1==1){
        for(int i=0;i<127;i++){
            for(int j=0;j<127;j++){
                image1[i][j] = ImageG[i][j];
            }
        }
    }
    else if(q1==2){
        for(int i=0;i<127;i++){
            for(int j=127;j<SIZE;j++){
                image1[i][j-127] = ImageG[i][j];
            }
        }
    }

    else if(q1==3){
        for(int r=127;r<SIZE;r++){
            for(int j=0;j<127;j++){
                image1[r-127][j] = ImageG[r][j];
            }
        }
    }
    else if(q1==4){
        for(int r=127;r<SIZE;r++){
            for(int j=127;j<SIZE;j++){
                image1[r-127][j-127] = ImageG[r][j];
            }
        }
    }

    cin>>q2;
    if(q2==1){
        for(int r=0;r<127;r++){
            for(int j=0;j<127;j++){
                image1[r][j+127] = ImageG[r][j];
            }
        }
    }
    else if(q2==2){
        for(int r=0;r<127;r++){
            for(int j=127;j<SIZE;j++){
                image1[r][j] = ImageG[r][j];
            }
        }
    }

    else if(q2==3){
        for(int r=127;r<SIZE;r++){
            for(int j=0;j<127;j++){
                image1[r-127][j+127] = ImageG[r][j];
            }
        }
    }
    else if(q2==4){
        for(int r=127;r<SIZE;r++){
            for(int j=127;j<SIZE;j++){
                image1[r-127][j] = ImageG[r][j];
            }
        }
    }
    cin>>q3;
    if(q3==1){
        for(int i=0;i<127;i++){
            for(int j=0;j<127;j++){
                image1[i+127][j] = ImageG[i][j];
            }
        }
    }
    else if(q3==2){
        for(int i=0;i<127;i++){
            for(int j=127;j<SIZE;j++){
                image1[i+127][j-127] = ImageG[i][j];
            }
        }
    }

    else if(q3==3){
        for(int i=127;i<SIZE;i++){
            for(int j=0;j<127;j++){
                image1[i][j] = ImageG[i][j];
            }
        }
    }
    else if(q3==4){
        for(int i=127;i<SIZE;i++){
            for(int j=127;j<SIZE;j++){
                image1[i][j-127] = ImageG[i][j];
            }
        }
    }
    cin>>q4;
    if(q4==1){
        for(int i=0;i<127;i++){
            for(int j=0;j<127;j++){
                image1[i+127][j+127] = ImageG[i][j];
            }
        }
    }
    else if(q4==2){
        for(int i=0;i<127;i++){
            for(int j=127;j<SIZE;j++){
                image1[i+127][j] = ImageG[i][j];
            }
        }
    }

    else if(q4==3){
        for(int i=127;i<SIZE;i++){
            for(int j=0;j<127;j++){
                image1[i][j+127] = ImageG[i][j];
            }
        }
    }
    else if(q4==4){
        for(int i=127;i<SIZE;i++){
            for(int j=127;j<SIZE;j++){
                image1[i][j] = ImageG[i][j];
            }
        }
    }
    else {
        cin.clear();
        cin.ignore();
        cout<<"Please enter available quarter "<< endl ;

        Shuffle();

    }
}

void skew(){
    string direction;
    cout <<"Enter 'h' to skew horizontally or 'v' to skew vertically : ";
    cin >> direction;
    cout << "Enter the degree : \n";
    double rad;
    cin >> rad;
    rad = (rad * 22) / (180 * 7);
    unsigned char shrink[SIZE][SIZE];
    unsigned char skew[SIZE][SIZE];
    int x = (tan(rad) * 256) / (tan(rad) + 1);;
    double step = SIZE - x;
    double move = step / SIZE;

    if (direction == "h") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                shrink[i][(j * x) / SIZE] = ImageG[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                ImageG[i][j] = shrink[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                skew[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = (int) step; j < step + x; j++) {
                skew[i][j] = shrink[i][(int) (j - step)];
            }
            step -= move;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                ImageG[i][j] = skew[i][j];
            }
        }
    }

    else if (direction == "v") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                shrink[j][(i * x) / SIZE] = ImageG[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                ImageG[i][j] = shrink[i][j];
            }
        }

        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                skew[j][i] = 255;
            }
        }
        for (int j = 0; j < SIZE; j++) {
            for (int i = (int) step; i < step + x; i++) {
                skew[i][j] = shrink[j][(int) (i - step)];
            }
            step -= move;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                ImageG[i][j] = skew[i][j];
            }
        }
    }
}

void  crop() {
    int x, y, length, width;
    cout << " Enter the x position for cutting: ";
    cin >> x;

    cout << "Enter the y position for cutting: ";
    cin >> y;

    cout << "Enter the square of the length: ";
    cin >> length;

    cout << "Enter the square of width: ";
    cin >> width;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ImageG[i][j] = 255;
        }
    }
    for (int i = x; i < length; i++) {
        for (int j = y; j < width; j++) {
            ImageG[i][j] = image1[x + i][y + j];
        }

    }
}
