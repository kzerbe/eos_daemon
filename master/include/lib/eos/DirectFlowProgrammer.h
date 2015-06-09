#ifndef DIRECTFLOWPROGRAMMER_H
#define DIRECTFLOWPROGRAMMER_H

#include <eos/sdk.h>
#include <eos/agent.h>
#include <eos/intf.h>
#include <eos/timer.h>
#include <eos/directflow.h>


class DirectFlowProgrammer
    : public eos::intf_handler      // watch for egres interface up
    , public eos::agent_handler     // watch app lifecycle
    , public eos::timeout_handler   // handle timer
{
    public:
        DirectFlowProgrammer(eos::sdk& sdk);
        virtual ~DirectFlowProgrammer();

        void CreateFlowEntry();

    protected:
        void on_initialized();
        void on_timeout();

    private:
        eos::sdk& m_sdk;
        eos::directflow_mgr* m_directFlowManager;
};

#endif // DIRECTFLOWPROGRAMMER_H
