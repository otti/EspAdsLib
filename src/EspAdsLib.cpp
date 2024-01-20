#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EspAdsLib.h"

// Constructor
ADS::AmsAddr::AmsAddr(char* NetId, uint16_t u16Port)
{
    this->Change(NetId, u16Port);
}

void ADS::AmsAddr::Change(char* NetId, uint16_t u16Port)
{
    this->ParseResult = ADS::AmsAddr::ConvertNetIdToBin(NetId);
    this->AmsAdr.port = u16Port;
}

void ADS::AmsAddr::PrintInfo(void)
{
    uint8_t i;
    char sNetId[25];
    sprintf(sNetId, "%i.%i.%i.%i.%i.%i", this->AmsAdr.netId.b[0], this->AmsAdr.netId.b[1], this->AmsAdr.netId.b[2], this->AmsAdr.netId.b[3], this->AmsAdr.netId.b[4], this->AmsAdr.netId.b[5]);

    ADS_DEBUG_PRINTLN("NetId Info")
    ADS_DEBUG_PRINTLN("---------------------------")
    ADS_DEBUG_PRINT("NetId: ")
    ADS_DEBUG_PRINTLN(sNetId)
    ADS_DEBUG_PRINT("Port:  ")
    ADS_DEBUG_PRINTLN(this->AmsAdr.port)
    if (this->ParseResult == ADS::ADS_LIB_ERR::NO_ERR)
        ADS_DEBUG_PRINTLN("NetId has a valid format")
    else
    {
        ADS_DEBUG_PRINT("NetId has an invalid format (")
        ADS_DEBUG_PRINT(this->ParseResult)
        ADS_DEBUG_PRINTLN(")")
    }
}

sAmsAddr_t ADS::AmsAddr::GetAmsAddr(void)
{
    return this->AmsAdr;
}

ADS::ADS_LIB_ERR ADS::AmsAddr::ConvertNetIdToBin(char* NetId)
{
    uint8_t u8ChrCnt = 0;
    uint8_t u8NoCnt = 0;
    uint8_t u8BlockCnt = 0;
    uint8_t u8Num = 0;

    char c;

    while (1)
    {
        c = *NetId;

        if ((c >= '0') && (c <= '9'))
        {
            u8Num *= 10;
            u8Num += c - '0';
            u8NoCnt++;
        }
        else if ((c == '.') || (c == '\0'))
        {
            if (u8NoCnt == 0) // there must be at least one char between two points
                return ADS::ADS_LIB_ERR::NO_NUM_BETWEEN_POINTS;

            if (u8NoCnt > 3)
                return ADS::ADS_LIB_ERR::MORE_TAHN_THREE_DIGITS_BETWEEN_POINTS;

            if (u8BlockCnt >= 6)
                return ADS::ADS_LIB_ERR::MORE_THAN_5_POINTS;

            this->AmsAdr.netId.b[u8BlockCnt] = u8Num;
            u8Num = 0;
            u8NoCnt = 0;
            u8BlockCnt++;
        }
        else
        {
            return ADS::ADS_LIB_ERR::INVALID_CHARS; // Invalid character only 0..9 and point allowed
        }

        if (c == '\0') // End of string?
        {
            if (u8BlockCnt == 6)                 // there must be exactly 6 blocks
                return ADS::ADS_LIB_ERR::NO_ERR; // done
            else
                return ADS::ADS_LIB_ERR::INVALID_NUM_OF_BLOCKS;
        }

        if (u8ChrCnt > 24) // larger than max length?
            return ADS::ADS_LIB_ERR::INVALID_LEN;

        NetId++; // Next char
        u8ChrCnt++;
    }
}

ADS::ADS_LIB_ERR ADS::AmsAddr::IsValid(void)
{
    return this->ParseResult;
}

