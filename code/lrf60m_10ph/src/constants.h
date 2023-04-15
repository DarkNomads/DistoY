/* I/O */
#define INPUT_FILE "../shared/data/lrf60m_10ph.in"
#define OUTPUT_FILE "../shared/data/lrf60m_10ph.out"

/* Global Variables */
#define SEGMENT_LENGTH 2
#define SINGLE_OUTPUT_LENGTH 17
#define MEASUREMENT_OUTPUT_LENGTH 32
#define SLAVE_MIN 1
#define SLAVE_MAX 127
#define CHECKSUM_CONSTANT 127
#define MAX_SENSOR_RANGE_MM 60001
#define ERROR_CHANCE 5
#define MASTER_ADDRESS "00"
#define COMMAND_ADDRESS "01"
#define INITIATE "AA"
#define END "A8"

/* Commands */
#define READ_SLAVE "04"
#define SET_SLAVE "41"
#define LASER_ON "42"
#define LASER_OFF "43"
#define SINGLE_MEASUREMENT "44"
