#ifndef __VEHI_BASIC__
#define __VEHI_BASIC__

#define ID_CAR_LENGTH 9
#define ITS_A_CAR 1
#define ITS_A_TRUCK 2
#define ITS_A_MOTORCYCLE 3

// ANSI escape codes for text color
#define ANSI_COLOR_BLACK   "\x1b[90m"
#define ANSI_COLOR_RED     "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[92m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[94m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[97m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//vehicle types
typedef enum {
	REGULAR,
	HYBRID,
	ELECTRIC,
	vehicleTypeSize
} eEngineType;

typedef enum {
	black, white,
	blue, silver,
	red, green,
	yellow, colorSize
}    eColor;

static const char* engineTypeStr[vehicleTypeSize] = { "Regular","Hybrid","Electric" };
static const char* colorStr[colorSize] = { "Black","White","Blue","Silver",
											"Red","Green","Yellow" };
typedef struct {
	eEngineType engineType;
	int year;
	eColor color;
	char id[ID_CAR_LENGTH];
	int price;
	int vehicleType;

} VehicleBasic;


#endif