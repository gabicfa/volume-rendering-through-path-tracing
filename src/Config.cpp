#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int SAMPLES_PER_PIXEL;
int MAX_DEPTH;
int NUM_LIGHT_SAMPLES;
int NUM_WIDTH;
int NUM_HEIGHT;
int SCENE;

void readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string variable;
        char equal_sign;
        int value;
        if (!(iss >> variable >> equal_sign >> value) || equal_sign != '=') {
            std::cerr << "Invalid format: " << line << std::endl;
            continue;  // skip this line
        }
        
        if (variable == "SAMPLES_PER_PIXEL") {
            SAMPLES_PER_PIXEL = value;
        } else if (variable == "MAX_DEPTH") {
            MAX_DEPTH = value;
        } else if (variable == "NUM_LIGHT_SAMPLES") {
            NUM_LIGHT_SAMPLES = value;
        } else if (variable == "NUM_WIDTH") {
            NUM_WIDTH = value;
        } else if (variable == "NUM_HEIGHT") {
            NUM_HEIGHT = value;
        } else if (variable == "SCENE") {
            SCENE = value;
        } else {
            std::cerr << "Unknown variable: " << variable << std::endl;
        }
    }
    file.close();
}
