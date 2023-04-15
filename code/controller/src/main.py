from constants import *
from helpers import *

import time
import datetime
import numpy as np
import math

# Main Device Loop
def main():

    datapoint = []

    while( True ):
        # Get the user's command from the terminal.
        command = input( "Enter a command: " )

        # Help Command
        if( command == 'help' ):
            print(
                 "1. exit - Exits the program.\
                \n2. angle - Returns the current angle (pitch) of the device.\
                \n3. distance - Returns the current laser range finder distance in meters.\
                \n4. heading - Returns the current cardinal direction.\
                \n5. data point - Returns a full data point, including angle, distance, and heading.\
                \n6. save - Saves the last data point, along with its metadata, to the SD card.\
                \n7. calibrate - Recalibrates the accelerometer and magnetic field."
            )

        # Exit Command
        elif( command == 'exit' ):
            break

        # Angle Command
        elif( command == 'angle' ):
            print( "Current Angle: {0}°".format( getAngle() ) )

        # Distance Command
        elif( command == 'distance' ):
            print( "Current Distance: {0}m".format( getDistance() ) )

        # Heading Command
        elif( command == 'heading' ):
            heading, symbol = getHeading()
            print( "Current Heading: {0}° ({1})".format( heading, symbol ) )

        # Data Point Command
        elif( command == 'data point' ):
            # Generate all the data points.
            angle = getAngle()
            distance = getDistance()
            heading, symbol = getHeading()
            # Generate all additional metadata.
            timestamp = datetime.datetime.now().isoformat()
            id = int( readData( LAST_ID_FILE ) ) + 1
            # Append all data and metadata to the data point in case it is saved.
            datapoint.append( id )
            datapoint.append( angle )
            datapoint.append( distance )
            datapoint.append( heading )
            datapoint.append( symbol )
            datapoint.append( timestamp )
            # Display all data.
            print( "Data Point:\n  * Angle: {0}°\n  * Distance: {1}m\n  * Heading: {2}° ({3})".format( angle, distance, heading, symbol ) )

        # Save Command
        elif( command == 'save' ):
            # Ensure there is already data stored in the data point.
            if( len( datapoint ) == 0 ):
                print( "There is no data to be saved.\n" )
                continue
            # Convert to JSON
            json = convertToJSON( datapoint )
            print( json )
            # Update the new last ID value.
            clearData( LAST_ID_FILE )
            writeData( LAST_ID_FILE, str( datapoint[0] ) )
            # Delete the last line of the saved data file.
            deleteLastLine( SAVED_DATA_FILE )
            # If there is any other data, add a comma after its JSON object.
            if( datapoint[0] > 1 ):
                deleteLastLine( SAVED_DATA_FILE )
                appendData( SAVED_DATA_FILE, '  },\n' )
            # Add the new datapoint's JSON object.
            appendData( SAVED_DATA_FILE, json )
            # Add the last line of the saved data file back.
            appendData( SAVED_DATA_FILE, ']' )
            # Delete the data in the data point.
            datapoint = []

        # Calibration Command
        elif( command == 'calibrate' ):
            calibrateSensors()
            print( "Device successfully calibrated." )

        # Other Commands
        else:
            print( "Unknown command: '{0}', type 'help' for a list of commands.".format( command ) )

        # Add a newline.
        print()

# Angle Routine
def getAngle():
    # Make sure the inclinometer is unlocked.
    writeData( INCLINOMETER_INPUT_FILE, INCLINOMETER_UNLOCK_COMMAND )

    # Attempt to send the read pitch command, or repeat after one second.
    while( not writeData( INCLINOMETER_INPUT_FILE, INCLINOMETER_READ_PITCH_COMMAND ) ):
        time.sleep( 1 )

    # Attempt to read the pitch data, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( INCLINOMETER_OUTPUT_FILE )
        time.sleep( 1 )

    # Clear the output file.
    clearData( INCLINOMETER_OUTPUT_FILE )

    # Split the data into segments.
    segments = data.split(' ')

    # Reconstruct the high and low portions of the value.
    angleHex = segments[3] + segments[2]

    # Convert the hex string to an integer value.
    angle = int.from_bytes( bytes.fromhex( angleHex ), byteorder='big', signed=True )

    # Return the angle.
    return angle
    
