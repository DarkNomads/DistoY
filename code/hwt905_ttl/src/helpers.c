#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

/*
    Function: Clears any data from a file.
    Inputs: A file name.
    Outputs: None.
*/
void clearData( char* filename ) {
    FILE* file = fopen( filename, "w" );
    fputs( "\0", file );
    fclose( file );
}

/*
    Function: Writes data to a specified file, the file must already be empty.
    Inputs: A file name and the data string to be written.
    Outputs: Outputs 0 if failed, or 1 if successful.
*/
int writeData( char* filename, char* data ) {
    // Check if the file contains any data.
    FILE* file = fopen( filename, "r" );
    if( file ) {
        // Determine the length of the file's contents.
        unsigned int start = ftell( file );
        fseek( file, 0, SEEK_END );
        int length = ftell( file );
        fseek( file, start, SEEK_SET );
        fclose( file );

        // Return if there is already data in the file.
        if( length > 0 ) {
            return 0;
        }
    }

    // Write the data to the file.
    file = fopen( filename, "w" );
    fputs( data, file );
    fclose( file );
    return 1;
}

/*
    Function: Reads all data from a given file into a string and stores the size of the array.
    Inputs: A file name and a pointer to an integer for storing data length.
    Outputs: The data as a string.
*/
char* readData( char* filename, int* length ) {
    FILE* file = fopen( filename, "r" );
    char* fileData;

    // Check that the file exists.
    if( file == NULL ) {
        *length = 0;
        fileData = malloc( sizeof( char ) );
        fileData[*length] = '\0';
        return fileData;
    }

    // Determine the length of the file's contents.
    unsigned int start = ftell( file );
    fseek( file, 0, SEEK_END );
    *length = ftell( file );
    fseek( file, start, SEEK_SET );

    // Write the entire file's contents into the data string.
    fileData = malloc( ( *length + 1 ) * sizeof( char ) );
    for( int i = 0; i < *length; i++ ) {
        fileData[i] = fgetc( file );
    }
    fileData[*length] = '\0';
    fclose( file );

    // Return the data string.
    return fileData;
}