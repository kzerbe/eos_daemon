#ifndef TRANSCODER1_0_H_INCLUDED
#define TRANSCODER1_0_H_INCLUDED


namespace OpenFlow
{
    template<>
    void Encode<Release_1_0>(std::ostream& os, const eos::flow_match_t& match)
    {
        auto fieldset = match.match_field_set();
        if (fieldset.input_intfs())
        {

        }
    }

    template <>
    void Encode<Release_1_0>(std::ostream& os, const eos::flow_action_t& match)
    {

    }

    template <>
    bool Decode<Release_1_0>(std::istream& is, eos::flow_match_t& match)
    {
        return false;
    }

    template <>
    bool Decode<Release_1_0>(std::istream& is, eos::flow_action_t& match)
    {
        return false;
    }
}


#endif // TRANSCODER1_0_H_INCLUDED
