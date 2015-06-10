#ifndef OPENFLOWRELEASE_H_INCLUDED
#define OPENFLOWRELEASE_H_INCLUDED

#include <eos/types/directflow.h>

namespace OpenFlow
{

    enum Release
    {
        Release_1_0,
        Release_1_1,
        Release_1_2,
        Release_1_3
    };


    template <int release>
    void Encode(std::ostream& os, const eos::flow_match_t& match);

    template <int release>
    void Encode(std::ostream& os, const eos::flow_action_t& match);

    template <int release>
    bool Decode(std::istream& is, eos::flow_match_t& match);

    template <int release>
    bool Decode(std::istream& is, eos::flow_action_t& match);

}

#include "lib/openFlow1_0/TransCoder1_0.h"

#endif // OPENFLOWRELEASE_H_INCLUDED
