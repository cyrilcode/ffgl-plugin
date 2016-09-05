//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_EMPTYEFFECT_H
#define FFGLPLUGIN_EMPTYEFFECT_H

#include "MyPlugin.h"

class EmptyEffect {

    float redness = 0.5f;
    float greenness = 0.5f;
    float blueness = 0.5f;
    GLint colorLocation;

public:
    PluginConfig getConfig();

    void init(FFGLShader &shader);
    void process(std::vector<float> &paramValues, FFGLExtensions &extensions);

};


#endif //FFGLPLUGIN_EMPTYEFFECT_H
