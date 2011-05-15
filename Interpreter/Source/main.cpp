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

using namespace std;

// Predicate for trimming characters up to a directory marker.
struct IsNotDir { bool operator()(char c) { return c != '/' && c != '\\'; } };

void do_cli(IoVM& vm)
{
    cout << std::endl;
    cout << "LikeMagic Io binding library." << std::endl;
    cout << "To run file from system commandline: LikeMagic <filename.io>" << std::endl;
    cout << "To run file from the Io> prompt: doFile(\"<filename.io>\")" << std::endl;
    cout << "" << std::endl;
    cout << "Type 'exit' to quit." << std::endl;
    vm.run_cli();
}

void do_file(IoVM& vm, string file_name)
{
    std::string scriptPath(file_name);
    boost::algorithm::trim_right_if(scriptPath, IsNotDir());
    vm.add_proto("scriptPath", scriptPath, true);

    std::stringstream code;
    code << "doFile(\"" << file_name << "\")";
    vm.do_string(code.str());
}

int main(int argc, char const* argv[])
{
    try
    {
        RuntimeTypeSystem type_sys;
        add_bindings(type_sys);

        IoVM vm(type_sys);

        for (int i=1; i<argc; ++i)
        {
            if (string(argv[i]) == "--runCLI")
                do_cli(vm);
            else
                do_file(vm, argv[i]);
        }
    }
    catch (std::logic_error e)
    {
        cout << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
    }
    catch (std::exception e)
    {
        cout << "LikeMagic exited with exception " << e.what() << std::endl;
    }
    catch (...)
    {
        cout << "LikeMagic exited with unknown error." << std::endl;
    }

    cout << "Press enter..." << std::endl;
    std::cin.ignore( 99, '\n' );

    return 0;
}
