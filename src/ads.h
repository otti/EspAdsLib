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

enum class eTransMode : uint32_t
{
    None              = 0, // No AdsNotification event is fired.
    ClientCycle       = 1, // Client triggered cyclic AdsNotification event
    ClientOnChange    = 2, // The AdsNotification event is fired when data changes triggered by the client
    Cyclic            = 3, // The AdsNotification event is fired cyclically.
    OnChange          = 4, // The Notification will be registered on the ADS Server side for an on-change and optional cyclical trigger 
    CyclicInContext   = 5, // The AdsNotification event is fired cyclically within the given task context
    OnChangeInContext = 6  // The AdsNotification event is fired when the data changes within the given task context
};

typedef struct __attribute__((__packed__)) 
{
   uint32_t   u32Length;     // Length of data in bytes, which should be sent per notification.
   eTransMode u32TransMode;
   uint32_t   u32MaxDelay;	  // At the latest after this time, the ADS Device Notification is called. The unit is 1ms.
   uint32_t   u32CycleTime;  // The ADS server checks if the value changes in this time slice. The unit is 1ms
}sADS_REQ_ADD_NOTIFICATION_t;

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
