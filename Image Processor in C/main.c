#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LENGTH 1025

/*This is an image processor that only accepts PGM files with the P2 format.*/

void arrayToImg(short imgArray[MAX_LENGTH][MAX_LENGTH], char* outName, char secLine[70], int* width, int* height, int* maxGray){
    /*This function writes the array into a PGM file format*/

    /*Creating the file to write to*/
    FILE* outImg = fopen(outName, "w");

    /*Lets start by filling the header */
    fprintf (outImg, "P2\n");
    fprintf (outImg, "%s\n", secLine);
    fprintf (outImg, "%d %d\n", *width, *height);
    fprintf (outImg, "%d\n", *maxGray);

    /*Writing the final img array to the file*/
    for(int row = 0; row < *height; row++){
        for(int col = 0; col < *width; col++){
            fprintf(outImg, "%d ", imgArray[row][col]);
        }
        fprintf(outImg, "\n");
    }

    fclose(outImg);
};

void imgToArray(char* fileName, int* width, int* height, int* maxGray, short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function read the image into a 2D array and collects the header information*/
    FILE* inFile = fopen(fileName, "r");

    /*Lets make a trash to store unuseful info as we itterate through the lines*/
    char trash[80];

    /*Read 1st line that contains the file signature 'P2'*/
    fgets(trash, 70, inFile);
    /*Read second line that contains a random string no longer than 70 characters*/
    fgets(trash, 70, inFile);
    /*Read the first integer after which is the image width*/
    fscanf(inFile, "%d", width);
    /*Read the integer after which is the image height*/
    fscanf(inFile, "%d", height);
    /*Read the last integer before the matrix which is the image maximum gray number*/
    fscanf(inFile, "%d", maxGray);

    /*Read the image matrix into the array*/
    int row;
    int col;
    for (row=0; row<*height; row++){
        for (col=0; col<*width; col++){
            fscanf(inFile, "%d", &imgArray[row][col]);

        }
    }
    fclose(inFile);
}

void invert(short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function inverts the colors in the image*/
    for(int i = 0; i<MAX_LENGTH; i++){
        for(int j=0; j<MAX_LENGTH; j++){
            imgArray[i][j] = 255 - imgArray[i][j];
        }
    }
}

void blur (short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function uses the box blur kernel to convolve the image*/
    short kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    for(int i = 1; i<1024; i++){
        for(int j= 1; j<1024; j++){
            imgArray[i][j] = (imgArray[i+1][j+1]*kernel[0][0] + imgArray[i][j+1]*kernel[0][1]+
                                    imgArray[i-1][j+1]*kernel[0][2]+imgArray[i+1][j]*kernel[1][0]+
                                    imgArray[i][j]*kernel[1][1]+imgArray[i-1][j]*kernel[1][2]+imgArray[i+1][j-1]*kernel[2][0]+
                                    imgArray[i][j+1]*kernel[2][1]+imgArray[i-1][j-1]*kernel[2][2])/9;
        }
    }
}

void gblur (short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function uses the Gaussian blur kernel to convolve the image*/
    short kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    for(int i = 1; i<1024; i++){
        for(int j= 1; j<1024; j++){
            imgArray[i][j] = (imgArray[i+1][j+1]*kernel[0][0] + imgArray[i][j+1]*kernel[0][1]+
                                    imgArray[i-1][j+1]*kernel[0][2]+imgArray[i+1][j]*kernel[1][0]+
                                    imgArray[i][j]*kernel[1][1]+imgArray[i-1][j]*kernel[1][2]+imgArray[i+1][j-1]*kernel[2][0]+
                                    imgArray[i][j+1]*kernel[2][1]+imgArray[i-1][j-1]*kernel[2][2])/16;
        }
    }
}

