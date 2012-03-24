
#include "Interpreter/Bindings.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

using namespace LikeMagic;
using namespace Iocaste::LikeMagicAdapters;

using namespace Interpreter;

#include <sstream>
#include <stdexcept>

#include "boost/algorithm/string/trim.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

using namespace std;


//#include "IoState.h"

void IoAddonsInit(IoObject *context);

//#define IOBINDINGS

#ifdef IO_CHECK_ALLOC
#define IO_SHOW_STATS 1
#endif

#include "Iocaste/Exception.hpp"

#ifdef IO_SHOW_STATS
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double System_UserTime(void)
{
	struct rusage u;
	int r = getrusage(0, &u);
	return r == -1 ? -1 : u.ru_utime.tv_sec + (((double)u.ru_utime.tv_usec)/1000000);
}

#endif

#include <iostream>
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
    vm.add_proto("scriptPath", scriptPath, NamespacePath::global(), true);

    std::stringstream code;
    code << "doFile(\"" << file_name << "\")";
    vm.do_string(code.str());
}


int main(int argc, const char *argv[])
{
 #ifdef USE_DMALLOC
    // Starting LikeMagic in codeblocks debug mode doesn't propagate the dmalloc environment settings.  I don't know why.
    dmalloc_debug_setup("check-blank,log=~/dmalloc.log");
#endif


        // If the IoVM object is declared inside the try catch as a stack variable,
        // it gets destructed when there's an exception and then is unavailable for e.g.
        // printing the error message or the stack.  Should maybe create with new and/or
        // use an intrusive_ptr to track references to the IoVM object.
        IoVM* vm=NULL;
        RuntimeTypeSystem* type_sys=NULL;

    try
    {
        type_sys = RuntimeTypeSystem::create();
        add_bindings(*type_sys);
        vm = new IoVM(*type_sys);

        for (int i=1; i<argc; ++i)
        {
            cout << flush;
            if (string(argv[i]) == "--runCLI")
                do_cli(*vm);
            else
                do_file(*vm, argv[i]);
        }

        delete vm;
        vm=NULL;
        delete type_sys;
        type_sys=NULL;

        cout << "Press enter..." << std::endl;
        std::cin.ignore( 99, '\n' );
        return 0;
    }
    catch (Iocaste::ScriptException const& ex)
    {
        // Attempting to access ex.what() here is stepping back into Io and never coming out ??
        cout << "main.cpp caught unhandled script exception: " << ex.what() << endl << flush;
    }
    catch (std::logic_error e)
    {
        cout << "LikeMagic exited with exception '" << e.what() << "'" << std::endl;
    }
    catch (std::exception e)
    {
        cout << "Exited with exception " << e.what() << std::endl;
    }
    catch (...)
    {
        cout << "main.cpp caught unhandled unknown exception" << endl;
    }

    cout << "Exiting with error" << endl;
    cin.ignore(99, '\n');

    delete vm;
    delete type_sys;

    return -1;
}
