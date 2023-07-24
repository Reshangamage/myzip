#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUsage(){
    printf("myzip [option] [input directory] [output directory]");
}

void compressDirectory(char* inputDir, char* outputDir){
    printf("option: compress\n");
    printf("input: %s\n", inputDir);
    printf("output: %s\n", outputDir);
}

void exractZipfile(char* zipfile, char* outputDir){
    printf("option: exract\n");
    printf("input: %s\n", zipfile);
    printf("output: %s\n", outputDir);
}

void showHelp(){
    printf("Help content");
}


int main(int argc, char* argv[])
{
    //printf("You have entered %d arguments:\n", argc);

    if(argc != 4){

        printUsage();

    }
    else{

        int temp = strcmp("-c", argv[1]);
        printf("temp = %d\n", temp);
        if(temp == 0){

            compressDirectory(argv[2], argv[3]);
        }

        else{
            int temp2 = strcmp("-e", argv[1]);
            if(temp2 == 0){
                exractZipfile(argv[2], argv[3]);

            }
            else{
                int temp3 = strcmp("-h", argv[1]);
                if(temp3 == 0){
                    showHelp();
                }

                else{
                    printf("Invalid option. Valid options are -c, -e and -h");
                }
            }
        }
    }

    //for (int i = 0; i < argc; i++) {
     //   printf("%s\n", argv[i]);
    //}
return 0;
}
