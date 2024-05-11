#!/bin/bash

gcc cube.c -Wconversion -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lm -o cube
