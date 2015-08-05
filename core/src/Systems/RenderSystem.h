#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <Systems/BaseRenderSystem.h>
// Include source file to remove linker errors
//#include <Systems/BaseRenderSystem.cpp>
#include <Components/Renderable.h>

typedef BaseRenderSystem<Renderable> RenderSystem;

#endif // RENDER_SYSTEM_H
