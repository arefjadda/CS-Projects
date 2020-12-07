#include <stdio.h>
#include <stdlib.h>


/*The image arrays when reading and writing must be of correct exact size, you can't just put in a maximum.
Ergo, we might need to create a function that first reads and collects the header info before proceeding to read the file in? not sure yet..*/


void arrayToImg(short imgArray[1025][1025], char* outName, char* secLine, int* width, int* height, int* maxGray){

    /*Creating the file to write to*/
    FILE* outImg = fopen(outName, "w");

    /*Lets start by filling the header */
    fprintf (outImg, "P2\n");
//    fprintf (outImg, "%s\n", secLine);
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


void imgToArray(char* fileName, int* width, int* height, int* maxGray, short imgArray[1025][1025]){
    FILE* inFile = fopen(fileName, "r");

    /*Lets make a trash to store unuseful info as we itterate through the lines*/
    char trash[80];

    fgets(trash, 70, inFile);
    printf("%s\n", trash);
    fgets(trash, 70, inFile);
    printf("%s\n", trash);
    fscanf(inFile, "%d", width);
    printf("%d\n", *width);
    fscanf(inFile, "%d", height);
    printf("%d\n", *height);
    fscanf(inFile, "%d", maxGray);
    printf("%d\n", *maxGray);
    int row;
    int col;
    for (row=0; row<*height; row++){
        for (col=0; col<*width; col++){
            fscanf(inFile, "%d", &imgArray[row][col]);

        }
    }
//    printf("%i %i\n", imgArray[0][0], imgArray[0][1]);

    fclose(inFile);
}

void invert(short imgArray[1025][1025]){
    for(int i = 0; i<1025; i++){
        for(int j=0; j<1025; j++){
            imgArray[i][j] = 255 - imgArray[i][j];
        }
    }
}

void blur (short imgArray[1025][1025]){
    short bBlur[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    for(int i = 1; i<1024; i++){
        for(int j= 1; j<1024; j++){
            imgArray[i][j] = (imgArray[i+1][j+1]*bBlur[0][0] + imgArray[i][j+1]*bBlur[0][1]+
                                    imgArray[i-1][j+1]*bBlur[0][2]+imgArray[i+1][j]*bBlur[1][0]+
                                    imgArray[i][j]*bBlur[1][1]+imgArray[i-1][j]*bBlur[1][2]+imgArray[i+1][j-1]*bBlur[2][0]+
                                    imgArray[i][j+1]*bBlur[2][1]+imgArray[i-1][j-1]*bBlur[2][2])/9;
        }
    }
}

int main() {

    int width;
    int height;
    int maxGray;
    short imgArray[1025][1025];
    short imgArrayDup[1025][1025];
    char* inFileName = "feep.pgm";
    char* outFileName = "feep_edited.pgm";


//    FILE* inFile = headerInfo("dog.pgm", width, height, maxGray);
    imgToArray(inFileName, &width, &height, &maxGray, imgArray);

    for (int i=0; i<1025; i++){
        for(int j=0; j<1025; j++){
            imgArrayDup[i][j] = imgArray[i][j];
        }
    }

    blur(imgArray);

    printf("%d %d %d\n", width, height, maxGray);
    printf("%d %d\n", imgArray[0][0], imgArrayDup[0][1]);


    arrayToImg(imgArray, outFileName, "# test", &width, &height, &maxGray);



    return 0;
}

