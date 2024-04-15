#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
using namespace std;
/*
file name :CS112_A3_Part2_S23-S24_20230082_20221186_.cpp
file purpose : this is a program that has 12 filters to apply on images .
section number: S23-S24
Team members:
1-Ayman Mohamed El-Shahat Moharam
ID:20230082
Email:ayman.elshahat01@gmail.com
* did the filters number 3,5,6,8,9,11,12, and the menu *

2-Nourhan Sayed Ramadan Ali 
ID:20221186
* did the filters number 1 ,2, 4 , 7 , 10*


*/
int menu();
string loadImage();
bool fileExists(string filename);
void saveImage(Image picture);
void BlackAndWhite(Image &picture);
void GrayConvert(Image &picture);
void invertColores(Image &picture);
void mergeImages(Image &image1);
Image resizeImage(Image img , double width , double height);
Image hFlip(Image img);
Image vFlip(Image img);
Image rotate270(Image img);
Image rotate180(Image img);
Image rotate90(Image img);
void lightenImage(Image &img);
void darkenImage(Image &img);
Image crop(Image img , int x , int y , int w , int h);
Image addFrameToImage(const Image& image, int borderWidth,  short int frameColor[3]);
void findEdges(Image &img);
Image blur( Image& img) ;



int main(){
    int option ;
    string image ;
    Image img;
    image = loadImage();
    img.loadNewImage(image);
    while(true){

    option = menu();
    if (option == 1 ){
        img.loadNewImage(loadImage());
        continue;
    }
    else if (option == 2 ){
        BlackAndWhite(img);
    }
    else if (option == 3){
        GrayConvert(img);
    
    }
    else if (option == 4){
        invertColores(img);
    }
    else if (option == 5){
        mergeImages(img);
    }
    else if (option == 6){
        int choice = 0 ;
        while (true){
        cout <<"    1-Horizontal flip \n";
        cout <<"    2-vertical flip \n";
        cout << "   Choose one of the above choices\n";
        cin >> choice;

        if (choice == 1){
           img = hFlip(img);
            break;
        }
        if (choice == 2){
            img = vFlip(img);
            break;
        }
        else {
            cout << "NOT A VALID CHOICE \n";
        }
        }
    
    }
    else if (option == 7){
        short int choice;
        while (true){
            
            cout << "1-rotate by 90 degrees \n";
            cout << "2-rotate by 180 degrees \n";
            cout << "3-rotate by 270 degrees \n";
            cin >> choice ;
            if (choice == 1){
                img = rotate90(img);
                break;
            }
            else if (choice == 2){
                img = rotate180(img);
                break;
            }
            else if (choice == 3 ){
                img = rotate270(img);
                break;
            }
            else {
                cout << "NOT A VALID CHOICE \n";
            }
    }
    }
    else if (option == 8){
        int choice ;
        while(true){
            cout << "1-Lighten image :\n";
            cout << "2-Darken image :\n";
            cin >> choice ;
            if (choice == 1 ){
                lightenImage(img);
                break;
            }

            else if (choice == 2){
                darkenImage(img);
                break;
            }

            else {
                cout << "NOT A VALID CHOICE \n";
            }

        }
    }

    else if (option == 9){
        int x,y,w,h;
        cout << "Enter the coordinates of the starting pixle separated by a space like this \"40 300\" :";
        cin >> x;
        cin >> y;
        cout << "Enter the desired dimensions separated by a space like this \"300 500\" :";
        cin >> w;
        cin >> h;
        img = crop( img , x , y , w , h );
        
    }

    else if (option == 10){
        int borderWidth;
         short int frameColor[3];
        cout << "Enter the desired border width : \n";
        cin >> borderWidth;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter the Red component of the desired frame color: ";
        cin >> frameColor[0];
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter the green component of the desired frame color: ";
        cin >> frameColor[1];
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
        cout << "Enter the blue component of the desired frame color: ";
        cin >> frameColor[2];
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        img = addFrameToImage(img , borderWidth , frameColor);
    }

    else if (option == 11){
        findEdges(img);
    }

    else if (option == 12){
        cout << "Enter the desired dimensions separated by spaces (e.g. 400 700)";
        double w,h;
        cin >> w;
        cin >> h;
        cout << w <<h;
        img = resizeImage(img , w, h);
    }

    else if (option == 13){
        img = blur(img);
    }

    else if(option == 14){
        saveImage(img);
        break;
    }

    else if (option == 15){
       break;
    }

    else {
        cout << "Not a valid choice \n";
    }

    }
}
int menu(){
    int option;
    cout << "1-Load new image: \n";
    cout << "2-Black and White: \n";
    cout << "3-Gray scaling: \n";
    cout << "4-Invert color : \n";
    cout << "5-Merge images : \n";
    cout << "6-Flip image: \n";
    cout << "7-rotate image: \n";
    cout << "8-Darken and Lighten image:  \n";
    cout << "9-Crop image:  \n";
    cout << "10-frame:  \n";
    cout << "11-Detect edges:  \n";
    cout << "12-Resize image  \n";
    cout << "13-blur image \n";
    cout << "14-save image \n";
    cout << "15-Exit  \n";
    cin >> option;
    return option;
    
}
void BlackAndWhite(Image &picture){
     for(int i = 0;i < picture.width;++i){
        for(int j = 0;j <picture.height;++j){
                unsigned int avg = 0;//store in avg
            for(int k = 0;k < 3;++k){
                avg += picture(i,j,k);
            }
           avg = avg /3.0;//division by 3
            for(int k = 0;k < 3;++k){
                if(avg>=127){
                    picture(i,j,k) = 255;
                    }//white
                
                else{
                    picture(i,j,k) = 0;
                    }//black
            }
        }
    }
}

