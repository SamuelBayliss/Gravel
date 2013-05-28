/* 
 * File:   preload.c
 * Author: sb1708
 *
 * Created on May 21, 2013, 11:02 PM
 */



/*
 * 
 */

#include <stdlib.h>

void register_routines() { 
    
}

void (*vlog_startup_routines[])() = {
   register_routines,
   NULL
};