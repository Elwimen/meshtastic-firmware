#pragma once
#include "SinglePortModule.h"

class DetectionSensorModule : public SinglePortModule, private concurrency::OSThread
{
  public:
    DetectionSensorModule() : SinglePortModule("detection", meshtastic_PortNum_DETECTION_SENSOR_APP), OSThread("DetectionSensor")
    {
    }

    /**
     * Returns claimed hardware to a benign state so the module can be torn down live: drops the
     * pullup on the pin it actually bound (remembered at setup, in case config changed since) and
     * powers the sensor back down where the board has an enable pin.
     */
    ~DetectionSensorModule();

  protected:
    virtual int32_t runOnce() override;

  private:
    bool firstTime = true;
    uint8_t boundPin = 0; // pin claimed at setup; 0 = never bound
    uint32_t lastSentToMesh = 0;
    bool wasDetected = false;
    void sendDetectionMessage();
    void sendCurrentStateMessage(bool state);
    bool hasDetectionEvent();
};

extern DetectionSensorModule *detectionSensorModule;