void outline (short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function uses the outline/edge-detection kernel to convolve the image*/
    short kernel[3][3] = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}
    };
    for(int i = 1; i<1024; i++){
        for(int j= 1; j<1024; j++){
            imgArray[i][j] = (imgArray[i+1][j+1]*kernel[0][0] + imgArray[i][j+1]*kernel[0][1]+
                                    imgArray[i-1][j+1]*kernel[0][2]+imgArray[i+1][j]*kernel[1][0]+
                                    imgArray[i][j]*kernel[1][1]+imgArray[i-1][j]*kernel[1][2]+imgArray[i+1][j-1]*kernel[2][0]+
                                    imgArray[i][j+1]*kernel[2][1]+imgArray[i-1][j-1]*kernel[2][2]);
            if (imgArray[i][j] > 255) {
                imgArray[i][j] = 255;
            }
            if (imgArray[i][j] < 1) {
                imgArray[i][j] = 1;
            }
        }
    }
}

void sharpen (short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function uses the sharpen kernel to convolve the image*/
    short kernel[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
    for(int i = 1; i<1024; i++){
        for(int j= 1; j<1024; j++){
            imgArray[i][j] = (imgArray[i+1][j+1]*kernel[0][0] + imgArray[i][j+1]*kernel[0][1]+
                                    imgArray[i-1][j+1]*kernel[0][2]+imgArray[i+1][j]*kernel[1][0]+
                                    imgArray[i][j]*kernel[1][1]+imgArray[i-1][j]*kernel[1][2]+imgArray[i+1][j-1]*kernel[2][0]+
                                    imgArray[i][j+1]*kernel[2][1]+imgArray[i-1][j-1]*kernel[2][2]);
            if (imgArray[i][j] > 255) {
                imgArray[i][j] = 255;
            }
            if (imgArray[i][j] < 0) {
                imgArray[i][j] = 0;
            }
        }

    }
}

void brightness(short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function inquires how the brightness should be changed and to what level
    and subsequently applies the processing*/
    char effect;
    double intensity;

    printf("Would you like to brighten or darken the image?(b/d)\n");
    scanf(" %c", &effect);

    switch(effect){
    case 'b':
        printf("How much would you like to brighten image? (a value between 0 to 10)\n");
        scanf("%lf", &intensity);
        intensity = 1 + (0.1 * intensity);
        for(int i = 0; i<MAX_LENGTH; i++){
            for(int j= 0; j<MAX_LENGTH; j++){
                imgArray[i][j] = intensity * imgArray[i][j];
                if (imgArray[i][j] > 255) {
                    imgArray[i][j] = 255;
                }
            }
        }
        break;
    case 'd':
        printf("How much would you like to darken image? (a value between 0 to 10)\n");
        scanf("%lf", &intensity);
        intensity = 1 - (0.1 * intensity);
        for(int i = 0; i<MAX_LENGTH; i++){
            for(int j= 0; j<MAX_LENGTH; j++){
                imgArray[i][j] = intensity * imgArray[i][j];
            }
        }
        break;
    default:
        printf("Invalid command.\n");
    }

}

void contrast(short imgArray[MAX_LENGTH][MAX_LENGTH]){
    /*This function attempts to create contrast changes in the image. The code is
    completely improvised, so this function does currently need improvement*/
    char effect;
    double intensity;

    printf("Would you like to increase or decrease the contrast?(i/d)\n");
    scanf(" %c", &effect);

    switch(effect){
    case 'i':
        printf("How much would you like to increase the contrast? (a value between 0 to 10)\n");
        scanf("%lf", &intensity);
        intensity = 1 + (0.1 * intensity);
        for(int i = 0; i<MAX_LENGTH; i++){
            for(int j= 0; j<MAX_LENGTH; j++){
                if (imgArray[i][j] > 127) {
                    imgArray[i][j] = (sqrt(intensity) + 0.2) * imgArray[i][j];
                } else {
                    imgArray[i][j] = (2 - (sqrt(intensity) + 0.2)) * imgArray[i][j];
                }
                if (imgArray[i][j] > 255) {
                    imgArray[i][j] = 255;
                }
            }
        }
        break;
    case 'd':
        printf("How much would you like to decrease the contrast? (a value between 0 to 10)\n");
        scanf("%lf", &intensity);
        intensity = 1 + (0.1 * intensity);
        for(int i = 0; i<MAX_LENGTH; i++){
            for(int j= 0; j<MAX_LENGTH; j++){
                if (imgArray[i][j] > 127) {
                    imgArray[i][j] = imgArray[i][j] / (sqrt(intensity) + 0.2);
                } else {
                    imgArray[i][j] = imgArray[i][j] / (2 - (sqrt(intensity) + 0.2));
                }
            }
        }
        break;
    default:
        printf("Invalid command.\n");
    }
}

void transformation(short imgArray[MAX_LENGTH][MAX_LENGTH], short imgArrayDup[MAX_LENGTH][MAX_LENGTH], int* height, int* width, char* transformed){
    /*This function asks the user for the type of transformation they want to apply
    and it applie the commanded transformation*/
    char effect[7];
    int rotate;
    char reflect;

    printf("Would you like to Rotate or Reflect the image?\n");
    scanf("%s", effect);
    lowercase(effect);

    /*The user can choose to what degree they would like to rotate the image*/
    if(strcmp(effect, "rotate") == 0) {
        printf("How many degrees would you like to rotate the image (counter-clockwise)?\n");
        printf("90, 180, or 270 degrees?\n");
        scanf(" %d", &rotate);
        switch(rotate){
        case 90:
            *transformed = 'y';
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArrayDup[i][j] = imgArray[j][i];
                }
            }
            break;
        case 180:
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArrayDup[i][j] = imgArray[*height-i][*width-j];
                }
            }
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArray[i][j] = imgArrayDup[i][j];
                }
            }
            break;
        case 270:
            *transformed = 'y';
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArrayDup[i][j] = imgArray[*height - j][i];
                }
            }
            break;
        default:
            printf("Invalid command.\n");
        }
    }
    /*The user can choose what type of reflection they want to apply.*/
    if(strcmp(effect, "reflect") == 0) {
        printf("Would you like to reflect the image vertically or horizontally?(v/h)\n");
        scanf(" %c", &reflect);
        switch(reflect){
        case 'v':
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArrayDup[i][j] = imgArray[*height - i][j];
                }
            }
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArray[i][j] = imgArrayDup[i][j];
                }
            }
            break;
        case 'h':
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArrayDup[i][j] = imgArray[i][*width - j];
                }
            }
            for(int i = 0; i<MAX_LENGTH; i++){
                for(int j= 0; j<MAX_LENGTH; j++){
                    imgArray[i][j] = imgArrayDup[i][j];
                }
            }
            break;
        default:
            printf("Invalid command.\n");
        }
    }

}

