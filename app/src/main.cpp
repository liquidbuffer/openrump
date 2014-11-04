#include <iostream>
#include <exception>
#include <boost/graph/graph_concepts.hpp>
#include <openrump/App.hpp>

#ifdef _DEBUG
const char* defaultScriptFile = "../../py/Main.py";
#endif

int main(int argc, char** argv)
{
    // handle script file
    char* scriptFile = nullptr;
    if(argc < 2)
    {
#ifdef _DEBUG
        std::cout << "Warning: A script file was not specified, but since this"
            << " is a debug build, script file is defaulting to @exec_dir/../../py/Main.py"
            << std::endl;
        scriptFile = const_cast<char*>(defaultScriptFile);
#else
        std::cerr << "Error: Usage: " << argv[0] << " MyScript.py" << std::endl;
        return -1;
#endif
    }
    else
    {
        scriptFile = argv[1];
    }

    try
    {
        OpenRump::App theApp(argv[0]);
        theApp.setScript(scriptFile);
        theApp.go();
    } catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

	return 0;
}
