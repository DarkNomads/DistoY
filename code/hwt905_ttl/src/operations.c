#include "operations.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Function: Unlocks the device registers and starts the unlock timer.
    Inputs: None.
    Outputs: The timer for the how long the device has been unlocked.
*/
time_t unlock() {
    printf("Unlocking sensor...\n");
    return time( NULL );
}

/*
    Function: Checks if the device is still unlocked.
    Inputs: The unlock timer.
    Outputs: Whether the device is still unlocked or not.
*/
int isUnlocked( time_t timer ) {
    return ( time( NULL ) - timer ) < LOCKOUT_TIME;
}

/*
    Function: Saves the sensor register data.
    Inputs: None.
    Outputs: None.
*/
void save() {
    printf("Saving register data...\n");
}

/*
    Function: Outputs the formatted value of the specific data.
    Inputs: The low and low high for the data, along with a pointer for the length of the output.
    Outputs: The formatted string to be written to the output file.
*/
char* format_data( char* low, char* high, int* outputLength ) {
    *outputLength = OUTPUT_LENGTH;
    char* output = malloc( *outputLength * sizeof( char ) );
    for( int i = 0; i < HEADER_LENGTH; i++ ) { output[i] = OUTPUT_HEADER[i]; }
    for( int i = HEADER_LENGTH; i < OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > OUTPUT_LENGTH-3 ) { output[i] = '0'; }
        else if( i > HEADER_LENGTH+3 ) { output[i] = high[i-HEADER_LENGTH-4]; }
        else { output[i] = low[i-HEADER_LENGTH-1]; }
    }
    output[*outputLength] = '\0';
    return output;
}

/*
    Function: Retrieves the pitch value of the sensor (Implemented as bounded random).
    Inputs: None.
    Outputs: The pitch value of the sensor, represented as high and low component strings.
*/
char** get_pitch() {
    char** data = malloc( 2 * sizeof( char* ) );
    for( int i = 0; i < 2; i++ ) {
        data[i] = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
        data[i][SEGMENT_LENGTH] = '\0';
    }

    for( int i = 0; i < 1; i++ ) {
        char hex[9];
        int randomAngle = rand() % 180;

        if( rand() % 2 == 0 ) { randomAngle *= -1; }
        sprintf( hex, "%08X", randomAngle );

        data[2*i][0] = hex[4];
        data[2*i][1] = hex[5];
        data[(2*i)+1][0] = hex[6];
        data[(2*i)+1][1] = hex[7];
    }

    return data;
}

/*
    Function: Retrieves the X, Y, and Z values for the magnetic field (Implemented as bounded random).
    Inputs: None.
    Outputs: The X, Y, and Z values for the magnetic field, represented as high and low component strings.
*/
char** get_magnetic() {
    char** data = malloc( 6 * sizeof( char* ) );
    for( int i = 0; i < 6; i++ ) {
        data[i] = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
        data[i][SEGMENT_LENGTH] = '\0';
    }

    for( int i = 0; i < 3; i++ ) {
        char hex[9];
        int randomValue = rand() % 32767;

        if( rand() % 2 == 0 ) { randomValue *= -1; }
        sprintf( hex, "%08X", randomValue );

        data[2*i][0] = hex[4];
        data[2*i][1] = hex[5];
        data[(2*i)+1][0] = hex[6];
        data[(2*i)+1][1] = hex[7];
    }

    return data;
}

/*
    Function: Retrieves the X, Y, and Z values for the acceleration (Implemented as bounded random).
    Inputs: None.
    Outputs: The X, Y, and Z values for the acceleration, represented as high and low component strings.
*/
char** get_acceleration() {
    char** data = malloc( 6 * sizeof( char* ) );
    for( int i = 0; i < 6; i++ ) {
        data[i] = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
        data[i][SEGMENT_LENGTH] = '\0';
    }

    for( int i = 0; i < 3; i++ ) {
        char hex[9];
        int randomValue = rand() % 32767;

        if( rand() % 2 == 0 ) { randomValue *= -1; }
        sprintf( hex, "%08X", randomValue );

        data[2*i][0] = hex[4];
        data[2*i][1] = hex[5];
        data[(2*i)+1][0] = hex[6];
        data[(2*i)+1][1] = hex[7];
    }

    return data;
}
