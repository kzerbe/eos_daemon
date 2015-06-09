#ifndef OPENFLOWACTIONCONVERTER_H
#define OPENFLOWACTIONCONVERTER_H

#include <eos/types/directflow.h>

#include "OpenFlowRelease.h"

class OpenFlowActionConverter
{
    public:
        OpenFlowActionConverter(const eos::flow_action_t& action);
        OpenFlowActionConverter(const std::istream is);

        size_t ToBuffer(OpenFlowRelease release, std::ostream& os);
        bool ToFlowAction(OpenFlowRelease release, eos::flow_action_t& action);
};

#endif // OPENFLOWACTIONCONVERTER_H
