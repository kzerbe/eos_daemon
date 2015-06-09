#include "lib/eos/OpenFlowActionConverter.h"

OpenFlowActionConverter::OpenFlowActionConverter(const eos::flow_action_t& action)
{
    //ctor
}

OpenFlowActionConverter::OpenFlowActionConverter(const std::istream is)
{

}

size_t OpenFlowActionConverter::ToBuffer(OpenFlowRelease release, std::ostream& os)
{
    return 0;
}


bool OpenFlowActionConverter::ToFlowAction(OpenFlowRelease release, eos::flow_action_t& action)
{
    return false;
}
