//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_MYPLUGIN_H
#define FFGLPLUGIN_MYPLUGIN_H

#include <FFGLPluginSDK.h>
#include <FFGLExtensions.h>
#include <FFGLShader.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#define FFGL_PLUGIN(CLASS,CODE,NAME,TYPE,DESC,ABOUT) \
    static CFFGLPluginInfo PluginInfo (MyPlugin<CLASS>::CreateInstance, \
    CODE,NAME,1,000,1,000,TYPE,DESC,ABOUT);

char *vertexShaderCode =
        "void main()"
                "{"
                "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
                "  gl_TexCoord[1] = gl_MultiTexCoord1;"
                "  gl_FrontColor = gl_Color;"
                "}";

class PluginParamInfo {
public:
    std::string name;
    DWORD type;
    float defaultValue;
    PluginParamInfo(std::string n, DWORD t, float d) : name(n), type(t), defaultValue(d) {}
};

class PluginConfig {
public:
    int minInputs = 0;
    int maxInputs = 0;
    std::vector<PluginParamInfo> params;
    std::string shaderCode;
};

template <class FX>
class MyPlugin : public CFreeFrameGLPlugin {
    FX fx;
    PluginConfig config;
    std::unordered_map<std::string,DWORD> paramMap;
    std::vector<float> paramValues;
    DWORD paramCount;

public:
    MyPlugin() {
        fx = FX();
        config = fx.getConfig();
        SetMinInputs(config.minInputs);
        SetMaxInputs(config.maxInputs);
        paramCount = 0;
        for (auto i : config.params)
        {
            paramMap.insert({i.name, paramCount});
            SetParamInfo(paramCount, i.name.c_str(), i.type, i.defaultValue);
            paramCount++;
        }
        paramValues.reserve(paramCount);
    }
    ~MyPlugin() {}

    DWORD ProcessOpenGL(ProcessOpenGLStruct* pGL)
    {
        shader.BindShader();

        fx.process(paramValues, extensions);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-1.0f,  1.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f( 1.0,  1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f( 1.0, -1.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        shader.UnbindShader();
        return FF_SUCCESS;
    }
    DWORD InitGL(const FFGLViewportStruct *vp)
    {
        extensions.Initialize();
        if (extensions.multitexture==0 || extensions.ARB_shader_objects==0)
            return FF_FAIL;

        shader.SetExtensions(&extensions);
        shader.Compile(vertexShaderCode,config.shaderCode.c_str());
        shader.BindShader();
        fx.init(shader);
        shader.UnbindShader();
        return FF_SUCCESS;
    }
    DWORD DeInitGL()
    {
        shader.FreeGLResources();
        return FF_SUCCESS;
    }

    DWORD	SetParameter(const SetParameterStruct* pParam) {
        if (pParam != NULL) {
            if (pParam->ParameterNumber < paramCount) {
                paramValues[pParam->ParameterNumber] = *((float *)(unsigned)&(pParam->NewParameterValue));
                return FF_SUCCESS;
            }
        }
        return FF_FAIL;
    }

    static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance) {
        *ppOutInstance = new MyPlugin();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

    FFGLExtensions extensions;
    FFGLShader shader;
};


#endif //FFGLPLUGIN_MYPLUGIN_H