#if ADS_DEBUG_PRINT_ENABLE == 1
void ADS::Ads::DebugPrintHex(void* pData, size_t Len)
{
    uint8_t* pu8Data = (uint8_t*)pData;
    char Hex[64];
    char Chars[32];
    uint8_t u8ChrPos = 0;
    uint32_t u32Adr = 0;
    char Number[5];
    uint8_t u8RemainingEmptyBytes;

    ADS_DEBUG_PRINTLN("Number of Bytes: " + String(Len));

    ADS_DEBUG_PRINTLN("       | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |");
    ADS_DEBUG_PRINTLN("-------|-------------------------------------------------|-----------------");

    while (Len--)
    {
        if ((u32Adr & 0xF) == 0) // Every 16 bytes
        {
            sprintf(Hex, "0x%04X | ", u32Adr);
            u8ChrPos = 0;
        }

        sprintf(Number, "%02X ", *pu8Data);
        strcat(Hex, Number);
        if ((*pu8Data >= ' ') && (*pu8Data <= '~'))
            Chars[u8ChrPos++] = *pu8Data;
        else
            Chars[u8ChrPos++] = '.'; // unprintable char

        pu8Data++;
        u32Adr++;

        // fill last incomplete line with ' '
        if ((Len == 0) && ((u32Adr & 0xF) != 0))
        {
            u8RemainingEmptyBytes = 0x0F - (u32Adr & 0xF) + 1;
            strcpy(Number, "   ");
            while (u8RemainingEmptyBytes--)
                strcat(Hex, Number);
        }

        if (((u32Adr & 0xF) == 0) || (Len == 0)) // Every 16 bytes or last char reached
        {
            Chars[u8ChrPos++] = '\0'; // terminate the string
            ADS_DEBUG_PRINTLN(String(Hex) + "| " + String(Chars));
        }
    }
}
#endif

// ------------------------------------------------------------------
// Implementation of ADS class
// ------------------------------------------------------------------

ADS::Ads::Ads(AmsAddr* SrcAddr, AmsAddr* DestAddr, char* DestIp)
{
    this->pAmsSrcAddr = SrcAddr;
    this->pAmsDestAddr = DestAddr;
    this->u16AdsPort = ADS_TCP_SERVER_PORT;
    this->u32InvokeId = 1;
    strncpy(this->DestIp, DestIp, sizeof(this->DestIp) - 1); // Minus terminating zero
}

bool ADS::Ads::Connect(void)
{
    ADS_DEBUG_PRINT("ADS connection to ");
    ADS_DEBUG_PRINT(this->DestIp);

    if (!this->client.connect(this->DestIp, this->u16AdsPort))
    {
        ADS_DEBUG_PRINTLN(" failed");
        return false;
    }
    else
    {
        ADS_DEBUG_PRINTLN(" established");
        return true;
    }
}

void ADS::Ads::Disconnect(void)
{
    ADS_DEBUG_PRINT("ADS connection to ");
    ADS_DEBUG_PRINT(this->DestIp);
    ADS_DEBUG_PRINTLN(" terminated");

    this->client.stop();
}

