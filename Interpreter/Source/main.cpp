// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "Interpreter/Bindings.hpp"
#include "Interpreter/Protos.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Backends::Io;

using namespace Interpreter;

#include <sstream>
#include <stdexcept>

#include "boost/algorithm/string/trim.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

// Predicate for trimming characters up to a directory marker.
struct IsNotDir { bool operator()(char c) { return c != '/' && c != '\\'; } };

int main(int argc, char const* argv[])
{
    try
    {
        RuntimeTypeSystem type_sys;
        add_bindings(type_sys);

        IoVM vm(type_sys);
        vm.add_proto("CppFalse", false, false);
        add_protos(vm, type_sys);

        if (argc != 2)
        {
            std::cout << std::endl;
            std::cout << "LikeMagic Io binding library." << std::endl;
            std::cout << "To run file from system commandline: LikeMagic <filename.io>" << std::endl;
            std::cout << "To run file from the Io> prompt: doFile(\"<filename.io>\")" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Type 'exit' to quit." << std::endl;
            vm.run_cli();
        }
        else
        {
            std::string scriptPath(argv[1]);
            boost::algorithm::trim_right_if(scriptPath, IsNotDir());
            vm.add_proto("scriptPath", scriptPath, true);

            std::stringstream code;
            code << "doFile(\"" << argv[1] << "\")";
            vm.do_string(code.str());
        }
    }
    catch (std::logic_error e)
    {
        std::cout << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
    }
    catch (std::exception e)
    {
        std::cout << "LikeMagic exited with exception " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "LikeMagic exited with unknown error." << std::endl;
    }

    std::cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );

    return 0;
}
