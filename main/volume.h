#ifndef VOLUME_H
#define VOLUME_H

float volume(long p) {
    float vol = 2.70270 * p;  // the magic number
    float volInLiter = vol / 1000;
    float volumeInCubic = vol / 1000000;
    return volInLiter;
}

#endif 