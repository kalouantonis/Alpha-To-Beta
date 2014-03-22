#ifndef SFMLPTRDEF_H
#define SFMLPTRDEF_H

/**
  * Used to define shared_ptr types for SFML classes
  */

#include <memory>

namespace sf
{
// Prototypes. Fine, as I will be using pointers
class RenderWindow;
class RenderTarget;
class Texture;

// Typedefs
typedef std::shared_ptr<RenderTarget> RenderTargetPtr;
typedef std::shared_ptr<Texture> TexturePtr;
// Non-modyfiable texture pointer. Can't modify data or pointer
typedef const std::shared_ptr<const Texture> ConstTexturePtr;
typedef std::shared_ptr<RenderWindow> RenderWindowPtr;
}


#endif // SFMLPTRDEF_H
