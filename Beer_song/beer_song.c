#include "beer_song.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>


void recite(uint8_t start_bottles, uint8_t take_down, char **song){
    int verse = 0;
    int final = 0;
    for (int i = start_bottles; i > start_bottles - take_down; i--) {
        if (i > 1) {
            // Verse when there are more than one bottle
            sprintf(song[verse++], "%d bottles of beer on the wall, %d bottles of beer.", i, i);
            if (i - 1 == 1) {
                sprintf(song[verse++], "Take one down and pass it around, 1 bottle of beer on the wall.");
            } else {
                sprintf(song[verse++], "Take one down and pass it around, %d bottles of beer on the wall.", i - 1);

            }
        } else if (i == 1) {
            // Verse when there is only one bottle
            sprintf(song[verse++], "1 bottle of beer on the wall, 1 bottle of beer.");
            sprintf(song[verse++], "Take it down and pass it around, no more bottles of beer on the wall.");
            final = 1;
        }
    }

    // Final verse when there are no more bottles
    if (start_bottles - take_down <= 0 && final == 0) {
        sprintf(song[verse++], "No more bottles of beer on the wall, no more bottles of beer.");
        sprintf(song[verse++], "Go to the store and buy some more, 99 bottles of beer on the wall.");
    }
}