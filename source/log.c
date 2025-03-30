#include "log.h"

/**
 * Takes a type and a void pointer to the variable or literal to
 * be printed to the mGBA debug console.
 * Acceptable types: CHAR, INT, PTR, U16, U32
 */
void mgbaLog(Type type, void* messagePtr) {
    *REG_DEBUG_ENABLE = 0xC0DE;

    int maxCharsPerLine = 64;
    char message[64];
    int length = 64;

    switch (type) {
    case CHAR:
        length = sprintf(message, "char: %s", (char*)messagePtr);
        break;
    case DIRECTION:
        Direction direction = *(int*)messagePtr;
        char dirStr[11];
        switch (direction) {
        case EAST: strcpy(dirStr, "East"); break;
        case SOUTH: strcpy(dirStr, "South"); break;
        case WEST: strcpy(dirStr, "West"); break;
        case NORTH: strcpy(dirStr, "North"); break;
        case SOUTHEAST: strcpy(dirStr, "Southeast"); break;
        case SOUTHWEST: strcpy(dirStr, "Southwest"); break;
        case NORTHEAST: strcpy(dirStr, "Northeast"); break;
        case NORTHWEST: strcpy(dirStr, "Northwest"); break;
        default: strcpy(dirStr, "Stationary"); break;
        }
        length = sprintf(message, "direction: %s", dirStr);
        break;
    case S32:
        length = sprintf(message, "s32: %d", *(s32*)messagePtr);
        break;
    case INT:
        length = sprintf(message, "int: %d", *(int*)messagePtr);
        break;
    case INTHEX:
        int numInt = *(int*)messagePtr;
        char* hex = toHex(numInt);
        length = sprintf(message, "inthex: %s", hex);
        free(hex);
        break;
    case S16:
        length = sprintf(message, "s16: %d", *(s16*)messagePtr);
        break;
    case PTR:
        length = sprintf(message, "ptr: %p", messagePtr);
        break;
    case U16:
        length = sprintf(message, "u16: %u", *(u16*)messagePtr);
        break;
    case U16HEX:
        u16 numHex16 = *(u16*)messagePtr;
        hex = toHex(numHex16);
        length = sprintf(message, "u16hex: %s", hex);
        free(hex);
        break;
    case U32:
        length = sprintf(message, "u32: %u", *(u32*)messagePtr);
        break;
    case U32HEX:
        u32 numHex = *(u32*)messagePtr;
        hex = toHex(numHex);
        length = sprintf(message, "u32hex: %s", hex);
        free(hex);
        break;
    case SPLITWORD: // basically prints two ints split by a dot
        s16 shi = (*(union SplitWord*)messagePtr).HALF_U.HI;
        s16 slo = (*(union SplitWord*)messagePtr).HALF_U.LO;
        length = sprintf(message, "signed SplitWord: %d.%hu", shi, slo);
        break;
    case USPLITWORD:
        s16 uhi = (*(union SplitWord*)messagePtr).HALF_U.HI;
        s16 ulo = (*(union SplitWord*)messagePtr).HALF_U.LO;
        length = sprintf(message, "unsigned SplitWord: %d.%d", uhi, ulo);
        break;
    }

    int charsLeft = length;
    while (charsLeft) {
        int charsToWrite = min(charsLeft, maxCharsPerLine);
        memcpy(REG_DEBUG_STRING, message, length);
        *REG_DEBUG_FLAGS = 2 | 0x100;
        messagePtr += charsToWrite;
        charsLeft -= charsToWrite;
    }
}

char* toHex(int num) {
    char* hex = malloc(sizeof(char) * 9);
    hex[8] = '\n';
    char hexChars[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    for (int i = 0; i < 8; i++) {
        int mask = 0xF << (i * 4);
        hex[7 - i] = hexChars[(num & mask) >> (i * 4)];
    }
    return hex;
}