uint32_t ADS::Ads::Write(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t WrLen, void* pData)
{
    sAMS_PACKET_t AmsSendPacket;
    sAMS_PACKET_t AmsReceivePacket;

    ADS_DEBUG_PRINTLN("ADS Write");

    AmsSendPacket.TargetAmsNetId = this->pAmsDestAddr->GetAmsAddr();
    AmsSendPacket.SourceAmsNetId = this->pAmsSrcAddr->GetAmsAddr();

    AmsSendPacket.u16CommandId = ADSSRVID_WRITE;
    AmsSendPacket.u16StateFlags = STATE_FLAG_MASK_ADS_CMD;
    AmsSendPacket.u32Length = (sizeof(sADS_REQ_WRITE_t) - ADS_MAX_DATA_SIZE) + WrLen;
    AmsSendPacket.u32ErrorCode = 0;
    AmsSendPacket.u32InvokeId = this->u32InvokeId++;

    AmsSendPacket.WriteRequest.u32IndexGroup = u32IdxGrp;
    AmsSendPacket.WriteRequest.u32IndexOffset = u32IdxOffset;
    AmsSendPacket.WriteRequest.u32Length = WrLen;

    memcpy(AmsSendPacket.WriteRequest.Data, pData, WrLen);

    AmsSendPacket.TmsTcpHeader.reserved = 0;
    AmsSendPacket.TmsTcpHeader.u32Length = SIZEOF_AMS_HEADER + sizeof(sADS_REQ_WRITE_t) - ADS_MAX_DATA_SIZE + WrLen;

    // DebugPrintHex(&AmsSendPacket, (size_t)(AmsSendPacket.TmsTcpHeader.u32Length + sizeof(sAMS_TCP_HEADER_t)));

    // Write AmsCmd
    if (this->client.write((uint8_t*)&AmsSendPacket, (size_t)(AmsSendPacket.TmsTcpHeader.u32Length + sizeof(sAMS_TCP_HEADER_t))) <= 0)
        ADS_DEBUG_PRINTLN("AdsWrite: no bytes send");

    unsigned long timeout = millis();
    while (this->client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            ADS_DEBUG_PRINTLN(">>> AdsWrite: Client Timeout !");
            ADS_DEBUG_PRINTLN(">>> Check your ADS router settings and your SrcNetId and DestNetId");
            this->client.stop();
            return ADSERR_DEVICE_TIMEOUT;
        }
    }

    // Read AmsResponse
    if ((this->client.read((uint8_t*)&AmsReceivePacket, sizeof(AmsReceivePacket))) <= 0)
        ADS_DEBUG_PRINTLN("AdsWrite: ERROR reading from socket");

    ADS_DEBUG_PRINTLN("ADS Write Response: " + String(AmsReceivePacket.u32WrResponse))

    return AmsReceivePacket.u32WrResponse;
}

uint32_t ADS::Ads::Read(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t RdLen, sADS_RESP_READ_t* Response)
{
    sAMS_PACKET_t AmsSendPacket;
    sAMS_PACKET_t AmsReceivePacket;

    ADS_DEBUG_PRINTLN("ADS Read");

    AmsSendPacket.TargetAmsNetId = this->pAmsDestAddr->GetAmsAddr();
    AmsSendPacket.SourceAmsNetId = this->pAmsSrcAddr->GetAmsAddr();

    AmsSendPacket.u16CommandId = ADSSRVID_READ;
    AmsSendPacket.u16StateFlags = STATE_FLAG_MASK_ADS_CMD;
    AmsSendPacket.u32Length = sizeof(sADS_REQ_READ_t);
    AmsSendPacket.u32ErrorCode = 0;
    AmsSendPacket.u32InvokeId = this->u32InvokeId++;

    AmsSendPacket.ReadRequest.u32IndexGroup = u32IdxGrp;
    AmsSendPacket.ReadRequest.u32IndexOffset = u32IdxOffset;
    AmsSendPacket.ReadRequest.u32Length = RdLen;

    AmsSendPacket.TmsTcpHeader.reserved = 0;
    AmsSendPacket.TmsTcpHeader.u32Length = SIZEOF_AMS_HEADER + sizeof(sADS_REQ_READ_t);

    // Write Read Request
    if (client.write((uint8_t*)&AmsSendPacket, (size_t)(SIZEOF_AMS_HEADER + SIZEOF_AMS_TCP_HEADER + sizeof(sADS_REQ_READ_t))) <= 0)
        ADS_DEBUG_PRINTLN("AdsRead: no bytes send");

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            ADS_DEBUG_PRINTLN(">>>AdsRead:  Client Timeout !");
            ADS_DEBUG_PRINTLN(">>> Check your ADS router settings and your SrcNetId and DestNetId");
            return ADSERR_DEVICE_TIMEOUT;
        }
    }

    // Read AmsResponse
    if ((client.read((uint8_t*)&AmsReceivePacket, sizeof(AmsReceivePacket))) <= 0)
        ADS_DEBUG_PRINTLN("AdsRead: ERROR reading from socket");

    memcpy(Response, &AmsReceivePacket.ReadResponse, sizeof(sADS_RESP_READ_t));

    return AmsReceivePacket.ReadResponse.u32Result;
}

