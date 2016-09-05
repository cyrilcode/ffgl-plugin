//
// Created by Darren Mothersele on 05/09/2016.
//

#include "EmptyEffect.h"

static CFFGLPluginInfo PluginInfo (
        MyPlugin<EmptyEffect>::CreateInstance,	// Create method
        "DZ00",								// Plugin unique ID
        "Empty Source Effect",					// Plugin name
        1,						   			// API major version number
        000,								  // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_SOURCE,						// Plugin type
        "Sample FFGL plugin",	// Plugin description
        "by Darren Mothersele - www.darrenmothersele.com" // About
);


char *vertexShaderCode =
        "void main()"
                "{"
                "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
                "  gl_TexCoord[1] = gl_MultiTexCoord1;"
                "  gl_FrontColor = gl_Color;"
                "}";

char *fragmentShaderCode =
        "void main() "
                "{"
                "   gl_FragColor = vec4(1,0,0,1);"
                "}";


DWORD EmptyEffect::init(FFGLExtensions &extensions) {
    shader.SetExtensions(&extensions);
    shader.Compile(vertexShaderCode,fragmentShaderCode);

    shader.BindShader();
    // init shader
    shader.UnbindShader();

    return FF_SUCCESS;
}

DWORD EmptyEffect::deinit() {
    shader.FreeGLResources();
    return FF_SUCCESS;
}

DWORD EmptyEffect::process() {

    shader.BindShader();

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