# Distance Routine
def getDistance():
    # Set the laser range finder's current slave address to the command address.
    slaveAddress = ''
    while( slaveAddress != '01' ):
        slaveAddress = ''
        while( not writeData( LASER_RANGE_FINDER_INPUT_FILE, LRF_SET_SLAVE_COMMAND_ADDRESS ) ):
            time.sleep( 1 )
        while( len( slaveAddress ) == 0 ):
            slaveAddress = readData( LASER_RANGE_FINDER_OUTPUT_FILE )
            time.sleep( 1 )
        clearData( LASER_RANGE_FINDER_OUTPUT_FILE )
        slaveAddress = slaveAddress.split( ' ' )[3]

    # Turn the laser on.
    on = ''
    while( on != '01' ):
        on = ''
        while( not writeData( LASER_RANGE_FINDER_INPUT_FILE, LRF_LASER_ON_COMMAND ) ):
            time.sleep( 1 )
        while( len( on ) == 0 ):
            on = readData( LASER_RANGE_FINDER_OUTPUT_FILE )
            time.sleep( 1 )
        clearData( LASER_RANGE_FINDER_OUTPUT_FILE )
        on = on.split( ' ' )[3]

    # Get the distance measurement.
    distance = 0
    error = True
    while( error ):
        measurementHex = ''
        while( not writeData( LASER_RANGE_FINDER_INPUT_FILE, LRF_SINGLE_MEASUREMENT_COMMAND ) ):
            time.sleep( 1 )
        while( len( measurementHex ) == 0 ):
            measurementHex = readData( LASER_RANGE_FINDER_OUTPUT_FILE )
            time.sleep( 1 )
        segments = measurementHex.split( ' ' )
        clearData( LASER_RANGE_FINDER_OUTPUT_FILE )
        # Convert measurement hex to characters.
        digits = []
        for i in range(6):
            digits.append( chr( int.from_bytes( bytes.fromhex( segments[i+3] ), byteorder='big', signed=True ) ) )
        # Convert digits to integer.
        joinedDigits = ''.join( digits )
        # Check if an error occurred.
        if( joinedDigits != 'ERR255' ):
            error = False
            distance = int( joinedDigits )

    # Turn the laser off.
    off = ''
    while( off != '01' ):
        off = ''
        while( not writeData( LASER_RANGE_FINDER_INPUT_FILE, LRF_LASER_OFF_COMMAND ) ):
            time.sleep( 1 )
        while( len( off ) == 0 ):
            off = readData( LASER_RANGE_FINDER_OUTPUT_FILE )
            time.sleep( 1 )
        clearData( LASER_RANGE_FINDER_OUTPUT_FILE )
        off = off.split( ' ' )[3]

    # Return the distance measurement in meters.
    return distance/1000