void GrayConvert(Image &picture){
     for(int i = 0;i < picture.width;++i){

        for(int j = 0;j <picture.height;++j){
                unsigned int avg = 0;//store in avg
            for(int k = 0;k < 3;++k){
                avg += picture(i,j,k);
            }
           avg = avg /3;//division by 3
            for(int k = 0;k < 3;++k){
                picture(i,j,k) = avg;
            }
        }
    }
}

void invertColores(Image &picture){
    for (int i = 0; i < picture.width; i++){
        for (int j = 0; j < picture.height; j++){
             for(int k = 0 ; k < 3 ; k++){
                picture(i,j,k) = 255 - picture(i,j,k);
            }
        }
    }
}

void mergeImages(Image &image1){
Image image2;
image2.loadNewImage(loadImage());
image2 = resizeImage(image2 , image1.width , image1.height);
//merging algorithm
for (int i = 0; i < image1.width; i++) {
    for (int j = 0; j < image1.height; j++) {
        for (int k = 0; k < 3; k++) {
            // Calculate the average of pixel values
            int avg = (image1(i, j, k) + image2(i, j, k)) / 2;
            // Update the pixel value in image1 with the average
            image1(i, j, k) = avg;
        }
    }
}

}
Image hFlip(Image img){
    Image res(img.width , img.height);
for (int i = 0; i < img.width; i++)
{
    for (int j = 0; j < img.height; j++)
    {
        for (int k = 0; k < 3; k++)
        { 
            res(i,j,k) = img(img.width - i -1 ,  j ,k);
        }     
    }
}
return res;
}

Image vFlip(Image img){
    Image res(img.width , img.height);
for (int i = 0; i < img.width; i++)
{
    for (int j = 0; j < img.height; j++)
    {
        for (int k = 0; k < 3; k++)
        { 
            res(i,j,k) = img(i , img.height - j -1 ,k);
        }
        
    }
    
}
return res;
}

//rotation 
Image rotate270(Image img){
    Image res(img.height , img.width);
    for (int i = 0 ; i < img.width ; i++){
        for (int j = 0; j < img.height; j++){
            for(int k = 0 ; k < 3 ; k++){

                res (j , img.width - 1- i , k) = img(i,j,k);
            }
        }
    }
    return res;
}

Image rotate180(Image img){
    Image res(img.width , img.height);
    for (int i = 0 ; i < img.width ; i++){
        for (int j = 0; j < img.height; j++){
            for(int k = 0 ; k < 3 ; k++){

                res ( img.width - 1 - i, img.height - 1 - j , k) = img(i,j,k);
            }
        }
    }
    return res;
}

Image rotate90(Image img){
    Image res(img.height , img.width);
    for (int i = 0 ; i < img.width ; i++){
        for (int j = 0; j < img.height; j++){
            for(int k = 0 ; k < 3 ; k++){

                res (img.height - 1 -j , i , k) = img(i,j,k);
            }
        }
    }
    return res;
}

void lightenImage(Image &img){
        for (int i = 0 ; i < img.width ; i++){
        for (int j = 0; j < img.height; j++){
            for(int k = 0 ; k < 3 ; k++){
                int newValue = img(i,j,k) + 128;
                img(i,j,k) = min(newValue , 255);
                }
            }
        }
    }
