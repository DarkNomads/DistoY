#include "operations.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Function: Calculates the checksum of hex strings.
    Inputs: Pointer to an array of strings and how many strings are in the array.
    Outputs: The calculated checksum string.
*/
char* calculate_checksum( char** segments, int count ) {
    char* checksum = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
    checksum[2] = '\0';

    // Convert segments into integer equivalents.
    int values[3];
    for( int i = 0; i < count; i++ ) { values[i] = (int)strtol( segments[i], NULL, 16 ); }

    // Sum all the values.
    int sum = 0;
    for( int i = 0; i < count; i++ ) { sum = (sum + values[i]); }

    // Bitwise AND by constant.
    sum &= CHECKSUM_CONSTANT;

    // Convert the sum to hex.
    char hex[9];
    sprintf( hex, "%08X", sum );
    checksum[0] = hex[6];
    checksum[1] = hex[7];

    return checksum;
}

/*
    Function: Reads the current slave value from the sensor, and formats the output string.
    Inputs: The current slave value, and a pointer for the length of the output.
    Outputs: The formatted output string from reading the slave value.
*/
char* read_slave( int slaveValue, int* outputLength ) {
    *outputLength = SINGLE_OUTPUT_LENGTH;
    char* output = malloc( (*outputLength+1) * sizeof( char ) );

    // Convert the slave integer value to hex.
    char slave[9];
    sprintf( slave, "%08X", slaveValue );

    // Format the output string.
    for( int i = 0; i < SINGLE_OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > SINGLE_OUTPUT_LENGTH-3 ) { output[i] = END[i-SINGLE_OUTPUT_LENGTH+2]; }
        else if( i > SINGLE_OUTPUT_LENGTH-6 ) { output[i] = READ_SLAVE[i-SINGLE_OUTPUT_LENGTH+5]; }
        else if( i > SINGLE_OUTPUT_LENGTH-9 ) { output[i] = slave[i-SINGLE_OUTPUT_LENGTH+8+6]; }
        else if( i > SINGLE_OUTPUT_LENGTH-12 ) { output[i] = READ_SLAVE[i-SINGLE_OUTPUT_LENGTH+11]; }
        else if( i > SINGLE_OUTPUT_LENGTH-15 ) { output[i] = MASTER_ADDRESS[i-SINGLE_OUTPUT_LENGTH+14]; }
        else { output[i] = INITIATE[i-SINGLE_OUTPUT_LENGTH+17]; }
    }
    output[*outputLength] = '\0';

    return output;
}

/*
    Function: Attempts to set the new slave address, fails if the new address is invalid, and formats the output string.
    Inputs: The pointer to the slave value, the new slave data segment, the checksum from the request, and a pointer for the length of the output.
    Outputs: The formatted output string from setting the slave value.
*/
char* set_slave( int* slave, char* newSlaveSegment, char* checksum, int* outputLength ) {
    // Convert the slave value to hex.
    char slaveSegment[3] = { '0', '0', '\0' };
    char hex[9];
    sprintf( hex, "%08X", *slave );
    slaveSegment[0] = hex[6];
    slaveSegment[1] = hex[7];

    // Attempt to set the new slave address.
    int newSlave = (int)strtol( newSlaveSegment, NULL, 16 );
    char successSegment[3] = { '0', '0', '\0' };
    if( newSlave > 0 && newSlave < 127 ) {
        successSegment[1] = '1';
        *slave = newSlave;
        slaveSegment[0] = newSlaveSegment[0];
        slaveSegment[1] = newSlaveSegment[1];
    }

    // Calculate the new checksum value.
    char* values[4] = { MASTER_ADDRESS, SET_SLAVE, successSegment, slaveSegment };
    char* calculatedChecksum = calculate_checksum( values, 4 );

    // Format the output string.
    *outputLength = SINGLE_OUTPUT_LENGTH;
    char* output = malloc( (*outputLength+1) * sizeof( char ) );
    for( int i = 0; i < SINGLE_OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > SINGLE_OUTPUT_LENGTH-3 ) { output[i] = END[i-SINGLE_OUTPUT_LENGTH+2]; }
        else if( i > SINGLE_OUTPUT_LENGTH-6 ) { output[i] = calculatedChecksum[i-SINGLE_OUTPUT_LENGTH+5]; }
        else if( i > SINGLE_OUTPUT_LENGTH-9 ) { output[i] = successSegment[i-SINGLE_OUTPUT_LENGTH+8]; }
        else if( i > SINGLE_OUTPUT_LENGTH-12 ) { output[i] = SET_SLAVE[i-SINGLE_OUTPUT_LENGTH+11]; }
        else if( i > SINGLE_OUTPUT_LENGTH-15 ) { output[i] = slaveSegment[i-SINGLE_OUTPUT_LENGTH+14]; }
        else { output[i] = INITIATE[i-SINGLE_OUTPUT_LENGTH+17]; }
    }
    output[*outputLength] = '\0';

    return output;
}

