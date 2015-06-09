
#include <eos/sdk.h>


#include "configuration.h"
#include "Daemon.h"
#include "lib/eos/DirectFlowProgrammer.h"

int main(int argc, char** argv)
{
    eos::sdk sdk;

    DirectFlowProgrammer programmer(sdk);
    Daemon daemon(sdk, ServerPort, ServerBacklog);

    sdk.main_loop(argc, argv);

    return 0;
}

