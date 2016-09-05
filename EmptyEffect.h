//
// Created by Darren Mothersele on 05/09/2016.
//

#ifndef FFGLPLUGIN_EMPTYEFFECT_H
#define FFGLPLUGIN_EMPTYEFFECT_H

#include "MyPlugin.h"

class EmptyEffect {

    FFGLShader shader;

public:

    DWORD init(FFGLExtensions &extensions);

    DWORD deinit();

    DWORD process();


};


#endif //FFGLPLUGIN_EMPTYEFFECT_H
