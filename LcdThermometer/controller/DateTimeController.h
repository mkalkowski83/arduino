#ifndef DATE_TIME_CONTROLLER_H
#define DATE_TIME_CONTROLLER_H

#include <LcdManager.h>
#include <Controller.h>
#include <RTClib.h>
#include "TimedExecutor.h"

class DateTimeController : public Controller {
private:
  LcdManager &lcdManager;
  RTC_DS3231 rtc;
  
  // Time executor for updating the time display
  TimedExecutor timeUpdateExecutor;
  
  void displayDateTime() {
    DateTime now = rtc.now();
    
    // Clear row 1 before writing new time/date
    lcdManager.clearRow(1);
    
    // Display time on the row 1
    lcdManager.setCursor(0, 1);
    
    // Format time string with leading zeros
    char timeStr[9]; // HH:MM + null terminator
    sprintf(timeStr, "%02d:%02d", now.hour(), now.minute());
    
    // Format date string with leading zeros
    char dateStr[11]; // DD/MM/YYYY + null terminator
    sprintf(dateStr, "%02d/%02d/%04d", now.day(), now.month(), now.year());
    
    // Calculate available space and determine the best layout
    uint8_t columns = lcdManager.getColumns();
    
    // If there's enough space for both on one line (with labels)
    lcdManager.print(timeStr);
    lcdManager.print(" ");
    lcdManager.print(dateStr);
    
  }

public:
  DateTimeController(LcdManager &lcd, unsigned long updateInterval = 1000)
    : lcdManager(lcd), timeUpdateExecutor(updateInterval) {}
  
  void begin() override {
    if (!rtc.begin()) {
      lcdManager.clearRow(1);
      lcdManager.setCursor(0, 1);
      lcdManager.print("RTC not found!");
      return;
    }
    
    // Set the RTC to the date & time this sketch was compiled
    // Uncomment this line when setting up for the first time
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    // Display initial date and time
    displayDateTime();
  }
  
  void update() override {
    if (timeUpdateExecutor.shouldExecute()) {
      displayDateTime();
    }
  }
  
  const char* getName() override {
    return "DateTimeController";
  }
};

#endif // DATE_TIME_CONTROLLER_H 