void imgProcessor(short imgArray[MAX_LENGTH][MAX_LENGTH], short imgArrayDup[MAX_LENGTH][MAX_LENGTH], int* height, int* width, char* transformed){
    /*This function asks the user for the type of image processing they want to do and
    sends them to the appropriate function*/
    char process[15];

    printf("Please enter the edit type that you would like to apply to your image:\n");
    printf("Convolution (contains boxblur, outline, sharpen, gaussianblur)\n");
    printf("Inversion\n");
    printf("Brightness (contains darken and lighten)\n");
    printf("Contrast\n");
    printf("Transformation (contains rotation and reflection)\n");
    scanf("%s", process);
    lowercase(process);

    if(strcmp(process, "inversion") == 0) {
        invert(imgArray);
    }
    if(strcmp(process, "brightness") == 0) {
        brightness(imgArray);
    }
    if(strcmp(process, "convolution") == 0) {
        convolution(imgArray, height, width);
    }
    if(strcmp(process, "contrast") == 0) {
        contrast(imgArray);
    }
    if(strcmp(process, "transformation") == 0) {
        transformation(imgArray, imgArrayDup, height, width, transformed);
    }
    printf("\n%s done.\n", process);
}

void lowercase(char word[15]){
    /*This function transforms a word of maximum 15 characters into all lowercase letters*/
    for(int i = 0; i < strlen(word); i++){
        word[i] = tolower(word[i]);
    }
}