uint32_t ADS::Ads::ReadWrite(uint32_t u32IdxGrp, uint32_t u32IdxOffset, size_t RdLen, size_t WrLen, void* pWrData, sADS_RESP_READ_t* Response)
{
    sAMS_PACKET_t AmsSendPacket;
    sAMS_PACKET_t AmsReceivePacket;

    ADS_DEBUG_PRINTLN("ADS ReadWrite");

    memset(Response, 0, sizeof(sADS_RESP_READ_t));

    AmsSendPacket.TargetAmsNetId = this->pAmsDestAddr->GetAmsAddr();
    AmsSendPacket.SourceAmsNetId = this->pAmsSrcAddr->GetAmsAddr();

    AmsSendPacket.u16CommandId = ADSSRVID_READWRITE;
    AmsSendPacket.u16StateFlags = STATE_FLAG_MASK_ADS_CMD;
    AmsSendPacket.u32Length = (sizeof(sADS_REQ_READ_WRITE_t) - ADS_MAX_DATA_SIZE) + WrLen;
    AmsSendPacket.u32ErrorCode = 0;
    AmsSendPacket.u32InvokeId = u32InvokeId++;

    AmsSendPacket.ReadWriteRequest.u32IndexGroup = u32IdxGrp;
    AmsSendPacket.ReadWriteRequest.u32IndexOffset = u32IdxOffset;
    AmsSendPacket.ReadWriteRequest.u32ReadLength = RdLen;
    AmsSendPacket.ReadWriteRequest.u32WriteLength = WrLen;

    memcpy(AmsSendPacket.ReadWriteRequest.Data, pWrData, WrLen);

    AmsSendPacket.TmsTcpHeader.reserved = 0;
    AmsSendPacket.TmsTcpHeader.u32Length = SIZEOF_AMS_HEADER + (sizeof(sADS_REQ_READ_WRITE_t) - ADS_MAX_DATA_SIZE) + WrLen;

    // Write Read Request
    if (client.write((uint8_t*)&AmsSendPacket, (size_t)(AmsSendPacket.TmsTcpHeader.u32Length + sizeof(sAMS_TCP_HEADER_t))) <= 0)
        ADS_DEBUG_PRINTLN("AdsReadWrite: no bytes send");

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
        if (millis() - timeout > 5000)
        {
            ADS_DEBUG_PRINTLN(">>> AdsReadWrite: Client Timeout !");
            ADS_DEBUG_PRINTLN(">>> Check your ADS router settings and your SrcNetId and DestNetId");
            client.stop();
            return ADSERR_DEVICE_TIMEOUT;
        }
    }

    // Read AmsResponse
    if ((client.read((uint8_t*)&AmsReceivePacket, sizeof(AmsReceivePacket))) <= 0)
        ADS_DEBUG_PRINTLN("AdsReadWrite: ERROR reading from socket");

    memcpy(Response, &AmsReceivePacket.ReadResponse, sizeof(sADS_RESP_READ_t));

    return AmsReceivePacket.ReadWriteResponse.u32Result;
}

uint32_t ADS::Ads::GetVaraibleHandleByName(std::string VarName, ADS::HANDLE &Handle)
{
    sADS_RESP_READ_t ReadResponse;
    uint32_t u32AdsRetVal;

    this->ReadWrite(ADSIGRP_SYM_HNDBYNAME, 0, sizeof(ADS::HANDLE), VarName.size(), (void*)VarName.c_str(), &ReadResponse);
    u32AdsRetVal = ReadResponse.u32Result;
    memcpy(&Handle, ReadResponse.Data, sizeof(ADS::HANDLE));

    return u32AdsRetVal;
}

uint32_t ADS::Ads::WritePlcVarByName(std::string VarName, void* pWrData, size_t WrLen)
{
    sADS_RESP_READ_t ReadResponse;
    ADS::HANDLE Handle;
    uint32_t u32AdsRetVal;

    ADS_DEBUG_PRINTLN("ADS WritePlcVarByName");

    u32AdsRetVal = this->GetVaraibleHandleByName(VarName, Handle);
    if (u32AdsRetVal)
        return u32AdsRetVal;

    // Write Var
    // ----------------------------------------------------
    u32AdsRetVal = this->Write(ADSIGRP_SYM_VALBYHND, Handle, WrLen, pWrData);

    return u32AdsRetVal;
}

