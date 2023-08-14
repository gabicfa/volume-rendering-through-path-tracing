#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

extern int SAMPLES_PER_PIXEL;
extern int MAX_DEPTH;
extern int NUM_LIGHT_SAMPLES;
extern int NUM_WIDTH;
extern int NUM_HEIGHT;
extern int SCENE;

void readConfig(const std::string& filename);

#endif