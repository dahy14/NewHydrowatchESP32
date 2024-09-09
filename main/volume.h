#ifndef VOLUME_H
#define VOLUME_H


float vol;
float volumeInCubic;
float CONSTANT = 2.70270;

float volume(float pulse) {
    vol = CONSTANT * pulse;  // the magic number
    volumeInCubic = vol / 1000000;
    return vol;
}

#endif 