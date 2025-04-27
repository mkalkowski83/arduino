#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <LiquidCrystal.h>

class LcdManager {
private:
    LiquidCrystal lcd;
    uint8_t cols = 16;
    uint8_t rows = 2;
    uint8_t currentCol = 0;
    uint8_t currentRow = 0;
    
    // For scrolling text
    String scrollText = "";
    String pendingScrollText = ""; // Tekst oczekujący na inicjalizację
    uint8_t pendingScrollRow = 0;  // Wiersz dla oczekującego tekstu
    bool scrollTextPending = false; // Flaga wskazująca, że jest tekst do inicjalizacji
    uint8_t scrollRow = 0;
    unsigned long lastScrollTime = 0;
    unsigned long scrollDelay = 300; // milliseconds between scroll steps
    int scrollPosition = 0;
    
    // Trim text to fit within the column constraints
    String fitTextToColumns(const String &text, uint8_t startCol) {
        int availableSpace = cols - startCol;
        if (text.length() <= availableSpace) {
            return text;
        } else {
            return text.substring(0, availableSpace);
        }
    }
    
public:    
    LcdManager(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t columns = 16, uint8_t rows = 2) 
        : lcd(rs, enable, d4, d5, d6, d7), cols(columns), rows(rows) {
    }
    
    void begin() {
        lcd.begin(cols, rows);
        clearScreen();
    }
    
    void clear() {
        lcd.clear();
        currentCol = 0;
        currentRow = 0;
        scrollText = "";
        scrollTextPending = false;
    }
    
    // Clear a specific row
    void clearRow(uint8_t row) {
        if (row < rows) {
            lcd.setCursor(0, row);
            for (uint8_t i = 0; i < cols; i++) {
                lcd.print(" ");
            }
        }
    }
    
    // Clear entire screen row by row
    void clearScreen() {
        for (uint8_t i = 0; i < rows; i++) {
            clearRow(i);
        }
        currentCol = 0;
        currentRow = 0;
        scrollText = "";
        scrollTextPending = false;
    }
    
    void setCursor(uint8_t col, uint8_t row) {
        // Make sure we don't go beyond display boundaries
        if (col >= cols) col = cols - 1;
        if (row >= rows) row = rows - 1;
        
        currentCol = col;
        currentRow = row;
        lcd.setCursor(col, row);
    }
    
    // Get current cursor column
    uint8_t getCol() {
        return currentCol;
    }
    
    // Get current cursor row
    uint8_t getRow() {
        return currentRow;
    }
    
    // Get display columns
    uint8_t getColumns() {
        return cols;
    }
    
    // Get display rows
    uint8_t getRows() {
        return rows;
    }
    
    // Print text and manage cursor position
    void print(const String &text) {
        String fittedText = fitTextToColumns(text, currentCol);
        lcd.print(fittedText);
        currentCol += fittedText.length();
        if (currentCol >= cols) {
            currentCol = cols;
        }
    }
    
    void print(float value) {
        String valueStr = String(value);
        print(valueStr);
    }
    
    void print(int value) {
        String valueStr = String(value);
        print(valueStr);
    }
    
    // Print at specific position with boundary checking
    void printAt(uint8_t col, uint8_t row, const String &text) {
        setCursor(col, row);
        print(text);
    }
    
    // Prints text on a new line if it would otherwise overflow
    void safePrint(const String &text) {
        if (currentCol + text.length() > cols) {
            if (currentRow + 1 < rows) {
                setCursor(0, currentRow + 1);
            } else {
                setCursor(0, 0); // Wrap to top if at bottom
            }
        }
        print(text);
    }
    
    // Set text to scroll on a specific row - will be initialized when updateScrollText is called
    void setScrollText(const String &text, uint8_t row = 0) {
        if (row >= rows) row = rows - 1;
        
        pendingScrollText = text;
        pendingScrollRow = row;
        scrollTextPending = true;
    }
    
    // Initialize scrolling text with pending values
    void initializeScrollText() {
        if (scrollTextPending) {
            // Initialize with the full text
            scrollText = pendingScrollText;
            scrollRow = pendingScrollRow;
            scrollPosition = cols; // Start with text just off the right edge
            lastScrollTime = millis();
            scrollTextPending = false;
            
            // Clear the row before starting
            clearRow(scrollRow);
            
            // Show initial position
            uint8_t savedCol = currentCol;
            uint8_t savedRow = currentRow;
            
            // Create a combined string with extra space at beginning and end for smooth scrolling
            String fullText = "                " + scrollText + "                ";
            
            // Calculate what portion of text should be visible initially
            String visibleText = fullText.substring(scrollPosition, scrollPosition + cols);
            
            // Display the visible text
            lcd.setCursor(0, scrollRow);
            lcd.print(visibleText);
            
            // Restore cursor position
            setCursor(savedCol, savedRow);
        }
    }
    
    // Set scroll speed (milliseconds between updates)
    void setScrollSpeed(unsigned long delay) {
        scrollDelay = delay;
    }
    
    // Update the scrolling text - call this in your loop
    void updateScrollText() {
        // Initialize if there's pending text
        if (scrollTextPending) {
            initializeScrollText();
        }
        
        // Only process if we have text to scroll and enough time has passed
        if (scrollText.length() == 0 || millis() - lastScrollTime < scrollDelay) {
            return;
        }
        
        lastScrollTime = millis();
        
        // Remember current cursor position
        uint8_t savedCol = currentCol;
        uint8_t savedRow = currentRow;
        
        // Create a combined string with extra space at beginning and end for smooth scrolling
        String fullText = "                " + scrollText + "                ";
        
        // Clear the row we're scrolling
        clearRow(scrollRow);
        
        // Calculate what portion of text should be visible now
        String visibleText;
        if (scrollPosition >= 0 && scrollPosition <= fullText.length() - cols) {
            // Normal case - take a substring
            visibleText = fullText.substring(scrollPosition, scrollPosition + cols);
        } else {
            // We're at the wraparound point
            scrollPosition = 0;
            visibleText = fullText.substring(0, cols);
        }
        
        // Display the visible text
        lcd.setCursor(0, scrollRow);
        lcd.print(visibleText);
        
        // Move the position one character left for next time
        scrollPosition++;
        
        // If we've scrolled past the end, wrap back to beginning
        if (scrollPosition > scrollText.length() + 20) {
            scrollPosition = 0;
        }
        
        // Restore cursor position
        setCursor(savedCol, savedRow);
    }
    
    LiquidCrystal* getLcd() {
        return &lcd;
    }
};

#endif 