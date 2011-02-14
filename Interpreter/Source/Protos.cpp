// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Interpreter/Protos.hpp"

#include "Bindings/Irrlicht/Protos.hpp"
#include "Bindings/Bullet/Protos.hpp"
#include "Bindings/Custom/Protos.hpp"

#ifdef USE_IRRKLANG
#include "Bindings/IrrKlang/Protos.hpp"
#endif

#ifdef USE_RAKNET
#include "Bindings/RakNet/Protos.hpp"
#endif

using namespace LikeMagic::Backends::Io;

namespace Interpreter{

void add_protos(IoVM& vm)
{
    Bindings::Irrlicht::add_protos(vm);
    Bindings::Bullet::add_protos(vm);
    Bindings::Custom::add_protos(vm);

#ifdef USE_IRRKLANG
    Bindings::IrrKlang::add_protos(vm);
#endif

#ifdef USE_RAKNET
    Bindings::RakNet::add_protos(vm);
#endif

}


}