uint32_t ADS::Ads::ReadPlcVarByName(std::string VarName, void* pRdData, size_t RdLen)
{
    sADS_RESP_READ_t ReadResponse;
    ADS::HANDLE Handle;
    uint32_t u32AdsRetVal;

    ADS_DEBUG_PRINTLN("ADS ReadPlcVarByName");

    u32AdsRetVal = this->GetVaraibleHandleByName(VarName, Handle);
    if (u32AdsRetVal)
        return u32AdsRetVal;

    // Read Var
    u32AdsRetVal = this->Read(ADSIGRP_SYM_VALBYHND, Handle, RdLen, &ReadResponse);

    memcpy(pRdData, ReadResponse.Data, RdLen);

    return u32AdsRetVal;
}

uint32_t ADS::Ads::ReadCoe(uint16_t u16Index, uint8_t u8Subindex, size_t RdLen, void* pRdData)
{
    return this->ReadCoe(u16Index, u8Subindex, false, RdLen, pRdData);
}

uint32_t ADS::Ads::ReadCoe(uint16_t u16Index, uint8_t u8Subindex, bool bCompleteAccess, size_t RdLen, void* pRdData)
{
    sADS_RESP_READ_t ReadResponse;
    uint32_t u32AdsRetVal;

    uint32_t u32IdxOffset = u16Index << 16 | u8Subindex;
    if (bCompleteAccess)
    {
        u32IdxOffset |= 0x100;
        if (u8Subindex > 1) // only 0 and 1 allowed for CA
            return ADSERR_DEVICE_INVALIDPARM;
    }

    u32AdsRetVal = this->Read(IDX_GRP_RW_COE, u32IdxOffset, RdLen, &ReadResponse);

    memcpy(pRdData, ReadResponse.Data, RdLen);

    return u32AdsRetVal;
}

uint32_t ADS::Ads::WriteCoe(uint16_t u16Index, uint8_t u8Subindex, bool bCompleteAccess, size_t WrLen, void* pWrData)
{
    uint32_t u32IdxOffset = u16Index << 16 | u8Subindex;
    if (bCompleteAccess)
    {
        u32IdxOffset |= 0x100;
        if (u8Subindex > 1) // only 0 and 1 allowed for CA
            return ADSERR_DEVICE_INVALIDPARM;
    }

    return this->Write(IDX_GRP_RW_COE, u32IdxOffset, WrLen, pWrData);
}

uint32_t ADS::Ads::WriteCoe(uint16_t u16Index, uint8_t u8Subindex, size_t WrLen, void* pWrData)
{
    return this->WriteCoe(u16Index, u8Subindex, false, WrLen, pWrData);
}

// completely untested!!!
uint32_t ADS::Ads::AddDeviceNotification(int32_t u32IdxGrp, uint32_t u32IdxOffset, uint32_t u32Len, eTransMode TransMode, uint32_t u32MaxDelay, uint32_t u32CycleTime, ADS::HANDLE &Handle)
{
    sADS_REQ_ADD_NOTIFICATION_t AddNoti;
    sADS_RESP_READ_t ReadResponse;
    uint32_t u32AdsRetVal;

    AddNoti.u32Length     = u32Len;
    AddNoti.u32TransMode  = TransMode;
    AddNoti.u32MaxDelay   = u32MaxDelay;
    AddNoti.u32CycleTime  = u32CycleTime;

    this->ReadWrite(u32IdxGrp, u32IdxOffset, sizeof(ADS::HANDLE), sizeof(AddNoti), (void*)&AddNoti, &ReadResponse);
    u32AdsRetVal = ReadResponse.u32Result;
    memcpy(&Handle, ReadResponse.Data, sizeof(ADS::HANDLE));

    return u32AdsRetVal;
}

// completely untested!!!
uint32_t ADS::Ads::DeleteDeviceNotification(int32_t u32IdxGrp, uint32_t u32IdxOffset, ADS::HANDLE Handle)
{
    this->Write(u32IdxGrp, u32IdxOffset, sizeof(ADS::HANDLE), (void*)&Handle);
}