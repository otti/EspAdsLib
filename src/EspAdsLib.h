// https://infosys.beckhoff.com/content/1033/tc3_ads_intro/index.html
// https://github.com/Beckhoff/ADS

#ifndef __ESP_ADS_LIB__
#define __ESP_ADS_LIB__

#include <WiFi.h>
#include <stdbool.h>
#include <stdint.h>

#include "AdsDef.h"
#include "ads.h"

#ifndef ADS_DEBUG_PRINT_ENABLE
#define ADS_DEBUG_PRINT_ENABLE 0
#endif

#if ADS_DEBUG_PRINT_ENABLE == 1
    #include <Arduino.h>
    #define ADS_DEBUG_PRINT(s) Serial.print(s);
    #define ADS_DEBUG_PRINTLN(s) Serial.println(s);
#else
    #define ADS_DEBUG_PRINT(s) ;
    #define ADS_DEBUG_PRINTLN(s) ;
#endif

namespace ADS
{
enum ADS_LIB_ERR
{
    NO_ERR = 0,
    NO_NUM_BETWEEN_POINTS = 1,
    MORE_TAHN_THREE_DIGITS_BETWEEN_POINTS = 2,
    MORE_THAN_5_POINTS = 3,
    INVALID_CHARS = 4,         // only 0...9 and point allowed
    INVALID_NUM_OF_BLOCKS = 5, // Must be exactly 6
    INVALID_LEN = 6            // Max 24 chars
};

class AmsAddr
{
  public:
    AmsAddr(char* NetId, uint16_t u16Port);
    ADS_LIB_ERR IsValid(void);
    void PrintInfo();
    sAmsAddr_t GetAmsAddr(void);
    void Change(char* NetId, uint16_t u16Port);

  private:
    ADS_LIB_ERR ConvertNetIdToBin(char* NetId);
    ADS_LIB_ERR ParseResult;
    sAmsAddr_t AmsAdr;
};

class Ads
{
  private:
    AmsAddr* pAmsSrcAddr;
    AmsAddr* pAmsDestAddr;
    uint32_t u32InvokeId;
    char DestIp[16];
    WiFiClient client;
    uint16_t u16AdsPort;

  public:
    Ads(AmsAddr* SrcAddr, AmsAddr* DestAddr, char* DestIp);
    bool Connect(void);
    void Disconnect(void);
    uint32_t Read(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t RdLen, sADS_RESP_READ_t* Response);
    uint32_t Write(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t WrLen, void* pData);
    uint32_t ReadWrite(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t RdLen, size_t WrLen, void* pWrData, sADS_RESP_READ_t* Response);
    uint32_t WritePlcVarByName(std::string VarName, void* pWrData, size_t WrLen);
    uint32_t ReadPlcVarByName(std::string VarName, void* pRdData, size_t RdLen);
    uint32_t ReadCoe(uint16_t u16Index, uint8_t u8Subindex, size_t RdLen, void* pRdData);
    uint32_t ReadCoe(uint16_t u16Index, uint8_t u8Subindex, bool bCompleteAccess, size_t RdLen, void* pRdData);
    uint32_t WriteCoe(uint16_t u16Index, uint8_t u8Subindex, size_t WrLen, void* pWrData);
    uint32_t WriteCoe(uint16_t u16Index, uint8_t u8Subindex, bool bCompleteAccess, size_t WrLen, void* pWrData);
#if ADS_DEBUG_PRINT_ENABLE == 1
    void DebugPrintHex(void* pData, size_t Len);
#endif
};
} // namespace ADS

#endif // __ESP_ADS_LIB__
