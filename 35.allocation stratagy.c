#include <stdio.h>
#include <string.h>
#define MAX_FILES 10 // maximum number of files that can be stored
#define BLOCK_SIZE 512 // size of each file block

struct File {
    char name[100]; // name of the file
    int size; // size of the file in bytes
    int blocks; // number of blocks required to store the file
    int index_block[MAX_FILES]; // array to store file pointers
};

// global variable to keep track of the file system
struct File files[MAX_FILES];
int num_files = 0; // current number of files stored

// function to add a new file to the file system
void add_file(char *name, int size) {
    if (num_files == MAX_FILES) {
        printf("Error: maximum number of files reached\n");
        return;
    }

    // calculate number of blocks required to store the file
    int blocks = size / BLOCK_SIZE;
    if (size % BLOCK_SIZE != 0) {
        blocks++;
    }

    // check if there are enough available blocks
    int available_blocks = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].index_block[i] == 0) {
            available_blocks++;
        }
    }
    if (available_blocks < blocks) {
        printf("Error: not enough available blocks\n");
        return;
    }

    // add file to file system
    int file_index = num_files;
    strcpy(files[file_index].name, name);
    files[file_index].size = size;
    files[file_index].blocks = blocks;
    int block_index = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].index_block[i] == 0) {
            files[file_index].index_block[block_index] = i;
            block_index++;
            if (block_index == blocks) {
                break;
            }
        }
    }
    num_files++;
    printf("File %s added to file system\n", name);
}

// function to read a file from the file system
void read_file(char *name) {
    int file_index = -1;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(files[i].name, name) == 0) {
            file_index = i;
            break;
        }
    }
    if (file_index == -1) {
        printf("Error: file not found\n");
        return;
    }

    // read data blocks of file
    printf("File %s:\n", name);
    for (int i = 0; i < files[file_index].blocks; i++) {
        int block_index = files[file_index].index_block[i];
        // code to read data from the block
        // ...
    }
}

// function to delete a
