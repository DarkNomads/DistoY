#ifndef OPERATIONS_H
#define OPERATIONS_H
char* calculate_checksum( char**, int );
char* read_slave( int, int* );
char* set_slave( int*, char*, char*, int* );
char* laser_on( int*, int* );
char* laser_off( int*, int* );
char* single_measurement( int* );
#endif