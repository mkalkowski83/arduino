#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "SevSegShift.h"

class DisplayManager {
private:
    SevSegShift display;
    byte numDigits;
    byte* digitPins;
    const byte segmentPins[8] = {0, 1, 2, 3, 4, 5, 6, 7}; // DP, G, F, E, D, C, B, A - fixed order for shift register
    int currentNumber;
    int currentDecimalPlaces;
    
public:
    DisplayManager(int shiftPinDs, int shiftPinShcp, int shiftPinStcp, byte* digits) 
        : display(shiftPinDs, shiftPinShcp, shiftPinStcp, 1, true), 
          numDigits(4), 
          currentNumber(0), 
          currentDecimalPlaces(0) {
        digitPins = digits;
    }
    
    void setup() {
        bool resistorsOnSegments = false;
        byte hardwareConfig = COMMON_ANODE;
        bool updateWithDelays = true;
        bool leadingZeros = false;
        bool disableDecPoint = false;
        
        display.begin(hardwareConfig, numDigits, digitPins, segmentPins, 
                     resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
        display.setBrightness(0);
    }
    
    void showNumber(int number, int decimalPlaces) {
        currentNumber = number;
        currentDecimalPlaces = decimalPlaces;
        
        display.setNumber(number, decimalPlaces);
    }
    
    void refreshCurrentDisplay() {
        display.refreshDisplay();
    }
};

#endif 