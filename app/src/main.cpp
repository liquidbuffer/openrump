#include <iostream>
#include <openrump/App.hpp>

int main(int argc, char** argv)
{
    OpenRump::BaseApp* theApp = new OpenRump::App(argv[0]);
    theApp->go();
    delete theApp;

	return 0;
}
