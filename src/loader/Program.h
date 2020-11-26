#ifndef DANZUN_PROGRAM_H_INCLUDED
#define DANZUN_PROGRAM_H_INCLUDED

#include <map>
#include <string>
#include <memory>

#include "../render/Texture.h"
#include "../render/Shader.h"
#include "../ani/Animation.h"
#include "../ui/Font.h"

#include "Script.h"

namespace dan {
    class Program {
    public:
        Program(const Script &init);
    };
}

#endif
