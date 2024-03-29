/* I/O */
#define INPUT_FILE "../shared/data/hwt905_ttl.in"
#define OUTPUT_FILE "../shared/data/hwt905_ttl.out"

/* Global Variables */
#define LOCKOUT_TIME 100
#define SEGMENT_LENGTH 2
#define HEADER_LENGTH 5
#define OUTPUT_LENGTH 14
#define INPUT_HEADER "FF AA"
#define OUTPUT_HEADER "55 5F"
#define CALIBRATING_NONE 0
#define CALIBRATING_ACCELEROMETER 1
#define CALIBRATING_MAGNETIC_FIELD 2

/* Commands */
#define UNLOCK_COMMAND "FF AA 69 88 B5"
#define SAVE_COMMAND "FF AA 00 00 00"
#define READ_PITCH "FF AA 27 3E 00"
#define READ_MAGNETIC_X "FF AA 27 3A 00"
#define READ_MAGNETIC_Y "FF AA 27 3B 00"
#define READ_MAGNETIC_Z "FF AA 27 3C 00"
#define READ_ACCELERATION_X "FF AA 27 34 00"
#define READ_ACCELERATION_Y "FF AA 27 35 00"
#define READ_ACCELERATION_Z "FF AA 27 36 00"
#define CALIBRATE_ACCELEROMETER "FF AA 01 03 00"
#define CALIBRATE_MAGNETIC_FIELD "FF AA 01 07 00"
#define END_CALIBRATION "FF AA 01 00 00"