#include <iostream>
#include <exception>
#include <openrump/App.hpp>

int main(int argc, char** argv)
{
    OpenRump::BaseApp* theApp = new OpenRump::App(argv[0]);
    try
    {
        theApp->go();
    } catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    delete theApp;

	return 0;
}