void darkenImage(Image &img){
        for (int i = 0 ; i < img.width ; i++){
        for (int j = 0; j < img.height; j++){
            for(int k = 0 ; k < 3 ; k++){
                int newValue = img(i,j,k) - 128;
                img(i,j,k) = max(newValue , 0);
                }
            }
        }
    }

Image crop(Image img , int x , int y , int w , int h){
        int wLimit = min(x+w , img.width) , hLimit = min(y+h , img.height);
        Image res(wLimit - x ,hLimit - y);
        for (int i = x ; i< wLimit ; i++){
            for (int j = y; j < hLimit ; j++){
                for (int k = 0 ; k < 3 ; k++){
                    res(i - x,j - y,k) = img(i,j,k);
                }
            }
        }
        return res;
    }

Image addFrameToImage(const Image& image, int borderWidth, short int  frameColor[3]) {
    // Calculate the new dimensions of the image with the frame added
    int newWidth = image.width + 2 * borderWidth;
    int newHeight = image.height + 2 * borderWidth;
    
    // Create a new image with the larger dimensions
    Image framedImage(newWidth, newHeight);
    
    // Copy the original image to the center of the new image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                framedImage(x + borderWidth, y + borderWidth, c) = image(x, y, c);
            }
        }
    }
    
    // Draw horizontal frame lines
    for (int y = 0; y < borderWidth; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                framedImage(x, y, c) = frameColor[c]; // Top border
                framedImage(x, newHeight - y - 1, c) = frameColor[c]; // Bottom border
            }
        }
    }
    
    // Draw vertical frame lines
    for (int x = 0; x < borderWidth; ++x) {
        for (int y = 0; y < newHeight; ++y) {
            for (int c = 0; c < image.channels; ++c) {
                framedImage(x, y, c) = frameColor[c]; // Left border
                framedImage(newWidth - x - 1, y, c) = frameColor[c]; // Right border
            }
        }
    }
    
    return framedImage;
}

void findEdges(Image& img) {
    // Convert the image to black and white
    BlackAndWhite(img);

    // Initialize an empty image to store the edge result
    Image edgeImage(img.width, img.height);

    // Iterate over each pixel in the image
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            // Check if the current pixel is on the boundary
            if (i == 0 || i == img.width - 1 || j == 0 || j == img.height - 1) {
                edgeImage(i, j, 0) = 0; // Set boundary pixels to black
            } else {
                // Check for transitions from black to white or vice versa
                if (img(i, j, 0) != img(i - 1, j, 0) || img(i, j, 0) != img(i, j - 1, 0)) {
                    for (int k = 0 ; k < 3 ; k ++){
                    edgeImage(i, j, k) = 0; // Set edge pixels to white
                    }
                } else {
                    for (int k = 0 ; k < 3 ; k ++){
                    edgeImage(i, j, k) = 255; // Set non-edge pixels to black
                    }
                }
            }
        }
    }

    // Copy the edge result back to the original image
    img = edgeImage;
}



Image resizeImage(Image img , double width , double height){
    Image res(width , height);
    double wRatio , hRatio;
   wRatio = img.width / width;
   hRatio = img.height / height;
    for (int i = 0 ; i < width ; i++){
        for (int j = 0 ; j < height ; j++){
              for (int k = 0 ; k < 3 ; k++){
                 res(i,j,k) = img(floor(i*wRatio), floor(j*hRatio), k);
            }
        }
    }
return res;
}

Image blur( Image& img) {
    Image res(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int avg = 0, counter = 0;
                for (int x = i - 20; x <= i + 20; x++) {
                    for (int y = j - 20; y <= j + 20; y++) {
                        if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
                            avg += img(x, y, k);
                            counter++;
                        }
                    }
                }
                    avg /= counter;
   
                res(i, j, k) = avg;
            }
        }
    }

    return res;
}

void saveImage(Image picture){
 cout<<"Enter new image name with extension jpg,bmp,png,tga: \n";
    string newimage;
    cin>>newimage;
    picture.saveImage(newimage);
}

string loadImage(){
    string imageName;
    cout << "Please enter your image name with extension jpg,bmp,png,tga: \n";
    cin >> imageName;
    if (fileExists(imageName)){
    return imageName;
    }
    else {
        cout << "There is no Image with the provided name \n";
        return loadImage();
    }

}

bool fileExists(string filename) {
    
    ifstream file(filename);
    return file.good();

}

