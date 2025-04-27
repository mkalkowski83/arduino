#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <LiquidCrystal.h>
#include <string.h>

class LcdManager {
private:
    LiquidCrystal lcd;
    uint8_t cols = 16;
    uint8_t rows = 2;
    
    // Variables for text scrolling
    char scrollText[2][100]; // Store text for scrolling (max 100 chars per row)
    int scrollPosition[2] = {0, 0}; // Current scroll position for each row
    bool isScrolling[2] = {false, false}; // Whether each row is in scrolling mode
    
public:    
    LcdManager(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t columns = 16, uint8_t rows = 2) 
        : lcd(rs, enable, d4, d5, d6, d7), cols(columns), rows(rows) {
    }
    
    ~LcdManager() {
        clear();
    }

    void printAtRow(const char* message, uint8_t row) {
        if (row >= rows) return;
        
        lcd.setCursor(0, row);
        lcd.print(message);
    }
    
    void begin() {
        lcd.begin(cols, rows);        
        lcd.clear();
    }
    
    void clear() {
        lcd.clear();
        // Reset scrolling state
        isScrolling[0] = false;
        isScrolling[1] = false;
    }
    
    // Set up text for scrolling in a specific row (row 0 = first row, row 1 = second row)
    void setScrollingText(const char* text, uint8_t row) {
        if (row >= rows) return;
        
        // Buffer size accounting for the extra spaces
        size_t bufferSize = sizeof(scrollText[row]) - 1;
        
        // Copy text to scrolling buffer
        size_t textLen = strlen(text);
        if (textLen > bufferSize - cols) {
            textLen = bufferSize - cols; // Ensure we have space for the padding spaces
        }
        
        // Copy the main text
        strncpy(scrollText[row], text, textLen);
        
        // Add spaces to the end to create separation between wrapped text
        for (int i = 0; i < cols; i++) {
            if (textLen + i < bufferSize) {
                scrollText[row][textLen + i] = ' ';
            }
        }
        
        // Ensure null termination
        scrollText[row][textLen + cols > bufferSize ? bufferSize : textLen + cols] = '\0';
        
        // Reset scroll position
        scrollPosition[row] = 0;
        
        // Enable scrolling if text is longer than display width
        isScrolling[row] = (strlen(text) > cols);
        
        // Display the initial text
        updateScrollingRow(row);
    }
    
    // Update scrolling for a specific row - call this regularly to animate the scrolling
    void updateScrollingRow(uint8_t row) {
        if (row >= rows || !isScrolling[row]) return;
        
        int textLen = strlen(scrollText[row]);
        if (textLen <= cols) {
            // Text fits on screen, just display it
            lcd.setCursor(0, row);
            lcd.print(scrollText[row]);
            for (uint8_t i = textLen; i < cols; i++) {
                lcd.write(' ');
            }
            return;
        }
        
        // Clear the row
        lcd.setCursor(0, row);
        for (uint8_t i = 0; i < cols; i++) {
            lcd.write(' ');
        }
        
        // Display the portion of text at current scroll position
        lcd.setCursor(0, row);
        
        for (uint8_t i = 0; i < cols; i++) {
            int charPos = (scrollPosition[row] + i) % textLen;
            lcd.write(scrollText[row][charPos]);
        }
        
        // Increment scroll position for next update
        scrollPosition[row] = (scrollPosition[row] + 1) % textLen;
    }
    
    // Update all scrolling rows - convenient method to call from loop()
    void updateScrolling() {
        for (uint8_t row = 0; row < rows; row++) {
            if (isScrolling[row]) {
                updateScrollingRow(row);
            }
        }
    }
};

#endif 