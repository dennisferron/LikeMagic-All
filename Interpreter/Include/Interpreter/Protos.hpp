// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Namespace.hpp"

namespace LikeMagic {
    class RuntimeTypeSystem;
    namespace Backends {
        namespace Io {
            class IoVM;
        }
    }
}

namespace Interpreter{
    void add_protos(LikeMagic::Backends::Io::IoVM&, LikeMagic::RuntimeTypeSystem&);
}
