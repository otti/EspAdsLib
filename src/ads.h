#ifndef _ADS_H_
#define _ADS_H_

#ifndef ADS_MAX_DATA_SIZE
#define ADS_MAX_DATA_SIZE           64 // This is the maximum payload size of an ADS message in byte
#endif

#define SIZEOF_AMS_TCP_HEADER       6
#define SIZEOF_AMS_HEADER           32

#define IDX_GRP_RW_COE              0xF302
#define IDX_GRP_RW_PLC_VAR_BY_NAME  0xF004

typedef struct __attribute__((__packed__)) 
{
    uint8_t b[6];
}sAmsNetId_t;

typedef struct __attribute__((__packed__)) 
{
    sAmsNetId_t netId;
    uint16_t    port;
}sAmsAddr_t;

typedef struct __attribute__((__packed__)) 
{
   uint16_t  reserved;
   uint32_t u32Length;
}sAMS_TCP_HEADER_t;

typedef struct __attribute__((__packed__)) 
{
   uint32_t u32Result;
   uint8_t  u8MajorVersion;
   uint8_t  u8MinorVersion;
   uint16_t u16VersionBuild;
   uint8_t  DeviceName[16];
}sADS_RESP_DEVICE_INFO_t;

typedef struct  __attribute__((__packed__)) 
{
   uint32_t u32IndexGroup;
   uint32_t u32IndexOffset;
   uint32_t u32Length;
}sADS_REQ_READ_t;

typedef struct  __attribute__((__packed__)) 
{
   uint32_t u32Result;
   uint32_t u32Length;
   uint8_t  Data[ADS_MAX_DATA_SIZE];
}sADS_RESP_READ_t;

#define sADS_RESP_RW_t sADS_RESP_READ_t

typedef struct  __attribute__((__packed__)) 
{
   uint32_t u32IndexGroup;
   uint32_t u32IndexOffset;
   uint32_t u32Length;
   uint8_t  Data[ADS_MAX_DATA_SIZE];
}sADS_REQ_WRITE_t;

typedef struct  __attribute__((__packed__)) 
{
   uint32_t u32IndexGroup;
   uint32_t u32IndexOffset;
   uint32_t u32ReadLength;
   uint32_t u32WriteLength;
   uint8_t  Data[ADS_MAX_DATA_SIZE];
}sADS_REQ_READ_WRITE_t;

typedef struct __attribute__((__packed__)) 
{
   sAMS_TCP_HEADER_t TmsTcpHeader;
   sAmsAddr_t        TargetAmsNetId;
   sAmsAddr_t        SourceAmsNetId;
   uint16_t          u16CommandId;
   uint16_t          u16StateFlags;
   uint32_t          u32Length;
   uint32_t          u32ErrorCode;
   uint32_t          u32InvokeId;
   union{
     sADS_REQ_READ_WRITE_t   ReadWriteRequest;
     sADS_REQ_READ_t         ReadRequest;
     sADS_REQ_WRITE_t        WriteRequest;
     sADS_RESP_READ_t        ReadResponse;
     sADS_RESP_RW_t          ReadWriteResponse;
     sADS_RESP_DEVICE_INFO_t DevInfoResponse;
     uint32_t                u32WrResponse;
   };
}sAMS_PACKET_t;


enum ADSTRANSMODE {
    ADSTRANS_NOTRANS      = 0,
    ADSTRANS_CLIENTCYCLE  = 1,
    ADSTRANS_CLIENTONCHA  = 2,
    ADSTRANS_SERVERCYCLE  = 3,
    ADSTRANS_SERVERONCHA  = 4,
    ADSTRANS_SERVERCYCLE2 = 5,
    ADSTRANS_SERVERONCHA2 = 6,
    ADSTRANS_CLIENT1REQ   = 10,
    ADSTRANS_MAXMODES
};

enum ADSSTATE {
    ADSSTATE_INVALID      = 0,
    ADSSTATE_IDLE         = 1,
    ADSSTATE_RESET        = 2,
    ADSSTATE_INIT         = 3,
    ADSSTATE_START        = 4,
    ADSSTATE_RUN          = 5,
    ADSSTATE_STOP         = 6,
    ADSSTATE_SAVECFG      = 7,
    ADSSTATE_LOADCFG      = 8,
    ADSSTATE_POWERFAILURE = 9,
    ADSSTATE_POWERGOOD    = 10,
    ADSSTATE_ERROR        = 11,
    ADSSTATE_SHUTDOWN     = 12,
    ADSSTATE_SUSPEND      = 13,
    ADSSTATE_RESUME       = 14,
    ADSSTATE_CONFIG       = 15,
    ADSSTATE_RECONFIG     = 16,
    ADSSTATE_STOPPING     = 17,
    ADSSTATE_INCOMPATIBLE = 18,
    ADSSTATE_EXCEPTION    = 19,
    ADSSTATE_MAXSTATES
};

#endif // _ADS_H_
