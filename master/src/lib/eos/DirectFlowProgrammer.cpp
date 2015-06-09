#include "lib/eos/DirectFlowProgrammer.h"

DirectFlowProgrammer::DirectFlowProgrammer(eos::sdk& sdk)
    : eos::intf_handler(sdk.get_intf_mgr())
    , eos::agent_handler(sdk.get_agent_mgr())
    , eos::timeout_handler(sdk.get_timeout_mgr())
    , m_sdk(sdk)
    , m_directFlowManager(sdk.get_directflow_mgr())
{
}

DirectFlowProgrammer::~DirectFlowProgrammer()
{
}

void DirectFlowProgrammer::CreateFlowEntry()
{
    eos::flow_match_t match;
}


void DirectFlowProgrammer::on_initialized()
{

}

void DirectFlowProgrammer::on_timeout()
{

}

