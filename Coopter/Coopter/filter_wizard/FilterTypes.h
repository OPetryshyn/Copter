#ifndef FILTERTYPES_H
#define FILTERTYPES_H

namespace FilterParams {
    enum FilterType
    {
        NONE        = 0x00,
        LPF         = 0x01,
        BPF         = 0x02,
        HPF         = 0x03
    };
}

#endif // FILTERTYPES_H
