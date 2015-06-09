#ifndef OPENFLOWMATCHCONVERTER_H_H
#define OPENFLOWMATCHCONVERTER_H_H

#include <eos/types/directflow.h>

#include "OpenFlowRelease.h"

class OpenFlowMatchConverter
{
    public:
        OpenFlowMatchConverter(const eos::flow_match_t& match);
        OpenFlowMatchConverter(const std::istream& is);

        size_t ToBuffer(OpenFlowRelease release, std::ostream& os);
        bool ToFlowMatch(OpenFlowRelease release, eos::flow_match_t& match);
};

#endif // OPENFLOWMATCHCONVERTER_H_H
