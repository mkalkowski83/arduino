#ifndef FLOAT_FORMATTER_H
#define FLOAT_FORMATTER_H

class FloatFormatter {
public:
    // Format a float value into a string with 2 decimal places
    static void format(char* buffer, float value, const char* suffix = "") {
        int intValue = (int)(value * 100);
        sprintf(buffer, "%d.%02d%s", intValue / 100, intValue % 100, suffix);
    }
};

#endif // FLOAT_FORMATTER_H 