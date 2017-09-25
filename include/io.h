

#ifndef IO_H
#define IO_H

#include <string.h>
#include <ctype.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"


size_t GetFileSize(FILE *file);
json_t *LoadJsonFile(const char *file);

#endif