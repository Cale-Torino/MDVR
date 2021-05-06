// New function to send 'items' codes which are held in the array 'data'
void sendMulti (const uint8_t& items, const uint32_t* data)
{
    for (int i = 0; i < 2; i++) 
    {
        for (uint8_t itemIndex = 0; itemIndex < items; ++itemIndex)
        {
            irsend.sendNEC(data[itemIndex], 32);
            delay(1000);
        }
    }
    delay(5000); //5 second delay between each signal burst
}

void loop () {
    static const uint8_t MaxItems = 3;
    uint32_t  data[MaxItems] = {0x1067E21D,0x106722DD,0x106722DD,0x106722DD,0x106722DD,0x106722DD,0x106722DD,0x10676897,0x10676897,0x10676897,0x10676897,0x10676897,0x10676897,0x10678877,0x10676897,0x1067A857,0x1067A857,0x10678877,0x1067A857};

    sendMulti(MaxItems, data);
}