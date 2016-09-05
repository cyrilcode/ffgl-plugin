//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_MYPLUGIN_H
#define FFGLPLUGIN_MYPLUGIN_H

#include <FFGLPluginSDK.h>
#include <FFGLExtensions.h>
#include <FFGLShader.h>

template <class FX>
class MyPlugin : public CFreeFrameGLPlugin {
    FX fx;
public:
    MyPlugin() {
        fx = FX();
        SetMinInputs(0);
        SetMaxInputs(0);
    }
    ~MyPlugin() {}

    DWORD ProcessOpenGL(ProcessOpenGLStruct* pGL)
    {
        return fx.process();
    }
    DWORD InitGL(const FFGLViewportStruct *vp)
    {
        extensions.Initialize();
        if (extensions.multitexture==0 || extensions.ARB_shader_objects==0)
            return FF_FAIL;

        return fx.init(extensions);
    }
    DWORD DeInitGL()
    {
        return fx.deinit();
    }

    static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance) {
        *ppOutInstance = new MyPlugin();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

    FFGLExtensions extensions;
};


#endif //FFGLPLUGIN_MYPLUGIN_H
