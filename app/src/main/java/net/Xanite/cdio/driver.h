#ifndef CDIO_DRIVER_H_
#define CDIO_DRIVER_H_

// تعريفاتك هنا

// Include general driver return code types
#include <cdio/driver_return_code.h>

// Define iso711_t and iso733_t types
typedef unsigned char iso711_t;  // ID data type

#ifndef ISO733_T_DEFINED
#define ISO733_T_DEFINED
typedef uint64_t iso733_t;       // Mode and other numeric data type
#endif

// Define constants for array sizes within the structure
#define MAX_NAME_LENGTH 256  
#define MAX_TEXT_LENGTH 256  
#define EMPTY_ARRAY_SIZE 256  

// Define the rock_t structure that represents the basic object
typedef struct {
    iso711_t len_id;              // Length of identifier
    iso711_t ext_ver;             // Extended version
    char data[MAX_TEXT_LENGTH];   // Additional data
    iso733_t st_mode;             // File mode
    iso733_t st_nlinks;           // Number of links
    iso733_t st_uid;              // User ID
    iso733_t st_gid;              // Group ID
    iso733_t dev_high;            // High part of device ID
    iso733_t dev_low;             // Low part of device ID
    char text[MAX_TEXT_LENGTH];   // Additional text
    char name[MAX_NAME_LENGTH];   // Object name
} rock_t;

// Function to initialize the structure
void init_rock_t(rock_t *rock) {
    rock->len_id = 0;
    rock->ext_ver = 0;
    rock->st_mode = 0;
    rock->st_nlinks = 0;
    rock->st_uid = 0;
    rock->st_gid = 0;
    rock->dev_high = 0;
    rock->dev_low = 0;
    memset(rock->data, 0, MAX_TEXT_LENGTH);
    memset(rock->text, 0, MAX_TEXT_LENGTH);
    memset(rock->name, 0, MAX_NAME_LENGTH);
}

#endif // DRIVER_H