void convolution(short imgArray[MAX_LENGTH][MAX_LENGTH], int* height, int* width){
    /*This is the convolution function that points to the type of convolution function determined by the user*/
    char process[15];

    printf("What type of convolution would you like to implement?\n");
    printf("BoxBlur\n");
    printf("GaussianBlur\n");
    printf("Outline\n");
    printf("Sharpen\n");
    scanf("%s", process);
    lowercase(process);

    if(strcmp(process, "boxblur") == 0) {
        blur(imgArray);
    }
    if(strcmp(process, "gaussianblur") == 0) {
        gblur(imgArray);
    }
    if(strcmp(process, "outline") == 0) {
        outline(imgArray);
    }
    if(strcmp(process, "sharpen") == 0) {
        sharpen(imgArray);
    }
}

void getFileName(char inFileName[30], char outFileName[35]){
    /*This function asks the user for the image file name*/
    char temp[26];

    printf("Please type the file name of the image you wish to edit (without the .pgm extension):\n");
    scanf("%s", temp);
    strcpy(inFileName, temp);
    strcpy(outFileName, temp);
    strcat(inFileName, ".pgm");
    strcat(outFileName, "_edited.pgm");

}


int main() {

    printf(" ____   ___  _  _    ____  ____   __    ___  ____  ____  ____   __  ____   \n");
    printf("(  _ \\ / __)( \\/ )  (  _ \\(  _ \\ /  \\  / __)(  __)/ ___)/ ___) /  \\(  _ \\  \n");
    printf(" ) __/( (_ \\/ \\/ \\   ) __/ )   /(  O )( (__  ) _) \\___ \\\\___ \\(  O ))   /  \n");
    printf("(__)   \\___/\\_)(_/  (__)  (__\\_) \\__/  \\___)(____)(____/(____/ \\__/(__\\_)  \n");

    printf("\n\nWelcome to the PGM image Processor!\n");
    /*This do while loop ensures that the user can edit another image after the editing process of their
    previous image is done.*/
    bool restart = false;
    do{
        /*Define all needed variables*/
        int width;
        int height;
        int maxGray;
        short imgArray[MAX_LENGTH][MAX_LENGTH];
        short imgArrayDup[MAX_LENGTH][MAX_LENGTH];
        char transformed = 'n';
        char inFileName[30] = "";
        char outFileName[35] = "";

        /*Get the input file name*/
        getFileName(inFileName, outFileName);

        /*Convert the image into a 2D array of shorts (2 byte) and also redeem header info*/
        imgToArray(inFileName, &width, &height, &maxGray, imgArray);

        /*Process the image*/
        imgProcessor(imgArray, imgArrayDup, &height, &width, &transformed);

        /*Convert the processed array back to the image format and write the image*/
        switch(transformed){
        case 'y':
            arrayToImg(imgArrayDup, outFileName, "# transformed image", &height, &width, &maxGray);
            break;
        case 'n':
            arrayToImg(imgArray, outFileName, "# edited image", &width, &height, &maxGray);
        }

        /*Check if the user would like to edit another image, break the while loop if not.*/
        char yn;
        printf("Would you like to edit another image?(y/n)  ");
        scanf(" %c", &yn);
        switch(yn){
        case 'y':
            restart = true;
            break;
        default:
            restart = false;
            printf("Thanks for checking out the app!\n");
        }


    /*Lets put a do while to keep the main restarting.*/
    }while(restart);

    return 0;
}

