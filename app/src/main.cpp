#include <iostream>
#include <openrump/App.hpp>

int main()
{
    OpenRump::BaseApp* theApp = new OpenRump::App();
    theApp->go();
    delete theApp;

	return 0;
}
