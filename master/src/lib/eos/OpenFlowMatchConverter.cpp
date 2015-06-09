#include "lib/eos/OpenFlowMatchConverter.h"

OpenFlowMatchConverter::OpenFlowMatchConverter(const eos::flow_match_t& match)
{
    //ctor
}

OpenFlowMatchConverter::OpenFlowMatchConverter(const std::istream& is)
{

}


size_t OpenFlowMatchConverter::ToBuffer(OpenFlowRelease release, std::ostream& os)
{
    return 0;
}


bool OpenFlowMatchConverter::ToFlowMatch(OpenFlowRelease release, eos::flow_match_t& match)
{
    return false;
}
