#include "constants.h"
#include "helpers.h"
#include "operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main( int argc, char *argv[] ) {

    /* Intitialize Random */
    srand( time( NULL ) );

    /* Sensor Variables */
    int* inputFileLength = malloc( sizeof( int ) );
    time_t unlockTimer;
    int unlocked = 0;
    int calibrationMode = CALIBRATING_NONE;
    int pendingCalibrationMode = CALIBRATING_NONE;

    /* Sensor Values */
    char* pitch_h;
    char* pitch_l;
    char* magnetic_x_h;
    char* magnetic_x_l;
    char* magnetic_y_h;
    char* magnetic_y_l;
    char* magnetic_z_h;
    char* magnetic_z_l;
    char* acceleration_x_h;
    char* acceleration_x_l;
    char* acceleration_y_h;
    char* acceleration_y_l;
    char* acceleration_z_h;
    char* acceleration_z_l;


    /* Sensor Loop */
    while( 1 ) {
        // Retrieve the pitch value.
        char** pitch_data = get_pitch();
        pitch_h = pitch_data[0], pitch_l = pitch_data[1];

        // Retrive the magnetic field values.
        char** magnetic_data = get_magnetic();
        magnetic_x_h = magnetic_data[0], magnetic_x_l = magnetic_data[1];
        magnetic_y_h = magnetic_data[2], magnetic_y_l = magnetic_data[3];
        magnetic_z_h = magnetic_data[4], magnetic_z_l = magnetic_data[5];

        // Retrive the acceleration values.
        char** acceleration_data = get_acceleration();
        acceleration_x_h = acceleration_data[0], acceleration_x_l = acceleration_data[1];
        acceleration_y_h = acceleration_data[2], acceleration_y_l = acceleration_data[3];
        acceleration_z_h = acceleration_data[4], acceleration_z_l = acceleration_data[5];

        // Check if the sensor has been locked.
        if( unlocked && !isUnlocked( unlockTimer ) ) {
            unlocked = 0;
            printf("Locking sensor...\n");
        }

        // Attempt to read data from the input file.
        char* data = readData( INPUT_FILE, inputFileLength );

        // If there is data, perform actions.
        if( *inputFileLength > 0 ) {
            // Clear the input file.
            clearData( INPUT_FILE );

            // Check if the sensor is being unlocked.
            if( strcmp( data, UNLOCK_COMMAND ) == 0 ) {
                unlockTimer = unlock();
                unlocked = isUnlocked( unlockTimer );
            }

            // Check if sensor is unlocked.
            else {
                // Block the command if the sensor is currently locked.
                if( !unlocked || !isUnlocked( unlockTimer ) ) {
                    printf( "Sensor is locked, cannot execute command: '%s'.\n", data );
                    pendingCalibrationMode = CALIBRATING_NONE;
                } 
                // Otherwise, check if the command is recognized.
                else {
                    // Check if the sensor registers are being saved.
                    if( strcmp( data, SAVE_COMMAND ) == 0 ) {
                        save();
                        int calibrationChange = pendingCalibrationMode != calibrationMode;
                        if( calibrationChange ) {
                            calibrationMode = pendingCalibrationMode;
                            if( calibrationMode == CALIBRATING_NONE ) { printf( "Calibration finished.\n" ); }
                            else if( calibrationMode == CALIBRATING_ACCELEROMETER ) { printf( "Calibrating the accelerometer.\n" ); }
                            else if( calibrationMode == CALIBRATING_MAGNETIC_FIELD ) { printf( "Calibrating the magnetic field.\n" ); }
                        }
                    }

                    // Check if the pitch is being read.
                    else if( strcmp( data, READ_PITCH ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( pitch_l, pitch_h, outputLength );
                        printf( "Writing pitch data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Pitch data written.\n" );
                    }

                    // Check if the magnetic field x is being read.
                    else if( strcmp( data, READ_MAGNETIC_X ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( magnetic_x_l, magnetic_x_h, outputLength );
                        printf( "Writing magnetic field x data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Magnetic field x data written.\n" );
                    }

                    // Check if the magnetic field y is being read.
                    else if( strcmp( data, READ_MAGNETIC_Y ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( magnetic_y_l, magnetic_y_h, outputLength );
                        printf( "Writing magnetic field y data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Magnetic field y data written.\n" );
                    }

                    // Check if the magnetic field z is being read.
                    else if( strcmp( data, READ_MAGNETIC_Z ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( magnetic_z_l, magnetic_z_h, outputLength );
                        printf( "Writing magnetic field z data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Magnetic field z data written.\n" );
                    }

                    // Check if the acceleration x is being read.
                    else if( strcmp( data, READ_ACCELERATION_X ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( acceleration_x_l, acceleration_x_h, outputLength );
                        printf( "Writing acceleration x data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Acceleration x data written.\n" );
                    }

                    // Check if the acceleration y is being read.
                    else if( strcmp( data, READ_ACCELERATION_Y ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( acceleration_y_l, acceleration_y_h, outputLength );
                        printf( "Writing acceleration y data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Acceleration y data written.\n" );
                    }

                    // Check if the acceleration z is being read.
                    else if( strcmp( data, READ_ACCELERATION_Z ) == 0 ) {
                        int* outputLength = malloc( sizeof( int ) );
                        char* output = format_data( acceleration_z_l, acceleration_z_h, outputLength );
                        printf( "Writing acceleration z data to the output file...\n" );
                        while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                        printf( "Acceleration z data written.\n" );
                    }

                    // Check if the accelerometer is being calibrated.
                    else if( strcmp( data, CALIBRATE_ACCELEROMETER ) == 0 ) {
                        pendingCalibrationMode = CALIBRATING_ACCELEROMETER;
                        printf( "Calibration of accelerometer pending, awaiting save command...\n" );
                    }

                    // Check if the magnetic field is being calibrated.
                    else if( strcmp( data, CALIBRATE_MAGNETIC_FIELD ) == 0 ) {
                        pendingCalibrationMode = CALIBRATING_MAGNETIC_FIELD;
                        printf( "Calibration of magnetic field pending, awaiting save command...\n" );
                    }

                    // Check if the calibration is being ended.
                    else if( strcmp( data, END_CALIBRATION ) == 0 ) {
                        pendingCalibrationMode = CALIBRATING_NONE;
                        printf( "End calibration pending, awaiting save command...\n" );
                    }

                    // If the command is invalid, output what the unknown command was.
                    else {
                        printf( "Unknown command: '%s'\n", data );
                    }
                }
            }
        }

        // Wait for one second before reading input again.
        sleep( 1 );
    }

    return 0;
}