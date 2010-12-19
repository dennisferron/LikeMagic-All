// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Interpreter/Bindings.hpp"

#include "Bindings/Irrlicht/Bindings.hpp"
#include "Bindings/Bullet/Bindings.hpp"
#include "Bindings/Custom/Bindings.hpp"
#ifdef USE_IRRKLANG
#include "Bindings/IrrKlang/Bindings.hpp"
#endif

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;

namespace Interpreter{

void add_bindings(RuntimeTypeSystem& type_sys)
{
    Bindings::Irrlicht::add_bindings(type_sys);
    Bindings::Bullet::add_bindings(type_sys);
    Bindings::Custom::add_bindings(type_sys);
#ifdef USE_IRRKLANG
    Bindings::IrrKlang::add_bindings(type_sys);
#endif
}

}
