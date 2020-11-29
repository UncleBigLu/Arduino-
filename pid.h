#pragma once

#include "filter.h"

#define P 1
#define I 0

int errPrevInternal = 0;
int ctrlPrevInternal = 0;
int pid(int data);