# Heading Routine
def getHeading():
    # MAGNETIC X #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read magnetic x command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_MAGNETIC_X ) ):
        time.sleep( 1 )
    # Attempt to read the magnetic x, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    magnetic_x = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # MAGNETIC Y #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read magnetic y command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_MAGNETIC_Y ) ):
        time.sleep( 1 )
    # Attempt to read the magnetic y, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    magnetic_y = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # MAGNETIC Z #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read magnetic z command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_MAGNETIC_Z ) ):
        time.sleep( 1 )
    # Attempt to read the magnetic z, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    magnetic_z = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # ACCELERATION X #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read acceleration x command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_ACCELERATION_X ) ):
        time.sleep( 1 )
    # Attempt to read the acceleration x, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    acceleration_x = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # ACCELERATION Y #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read acceleration y command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_ACCELERATION_Y ) ):
        time.sleep( 1 )
    # Attempt to read the acceleration y, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    acceleration_y = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # ACCELERATION Z #
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )
    # Attempt to send the read acceleration z command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_READ_ACCELERATION_Z ) ):
        time.sleep( 1 )
    # Attempt to read the acceleration z, or repeat after one second.
    data = ""
    while( len( data ) == 0 ):
        data = readData( MAGNETOMETER_OUTPUT_FILE )
        time.sleep( 1 )
    # Clear the output file.
    clearData( MAGNETOMETER_OUTPUT_FILE )
    # Split the data into segments.
    segments = data.split(' ')
    # Reconstruct the high and low portions of the value and convert to an integer.
    hex = segments[3] + segments[2]
    acceleration_z = int.from_bytes( bytes.fromhex( hex ), byteorder='big', signed=True )

    # Vectorize the magnetic field and acceleration.
    magnetic_vector =  np.array( [ magnetic_x, magnetic_y, magnetic_z ] )
    acceleration_vector =  np.array( [ acceleration_x, acceleration_y, acceleration_z ] )

    # Generate the horizontal component vector by projecting the magnetic field onto the acceleration vector, then subtract the magnetic field vector.
    north_vector = magnetic_vector - ( ( magnetic_vector.dot( acceleration_vector ) / acceleration_vector.dot( acceleration_vector ) ) * acceleration_vector )

    # Compute the heading on the X/Y plane.
    heading = math.atan2( north_vector[0], north_vector[1] ) * 180 / math.pi

    # Normalize heading to positive value.
    if( heading < 0 ):
        heading += NORTH[1]
    
    # Determine the closest (inter)cardinal direction symbol.
    symbol = 'X'
    closest = 360
    for cardinal in HEADINGS:
        difference = abs( heading-cardinal[1] )
        if( closest > difference ):
            closest = difference
            symbol = cardinal[0]
        elif( cardinal[0] == 'N' ):
            difference = abs( heading-cardinal[2] )
            if( closest > difference ):
                closest = difference
                symbol = cardinal[0]

    # Return the heading and symbol. 
    return round( heading, 2 ), symbol

# Sensor Calibration Rountine
def calibrateSensors():
    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )

    # Attempt to send the calibrate accelerometer command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_ACCELEROMETER_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Attempt to send the save calibration command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_SAVE_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Wait for the magnetometer calibration to complete.
    time.sleep( 10 )

    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )

    # Attempt to send the calibrate magnetic field command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_MAGNETIC_FIELD_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Attempt to send the save calibration command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_SAVE_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Wait for the magnetometer calibration to complete.
    time.sleep( 10 )

    # Make sure the magnetometer is unlocked.
    writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_UNLOCK_COMMAND )

    # Attempt to send the end calibration command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_END_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Attempt to send the save calibration command, or repeat after one second.
    while( not writeData( MAGNETOMETER_INPUT_FILE, MAGNETOMETER_SAVE_CALIBRATION_COMMAND ) ):
        time.sleep( 1 )

    # Return after finishing calibration
    return

# JSON Data Conversion Routine
def convertToJSON( datapoint ):
    # Build the JSON format.
    json = '  {\n'
    json += '    "id": {0},\n'.format( datapoint[0] )
    json += '    "data": {\n'
    json += '      "angle": {0},\n'.format( datapoint[1] )
    json += '      "distance": {0},\n'.format( datapoint[2] )
    json += '      "heading": {0},\n'.format( datapoint[3] )
    json += '      "symbol": "{0}"\n'.format( datapoint[4] )
    json += '    },\n'
    json += '    "metadata": {\n'
    json += '      "timestamp": "{0}"\n'.format( datapoint[5] )
    json += '    }\n'
    json += '  }\n'

    # Return the JSON string.
    return json

if __name__ == '__main__':
    main()