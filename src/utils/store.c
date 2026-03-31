/* #include "../include/utils/store.h"


void Erase_User_Page() {
    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t pageError;

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
    eraseInitStruct.NbPages = 1; //reading more about this... since the pages start at 1? 
    // maybe this captures pages from the start address provided?

    HAL_FLASHEx_Erase(&eraseInitStruct, &pageError); //we might need to check for pageError... I might do that later
}


uint8_t Read_Flash_Byte(uint32_t address) {
    return *(__IO uint8_t*)address;
}

uint16_t Read_Flash_HalfWord(uint32_t address) {
    return *(__IO uint16_t*)address;
}

void get_name(char read_into[]) {
    for (int i = 0; i < 7; i++) {
        read_into[i] = (char)Read_Flash_Byte(NAME_ADDR_START + i); //continously read and cast as character
    }
}

uint16_t get_score() {
    return Read_Flash_HalfWord(SCORE_ADDR_START); //score is uint16_t
}

uint8_t get_sound_preferences() {
    //sound preference is a bool... honestly would have been nice if i could just use a bit... but there is nothing else to save.... unfortunately
    return Read_Flash_Byte(SOUND_ADDR_START); 
}

void save_all_settings(const char name[], uint16_t score, uint8_t sound_pref) {
    //I was thinking of combining all values into one large value and storing it all together, but that would not be possible
    //name (8 bytes including the null terminator) + score (2 bytes) + sound_pref (1 byte) = 11 bytes ... wth is type that would hve 11 bytes

    //unlock
    HAL_FLASH_Unlock();

    // we have to erase all first... 
    Erase_User_Page();

    //write Name (7 bytes + 1 byte null terminator) to memory - we will write as HalfWords (16-bit) because our flash prefers it
    //please make sure the char array is null terminated y'know...
    for (int i = 0; i < 7; i += 2) {
        uint16_t data = name[i] | (name[i+1] << 8); //piece two uint8_ts into one uint16_t
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, NAME_ADDR_START + i, data);
    }

    // write Score (16-bit)
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, SCORE_ADDR_START, (uint64_t)score); //casting to uint64_t here, becuase that is what this function takes 
    //but no worries, we are not saving those chunks
    // write Sound Pref (8-bit as halfword)
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, SOUND_ADDR_START, (uint64_t)sound_pref);

    //lock after use
    HAL_FLASH_Lock();
} */