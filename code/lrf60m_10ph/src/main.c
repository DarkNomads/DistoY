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
    int initiated = 0;

    /* Sensor Values */
    int* slave = malloc( sizeof( int ) );
    *slave = ( rand() % SLAVE_MAX ) + SLAVE_MIN;
    int* laser = malloc( sizeof( int ) );
    *laser = 0;

    /* Sensor Loop */
    while( 1 ) {
        // Attempt to read data from the input file.
        char* data = readData( INPUT_FILE, inputFileLength );

        // If there is data, perform actions.
        if( *inputFileLength > 0 ) {
            // Clear the input file.
            clearData( INPUT_FILE );

            // Count how many segments are in the data.
            int segmentsCount = 0;
            for( int i = 0; i < *inputFileLength; i++ ) {
                if( i+1 == *inputFileLength ) { i++; }
                if( i % 3 == 0 ) { segmentsCount++; }
            }

            // Split the data into segments.
            char* segments[segmentsCount];
            for( int i = 0; i < segmentsCount; i++ ) {
                char* segment = malloc( (SEGMENT_LENGTH+1) * sizeof( char ) );
                segment[0] = data[3*i];
                segment[1] = data[(3*i)+1];
                segment[2] = '\0';
                segments[i] = segment;
            }

            // Check if a command has been initiated.
            if( strcmp( segments[0], INITIATE ) == 0 ) {
                initiated = 1;
            }

            // Block the command if one has not been initiated yet.
            if( !initiated ) {
                printf("No command initiated, ignoring all data...\n");
                continue;
            }
            
            // Block the command if it has an invalid command length.
            if( segmentsCount < 5 ) {
                printf("Invalid command length, ignoring all data...\n");
                continue;
            }

            // Set the target address for the command.
            char* targetAddress = segments[1];

            // Set the command.
            char* command = segments[2];

            // Set the checksum.
            char* checksum = segments[segmentsCount-2];

            // Check if the slave address is being read.
            if( strcmp( command, READ_SLAVE ) == 0 ) {
                // Ensure data has exactly 5 segments.
                if( segmentsCount != 5 ) {
                    printf("Read slave command expects 5 segments of data, ignoring all data...\n");
                    continue;
                }

                // Ensure the command is being issued to the master address.
                if( strcmp( targetAddress, MASTER_ADDRESS ) != 0 ) {
                    printf("Read slave command must be sent to master address.\n");
                    continue;
                } 

                // Ensure the checksum value is correct.
                if( strcmp( checksum, READ_SLAVE ) != 0 ) {
                    printf("Incorrect checksum value, ignoring all data...\n");
                    continue;
                }

                // Ensure there is a valid end segment.
                if( strcmp( segments[segmentsCount-1], END ) != 0 ) {
                    printf("Invalid end segment, ignoring all data...\n");
                    continue;
                }
                
                // Read the slave address.
                int* outputLength = malloc( sizeof( int ) );
                char* output = read_slave( *slave, outputLength );
                printf( "Writing slave address to the output file...\n" );
                while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                printf( "Slave address written.\n" );
            }

            // Check if the slave address is being set.
            else if( strcmp( command, SET_SLAVE ) == 0  ) {
                // Ensure data has exactly 6 segments.
                if( segmentsCount != 6 ) {
                    printf("Set slave command expects 6 segments of data, ignoring all data...\n");
                    continue;
                }

                // Ensure the command is being issued to the master address.
                if( strcmp( targetAddress, MASTER_ADDRESS ) != 0 ) {
                    printf("Set slave command must be sent to master address.\n");
                    continue;
                }

                // Set the data segment.
                char* dataSegment = segments[3];

                // Ensure the checksum value is correct.
                char* values[3] = { targetAddress, command, dataSegment };
                char* calculatedChecksum = calculate_checksum( values, 3 );
                if( strcmp( checksum, calculatedChecksum ) != 0 ) {
                    printf("Incorrect checksum value, ignoring all data...\n");
                    continue;
                }

                // Ensure there is a valid end segment.
                if( strcmp( segments[segmentsCount-1], END ) != 0 ) {
                    printf("Invalid end segment, ignoring all data...\n");
                    continue;
                }

                // Set the new slave.
                int* outputLength = malloc( sizeof( int ) );
                char* output = set_slave( slave, dataSegment, checksum, outputLength );
                printf( "Writing new slave address to the output file...\n" );
                while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                printf( "New slave address written.\n" );
            }

            // Check if the laser if being is being turned on.
            else if( strcmp( command, LASER_ON ) == 0  ) {
                // Ensure data has exactly 5 segments.
                if( segmentsCount != 5 ) {
                    printf("Laser ON command expects 5 segments of data, ignoring all data...\n");
                    continue;
                }

                // Ensure the command is being issued to the command address.
                if( strcmp( targetAddress, COMMAND_ADDRESS ) != 0 ) {
                    printf("Laser ON command must be sent to command address.\n");
                    continue;
                }

                // Set the data segment.
                char* dataSegment = segments[3];

                // Ensure the checksum value is correct.
                char* values[2] = { targetAddress, command };
                char* calculatedChecksum = calculate_checksum( values, 2 );
                if( strcmp( checksum, calculatedChecksum ) != 0 ) {
                    printf("Incorrect checksum value, ignoring all data...\n");
                    continue;
                }

                // Ensure there is a valid end segment.
                if( strcmp( segments[segmentsCount-1], END ) != 0 ) {
                    printf("Invalid end segment, ignoring all data...\n");
                    continue;
                }

                // Turn the laser on.
                int* outputLength = malloc( sizeof( int ) );
                char* output = laser_on( laser, outputLength );
                printf( "Writing laser ON to the output file...\n" );
                while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                printf( "Laser ON written.\n" );
            }

            // Check if the laser if being is being turned off.
            else if( strcmp( command, LASER_OFF ) == 0  ) {
                // Ensure data has exactly 5 segments.
                if( segmentsCount != 5 ) {
                    printf("Laser OFF command expects 5 segments of data, ignoring all data...\n");
                    continue;
                }

                // Ensure the command is being issued to the command address.
                if( strcmp( targetAddress, COMMAND_ADDRESS ) != 0 ) {
                    printf("Laser OFF command must be sent to command address.\n");
                    continue;
                }

                // Set the data segment.
                char* dataSegment = segments[3];

                // Ensure the checksum value is correct.
                char* values[2] = { targetAddress, command };
                char* calculatedChecksum = calculate_checksum( values, 2 );
                if( strcmp( checksum, calculatedChecksum ) != 0 ) {
                    printf("Incorrect checksum value, ignoring all data...\n");
                    continue;
                }

                // Ensure there is a valid end segment.
                if( strcmp( segments[segmentsCount-1], END ) != 0 ) {
                    printf("Invalid end segment, ignoring all data...\n");
                    continue;
                }

                // Turn the laser off.
                int* outputLength = malloc( sizeof( int ) );
                char* output = laser_off( laser, outputLength );
                printf( "Writing laser OFF to the output file...\n" );
                while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                printf( "Laser OFF written.\n" );
            }

            // Check if a single measurement is being taken.
            else if( strcmp( command, SINGLE_MEASUREMENT ) == 0 ) {
                // Ensure data has exactly 5 segments.
                if( segmentsCount != 5 ) {
                    printf("Single measurement command expects 5 segments of data, ignoring all data...\n");
                    continue;
                }

                // Ensure the command is being issued to the command address.
                if( strcmp( targetAddress, COMMAND_ADDRESS ) != 0 ) {
                    printf("Single measurement command must be sent to command address.\n");
                    continue;
                }

                // Ensure the checksum value is correct.
                char* values[2] = { targetAddress, command };
                char* calculatedChecksum = calculate_checksum( values, 2 );
                if( strcmp( checksum, calculatedChecksum ) != 0 ) {
                    printf("Incorrect checksum value, ignoring all data...\n");
                    continue;
                }

                // Ensure there is a valid end segment.
                if( strcmp( segments[segmentsCount-1], END ) != 0 ) {
                    printf("Invalid end segment, ignoring all data...\n");
                    continue;
                }

                // Record a single measurment reading.
                int* outputLength = malloc( sizeof( int ) );
                char* output = single_measurement( outputLength );
                printf( "Writing single measurement to the output file...\n" );
                while( !writeData( OUTPUT_FILE, output ) ) { sleep(1); }
                printf( "Single measurement written.\n" );

            } 

            // If the command is invalid, output what the unknown command was.
            else {
                printf( "Unknown command: '%s'\n", data );
            }
        }

        // Wait for one second before reading input again.
        sleep( 1 );
    }

    return 0;
}