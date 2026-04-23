#include "Flags.h"

bool check_Flag(uint8_t flags, int index) {	return (flags & (1 << index)) != 0; }
