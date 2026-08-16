#pragma once

#include "ScanI2C.h"
#include <stddef.h>

class ScanI2CConsumer
{
  public:
    ScanI2CConsumer();
    /** Deregisters from the consumer list, so a consumer (e.g. a telemetry module) can be
     * deleted at runtime without leaving a dangling pointer behind for the next scan. */
    virtual ~ScanI2CConsumer();
    virtual void i2cScanFinished(ScanI2C *i2cScanner) = 0;
};

void ScanI2CCompleted(ScanI2C *i2cScanner);