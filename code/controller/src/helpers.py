# Function: Clears any data from a file.
# Inputs: A file name.
# Outputs: None.
def clearData( filename ):
    file = open( filename, 'w' )
    file.write( '' )
    file.close()

# Function: Writes data to a specified file, the file must already be empty.
# Inputs: A file name and data to be written.
# Outputs: True if the write is successful, or False if not.
def writeData( filename, data ):
    # Ensure the file has no data.
    file = open( filename, 'r' )
    line = file.readline()
    file.close()
    if( len(line) > 0 ):
        return False

    # Otherwise, write data to the file.
    file = open( filename, 'w' )
    file.write( data )
    file.close()
    return True

# Function: Reads the first line of a file and returns it.
# Inputs: A file name.
# Outputs: The first line string.
def readData( filename ):
    file = open( filename, 'r' )
    line = file.readline()
    file.close()
    return line

# Function: Appends data to the end of the file.
# Inputs: A file name.
# Outputs: None.
def appendData( filename, data ):
    file = open( filename, 'a' )
    file.write( data )
    file.close()

# Function: Deletes the last line of a file.
# Inputs: A file name.
# Outputs: None.
def deleteLastLine( filename ):
    file = open( filename, 'r+' )
    current = previous = file.tell()
    while file.readline():
        previous = current
        current = file.tell()
    file.truncate( previous )