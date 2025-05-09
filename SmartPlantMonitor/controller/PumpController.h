#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H

#include "Controller.h"
#include "../service/IrrigationService.h"

class PumpController : public Controller {
private:
    IrrigationService* irrigationService;
    
public:
    PumpController(IrrigationService* service) 
        : irrigationService(service) {
    }
    
    void begin() override {
        if (irrigationService != nullptr) {
            irrigationService->begin();
        }
    }
    
    void update() override {
        if (irrigationService != nullptr) {
            irrigationService->update();
        }
    }
    
    const char* getName() override {
        return "PumpController";
    }
};

#endif // PUMP_CONTROLLER_H 