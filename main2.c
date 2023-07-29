#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void printUsage(){

    printf("myzip [option] [input directory] [output directory] [zip filename]\n");
    printf("to exract [zip filename] [output directory] [program name]\n");
    printf("For [help]\n");

}

void compressDirectory(char* inputDir, char* outputDir, char* zipFilename){

    printf("option: compress\n");
    printf("input: %s\n", inputDir);
    printf("output: %s\n", outputDir);
    printf("zipFilename: %s\n", zipFilename);

}

void exractZipfile(char* zipfile, char* outputDir, char* zipFilename){

    printf("option: exract\n");
    printf("input: %s\n", zipfile);
    printf("output: %s\n", outputDir);
    printf("programName: %s\n", zipFilename);

}

void showHelp(char* zipFileName){

    printf("Help content for: %s:\n", programName);
    printf("Help content goes here\n");


}
int isDirectoryExists(){
    DIR* dir = opendir("C:/Users/user/Desktop/New folder");
    if (dir) {
        /* Directory exists. */
        printf("dir exists");
        closedir(dir);
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
        printf("Dir does not exists");
    } else {
        /* opendir() failed for some other reason. */
        printf("faild to open, some other reasons");
    }

    return 0;
}

int main(int argc, char* argv[])
{
    char** args = argv;
    //printf("You have entered %d arguments:\n", argc);

    if(argc != 5){

        printUsage();

}

    else{

        char* option = args[1];
        char* inputDir = args[2];
        char* outputDir = args[3];
        char* zipFilename = args[4];

        int temp = strcmp("-c", argv[1]);
        printf("temp = %d\n", temp);
        if(temp == 0){

            compressDirectory(argv[2], argv[3],argv[4]);
        }

        else{

            int temp2 = strcmp("-e", argv[1]);
            if(temp2 == 0){
                exractZipfile(argv[2], argv[3], argv[4]);

            }

            else{

                int temp3 = strcmp("-h", argv[1]);
                if(temp3 == 0){
                    showHelp(argv[1]);

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