/*
    Function: Attempts to turn on the laser and formats the output string.
    Inputs: The pointer to the laser value and a pointer for the length of the output.
    Outputs: The formatted output string from turning the laser on.
*/
char* laser_on( int* laser, int* outputLength ) {
    // Attempt to turn the laser on.
    char successSegment[3] = { '0', '0', '\0' };
    if( !(*laser) ) {
        successSegment[1] = '1';
        *laser = 1;
    }

    // Calculate the new checksum value.
    char* values[4] = { COMMAND_ADDRESS, LASER_ON, successSegment };
    char* calculatedChecksum = calculate_checksum( values, 3 );

    // Format the output string.
    *outputLength = SINGLE_OUTPUT_LENGTH;
    char* output = malloc( (*outputLength+1) * sizeof( char ) );
    for( int i = 0; i < SINGLE_OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > SINGLE_OUTPUT_LENGTH-3 ) { output[i] = END[i-SINGLE_OUTPUT_LENGTH+2]; }
        else if( i > SINGLE_OUTPUT_LENGTH-6 ) { output[i] = calculatedChecksum[i-SINGLE_OUTPUT_LENGTH+5]; }
        else if( i > SINGLE_OUTPUT_LENGTH-9 ) { output[i] = successSegment[i-SINGLE_OUTPUT_LENGTH+8]; }
        else if( i > SINGLE_OUTPUT_LENGTH-12 ) { output[i] = LASER_ON[i-SINGLE_OUTPUT_LENGTH+11]; }
        else if( i > SINGLE_OUTPUT_LENGTH-15 ) { output[i] = COMMAND_ADDRESS[i-SINGLE_OUTPUT_LENGTH+14]; }
        else { output[i] = INITIATE[i-SINGLE_OUTPUT_LENGTH+17]; }
    }
    output[*outputLength] = '\0';

    return output;
}

/*
    Function: Attempts to turn off the laser and formats the output string.
    Inputs: The pointer to the laser value and a pointer for the length of the output.
    Outputs: The formatted output string from turning the laser off.
*/
char* laser_off( int* laser, int* outputLength ) {
    // Attempt to turn the laser off.
    char successSegment[3] = { '0', '0', '\0' };
    if( (*laser) ) {
        successSegment[1] = '1';
        *laser = 0;
    }

    // Calculate the new checksum value.
    char* values[4] = { COMMAND_ADDRESS, LASER_OFF, successSegment };
    char* calculatedChecksum = calculate_checksum( values, 3 );

    // Format the output string.
    *outputLength = SINGLE_OUTPUT_LENGTH;
    char* output = malloc( (*outputLength+1) * sizeof( char ) );
    for( int i = 0; i < SINGLE_OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > SINGLE_OUTPUT_LENGTH-3 ) { output[i] = END[i-SINGLE_OUTPUT_LENGTH+2]; }
        else if( i > SINGLE_OUTPUT_LENGTH-6 ) { output[i] = calculatedChecksum[i-SINGLE_OUTPUT_LENGTH+5]; }
        else if( i > SINGLE_OUTPUT_LENGTH-9 ) { output[i] = successSegment[i-SINGLE_OUTPUT_LENGTH+8]; }
        else if( i > SINGLE_OUTPUT_LENGTH-12 ) { output[i] = LASER_OFF[i-SINGLE_OUTPUT_LENGTH+11]; }
        else if( i > SINGLE_OUTPUT_LENGTH-15 ) { output[i] = COMMAND_ADDRESS[i-SINGLE_OUTPUT_LENGTH+14]; }
        else { output[i] = INITIATE[i-SINGLE_OUTPUT_LENGTH+17]; }
    }
    output[*outputLength] = '\0';

    return output;
}

