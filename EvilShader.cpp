//
// Created by Darren Mothersele on 05/09/2016.
//

#include "EvilShader.h"

FFGL_PLUGIN(EvilShader,"DZEV","Evil",FF_EFFECT,"Sample FFGL Plugin",
"by Darren Mothersele - www.darrenmothersele.com")


std::string fragmentShaderCode = R"GLSL(
// Adapted from https://www.shadertoy.com/view/llS3WG

uniform vec3      iResolution;
uniform sampler2D iChannel0;

#define T texture2D(iChannel0,.5+(p.xy*=.98))
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec3 p=gl_FragCoord.xyz/iResolution-.5, o=T.rbb;
	for (float i=0.;i<50.;i++) p.z+=pow(max(0.,.5-length(T.rg)),2.)*exp(-i*.1);
	fragColor=vec4(o*o+p.z,1);
}
void main(void) {
mainImage(gl_FragColor, gl_FragCoord.xy);
}

)GLSL";


PluginConfig EvilShader::getConfig() {
    PluginConfig pluginConfig;
    pluginConfig.shaderCode = fragmentShaderCode;
    pluginConfig.params.push_back({"Speed", FF_TYPE_STANDARD, 0.5f});
    pluginConfig.inputNames.push_back({"iChannel0"});
    return pluginConfig;
}

void EvilShader::init(FFGLShader &shader) {
    resValueLocation = shader.FindUniform("iResolution");
}

void EvilShader::process(std::vector<float> &paramValues, FFGLExtensions &extensions)
{
    float vpdim[4];
    glGetFloatv(GL_VIEWPORT, vpdim);
    extensions.glUniform3fARB(resValueLocation, vpdim[2], vpdim[3], 1.0);
}


