
#include <eos/sdk.h>


#include "configuration.h"
#include "Daemon.h"


int main(int argc, char** argv)
{
    eos::sdk sdk;

    MacTableDaemon daemon(sdk, ServerPort, ServerBacklog);

    sdk.main_loop(argc, argv);

    return 0;
}

