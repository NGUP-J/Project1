#include "resource_holder.h"


    ResourceHolder& ResourceHolder::get()
    {
        static ResourceHolder holder;
        return holder;
    }

    ResourceHolder::ResourceHolder()
        : fonts("fonts", "ttf")
        , textures("img", "png")
        , soundBuffers("sfx", "ogg")
    {
    }
