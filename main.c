#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

//Function prototypes
char* getZipnameFromPath(char* dirPath){ //implementation for getting the directory name from path
    DIR *folder;
        struct dirent *entry;
        int files = 0;

        char* dirName;
        folder = opendir(dirPath);
        if(folder == NULL)
        {
            perror("Unable to read directory");


        }
        entry = readdir(folder);
        dirName = entry->d_name;
        printf("input: %s\n",dirName);

        return "/test.zip";
}

// Function to print the usage of the program
void printUsage(){
    printf("myzip [option] [input directory] [output directory]");
    //printf("to exract [zip filename] [input directory] [output directory]\n");
    //printf("For [help]\n");
}

void zip_walk(struct zip_t *zip, const char *path) { //make the zip file from dir
    int MAX_PATH = 500;
    DIR *dir;
    struct dirent *entry;
    char fullpath[MAX_PATH];
    struct stat s;

    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    assert(dir);

    while ((entry = readdir(dir))) {
      // skip "." and ".."
      if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
        continue;

      snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
      stat(fullpath, &s);
      if (S_ISDIR(s.st_mode))
        zip_walk(zip, fullpath);
      else {
        zip_entry_open(zip, fullpath);
        zip_entry_fwrite(zip, fullpath);
        zip_entry_close(zip);
      }
    }

    closedir(dir);
}

//implementation for compressing a directory
void compressDirectory(char* inputDir, char* outputDir){
    printf("option: compress\n");
    printf("input: %s\n", inputDir);
    printf("output: %s\n", outputDir);
    char* zipfile;

    //Get directory name from input directory path
    char* zipName = getZipnameFromPath(inputDir);

    zipfile = strcat(outputDir, zipName);

    struct zip_t *zip = zip_open(zipfile, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w'); //open zip file to compress
    {
        zip_walk(zip,inputDir);
}

    zip_close(zip);

}

int on_extract_entry(const char *filename, void *arg) {
        static int i = 0;
        int n = *(int *)arg;
        printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

        return 0;
    }

//implementation for extracting a zip file
void exractZipfile(char* zipfile, char* outputDir){
    printf("option: exract\n");
    printf("input: %s\n", zipfile);
    printf("output: %s\n", outputDir);



    int arg = 2;
    zip_extract(zipfile, outputDir, on_extract_entry, &arg);
}

void showHelp(){
    printf("Help content");
}

int isValidfile(const char *path) {
    struct stat st;

    if (stat(path, &st) < 0)
        return -1;

    return S_ISREG(st.st_mode);
}

int isValidDir(char* dirPath){
    //Try open Directory
    //If can be opened , It is a valid directory
    //If valid return 1, If not valid return 0
    DIR *folder;
        struct dirent *entry;
        int files = 0;

        char* dirName;
        folder = opendir(dirPath);
        if(folder == NULL)
        {
            perror("Unable to read directory");
            return 0;

        }
    return 1;

}

int main(int argc, char* argv[])
{
    //printf("You have entered %d arguments:\n", argc);
    if(argc >= 2){

        if(strcmp("-c", argv[1]) == 0){

            //User enter compress [-c] option
            //check user entered input directory and output directory parameters

            int isValid = 0;

            //Check User entered input directory is valid
            isValid = isValidDir(argv[2]);

            //Check output directory is valid
            if(isValid == 1){ //Input directory is valid

                    isValid = isValidDir(argv[3]);

            }else{

                printf("Invalid input Directory");
            }

            //If inputs valid, call compress method

            if( isValid == 1){

                //Output directory also valid
                compressDirectory(argv[2], argv[3]);
            }else{
                printf("Output directory is invalid");
            }


        }
        else if(strcmp("-e", argv[1]) == 0){
            //User entered extract option[-e]
            //check user entered input zip file and output directory
            int isValid = 0;

            //Check zip file is exists
            isValid = isValidfile(argv[2]);

            //Check output directory is valid
             if(isValid == 1){ //Input zip file is valid

                    isValid = isValidDir(argv[3]);

            }else{

                printf("Invalid input Directory");
            }
            //If inputs are valid, call extract method
            if(isValid == 1){

            exractZipfile(argv[2], argv[3]);

            }

        }
        else if(strcmp("-h", argv[1]) == 0){

            //User entered help option[-h]
            //call help method
            showHelp();
        }else{

            //User entered invalid option
            //Show Usage
            printUsage();


        }
    }

    return 0;

}
