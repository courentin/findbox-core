#ifndef memory_h
#define memory_h

#include <FlashStorage_STM32.h>

class Memory
{
public:
    bool isDiscovered()
    {
        bool isDiscovered = false;
        EEPROM.get(is_discovered_address, isDiscovered);

        return isDiscovered;
    }

    void setDiscovered()
    {
        EEPROM.put(is_discovered_address, true);
        EEPROM.commit();
    }

    void setUndiscovered()
    {
        EEPROM.put(is_discovered_address, false);
        EEPROM.commit();
    }

private:
    uint16_t is_discovered_address = 0;
};

#endif
