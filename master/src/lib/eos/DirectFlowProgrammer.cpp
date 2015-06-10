#include "lib/eos/DirectFlowProgrammer.h"


#include "lib/Transcoder.h"


DirectFlowProgrammer::DirectFlowProgrammer(eos::sdk& sdk)
    : eos::intf_handler(sdk.get_intf_mgr())
    , eos::agent_handler(sdk.get_agent_mgr())
    , eos::timeout_handler(sdk.get_timeout_mgr())
    , m_sdk(sdk)
    , m_directFlowManager(sdk.get_directflow_mgr())
{
    auto ingress = eos::intf_id_t("Ethernet1");
    auto match = eos::flow_match_t();
    eos::flow_match_field_set_t fieldSet;
    fieldSet.input_intfs_is(true);
    match.match_field_set_is(fieldSet);
    match.input_intf_set(ingress);

    std::ostringstream ss;
    OpenFlow::Encode<OpenFlow::Release_1_0>(ss, match);
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

