#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_PIX 70

/*The image arrays when reading and writing must be of correct exact size, you can't just put in a maximum.
Ergo, we might need to create a function that first reads and collects the header info before proceeding to read the file in? not sure yet..*/

void arrayToImg(int imageArr[][10], char* outName, char* secLine, int width[], int height[], int maxGray[]){

    /*Creating the file to write to*/
    FILE* outImg = fopen(outName, "wb");

    /*Lets start by filling the header */
    fprintf (outImg, "P2\n");
    fprintf (outImg, "%s\n", secLine);
    fprintf (outImg, "%d %d\n", width, height);
    fprintf (outImg, "%d\n", maxGray);

    /*Writing the final img array to the file*/
    int row;
    int col;
    for(row=0; row<height; row++){
        for(col=0; col<width; col++){
            fprintf(outImg, "%d ", imageArr[row][col]);
        }
        fprintf(outImg, "\n");
    }

    fclose(outImg);

};

void imgToArray(char* fileName, int* width, int* height, int* maxGray){
    FILE* inFile = fopen(fileName, "r");

    /*Lets make a trash to store unuseful info as we itterate through the lines*/
    char trash[100];

    fgets(trash, 100, inFile);
    fgets(trash, 100, inFile);
    fscanf(inFile, "%d %d", width, height);
    fscanf(inFile, "%d", maxGray);

    /*Creating a global variable that can be edited in other functions*/
    int myArray[50][50];
    int row;
    int col;
    for (row=0; row<*height; row++){
        for (col=0; col<*width; col++){
            fprintf(inFile, "%d", myArray[row][col]);
        }
    }


    printf("%d %d\n", myArray[0][0], myArray[0][1]);
    fclose(inFile);

};

void headerInfo(char* fileName, int* width, int* height, int* maxGray){

};

int main() {

    /*use an array of random arrays to create a test image*/
    int image[10][10] = {
    {18, 62, 81, 91, 102, 103, 111, 113, 137, 254},
    {65, 78, 116, 153, 157, 173, 179, 192, 241, 253},
    {20, 28, 72, 73, 90, 122, 132, 187, 202, 213},
    {34, 39, 54, 80, 176, 217, 224, 232, 238, 242},
    {56, 73, 104, 109, 153, 162, 180, 246, 248, 254},
    {19, 20, 38, 53, 89, 110, 131, 158, 179, 239},
    {71, 132, 153, 194, 221, 223, 225, 234, 238, 246},
    {21, 59, 81, 137, 142, 164, 179, 212, 213, 245},
    {41, 42, 63, 74, 77, 82, 120, 130, 184, 249},
    {2, 46, 68, 96, 112, 119, 187, 223, 235, 246}
    };
    arrayToImg(image, "output.pgm", "# test", 10, 10, 255);
//    char line[255];
//    FILE* img = fopen("output.pgm", "r");
//    fgets(line, 255, img);
//    printf("%s", line);
    int width = 50;
    int height = 50;
    int maxGray = 255;
    imgToArray("dog.pgm", width, height, maxGray);


    return 0;
}

