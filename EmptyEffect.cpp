//
// Created by Darren Mothersele on 05/09/2016.
//

#include "EmptyEffect.h"


FFGL_PLUGIN(EmptyEffect,"DZ00","Empty Source Effect",FF_SOURCE,"Sample FFGL Plugin",
    "by Darren Mothersele - www.darrenmothersele.com")


char *fragmentShaderCode =
        "uniform vec3 color;"
                "uniform float blueness;"
        "void main() "
                "{"
                "   gl_FragColor = vec4(color,1);"
                "}";


PluginConfig EmptyEffect::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.minInputs = 0;
    pluginConfig.maxInputs = 0;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Red", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Green", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.params.push_back({"Blue", FF_TYPE_STANDARD, 0.5f});
    return pluginConfig;
}

void EmptyEffect::init(FFGLShader &shader) {
    colorLocation = shader.FindUniform("color");
}

void EmptyEffect::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    extensions.glUniform3fARB(colorLocation, paramValues[0], paramValues[1], paramValues[2]);
}








