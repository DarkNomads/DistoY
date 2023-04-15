#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <time.h>

time_t unlock();
int isUnlocked( time_t );
void save();
char* format_data( char*, char*, int* );
char** get_pitch();
char** get_magnetic();
char** get_acceleration();

#endif