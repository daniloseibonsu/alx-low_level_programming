#!/bin/bash
gcc -wall -pedantie -werror -wextra -c *.c
ar -rc liball.a *.o
ranlib liball.a