/*
    Function: 
    Inputs: 
    Outputs: 
*/
char* single_measurement( int* outputLength ) {
    // Determine if an error has occured.
    int error = ( rand() % ERROR_CHANCE == 0 );

    // Create the data segments.
    char* dataSegments[6];

    // Determine the measurement.
    int measurement;
    if( !error ) {
        measurement = rand() % MAX_SENSOR_RANGE_MM;

        // Split the measurements into digits.
        int digits[6];
        for( int i = 5; i >= 0; i-- ) {
            digits[i] = (measurement % 10)+48;
            measurement /= 10;
        }

        // Convert each digit into its hex equivalent, and place it in a data segment.
        for( int i = 0; i < 6; i++ ) {
            char* segment = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
            char hex[9];
            sprintf( hex, "%08X", digits[i] );
            segment[0] = hex[6];
            segment[1] = hex[7];
            segment[2] = '\0';
            dataSegments[i] = segment;
        }
    } else {
        // Places ERR255 into the data segments.
        dataSegments[0] = "45";
        dataSegments[1] = "52";
        dataSegments[2] = "52";
        dataSegments[3] = "32";
        dataSegments[4] = "35";
        dataSegments[5] = "35";
    }

    // Calculate the new checksum value.
    char* dataChecksum = calculate_checksum( dataSegments, 6 );
    char* values[3] = { COMMAND_ADDRESS, SINGLE_MEASUREMENT, dataChecksum };
    char* calculatedChecksum = calculate_checksum( values, 3 );

    // Format the output string.
    *outputLength = MEASUREMENT_OUTPUT_LENGTH;
    char* output = malloc( (*outputLength+1) * sizeof( char ) );
    for( int i = 0; i < MEASUREMENT_OUTPUT_LENGTH; i++ ) {
        if( (i+1) % 3 == 0 ) { output[i] = ' '; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-3 ) { output[i] = END[i-MEASUREMENT_OUTPUT_LENGTH+2]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-6 ) { output[i] = calculatedChecksum[i-MEASUREMENT_OUTPUT_LENGTH+5]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-9 ) { output[i] = dataSegments[5][i-MEASUREMENT_OUTPUT_LENGTH+8]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-12 ) { output[i] = dataSegments[4][i-MEASUREMENT_OUTPUT_LENGTH+11]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-15 ) { output[i] = dataSegments[3][i-MEASUREMENT_OUTPUT_LENGTH+14]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-18 ) { output[i] = dataSegments[2][i-MEASUREMENT_OUTPUT_LENGTH+17]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-21 ) { output[i] = dataSegments[1][i-MEASUREMENT_OUTPUT_LENGTH+20]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-24 ) { output[i] = dataSegments[0][i-MEASUREMENT_OUTPUT_LENGTH+23]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-27 ) { output[i] = SINGLE_MEASUREMENT[i-MEASUREMENT_OUTPUT_LENGTH+26]; }
        else if( i > MEASUREMENT_OUTPUT_LENGTH-30 ) { output[i] = COMMAND_ADDRESS[i-MEASUREMENT_OUTPUT_LENGTH+29]; }
        else { output[i] = INITIATE[i-MEASUREMENT_OUTPUT_LENGTH+32]; }
    }
    output[*outputLength] = '\0';

    return output;
}