#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "cia402_common.h"

/* 0x6060 values accepted by this application. 0 is "no mode"/IDLE. */
static inline bool Cia402ModeIsSupported(int8_t mode)
{
    switch (mode)
    {
    case kOd6060_NO_MODE:
    case kOd6060_PPM:
    case kOd6060_PVM:
    case kOd6060_TPM:
    case kOd6060_HM:
    case kOd6060_CSP:
    case kOd6060_CSV:
    case kOd6060_CST:
    case kOd6060_MIT:
        return true;
    default:
        return false;
    }
}

/* Scalar (VAR) OD objects only have subindex 0. */
static inline bool Cia402ScalarSubindexIsZero(uint8_t subindex)
{
    return subindex == 0U;
}

/* J8 is the HOST entry; J9 is the BUS/master entry. */
static inline bool Cia402AccessAllowsWrite(bool host_entry, bool authority_is_host)
{
    return host_entry == authority_is_host;
}
