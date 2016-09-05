//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_EVILSHADER_H
#define FFGLPLUGIN_EVILSHADER_H

#include "MyPlugin.h"

class EvilShader {

    GLint resValueLocation;
    GLint inputTextureLocation;

public:
    PluginConfig getConfig();

    void init(FFGLShader &shader);
    void process(std::vector<float> &paramValues, FFGLExtensions &extensions);


};


#endif //FFGLPLUGIN_EVILSHADER_H
