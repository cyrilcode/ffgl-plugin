//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_UNDERWATERLIFE_H
#define FFGLPLUGIN_UNDERWATERLIFE_H

#include "MyPlugin.h"
#include <chrono>

class UnderwaterLife
{
    GLint resolutionLocation;
    GLint timeLocation;

    double elapsedTime;
    float globalTime;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

public:
    PluginConfig getConfig();

    void init(FFGLShader &shader);
    void process(std::vector<float> &paramValues, FFGLExtensions &extensions);

    double GetCounter();
};


#endif //FFGLPLUGIN_UNDERWATERLIFE_H
