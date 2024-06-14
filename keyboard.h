#ifndef SWITCHES_H
#define SWITCHES_H
#include "gpio_defs.h"

// Column is on port D for interrupt support
#define C1_POS (5)
#define C2_POS (0)
#define C3_POS (2)
// ROW is on port A 
#define R1_POS (5)
#define R2_POS (4)
#define R3_POS (2)
#define R4_POS (1)

// Function prototypes
extern void init(void);

// Shared variables
extern volatile unsigned count;

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
