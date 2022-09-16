/** @file
   Copyright (c) 2015 - 2016 Beckhoff Automation GmbH & Co. KG

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#ifndef __ADSDEF_H__
#define __ADSDEF_H__

#define ADS_TCP_SERVER_PORT 0xBF02


#define STATE_FLAG_MASK_RESPONSE       0x0001
#define STATE_FLAG_MASK_ADS_CMD        0x0004

////////////////////////////////////////////////////////////////////////////////
// AMS Ports
#define AMSPORT_LOGGER                  100
#define AMSPORT_R0_RTIME                200
#define AMSPORT_R0_TRACE                (AMSPORT_R0_RTIME + 90)
#define AMSPORT_R0_IO                   300
#define AMSPORT_R0_SPS                  400
#define AMSPORT_R0_NC                   500
#define AMSPORT_R0_ISG                  550
#define AMSPORT_R0_PCS                  600
#define AMSPORT_R0_PLC                  801
#define AMSPORT_R0_PLC_RTS1             801
#define AMSPORT_R0_PLC_RTS2             811
#define AMSPORT_R0_PLC_RTS3             821
#define AMSPORT_R0_PLC_RTS4             831
#define AMSPORT_R0_PLC_TC3              851

////////////////////////////////////////////////////////////////////////////////
// ADS Cmd Ids
#define ADSSRVID_INVALID                    0x00
#define ADSSRVID_READDEVICEINFO             0x01
#define ADSSRVID_READ                       0x02
#define ADSSRVID_WRITE                      0x03
#define ADSSRVID_READSTATE                  0x04
#define ADSSRVID_WRITECTRL                  0x05
#define ADSSRVID_ADDDEVICENOTE              0x06
#define ADSSRVID_DELDEVICENOTE              0x07
#define ADSSRVID_DEVICENOTE                 0x08
#define ADSSRVID_READWRITE                  0x09

////////////////////////////////////////////////////////////////////////////////
// ADS reserved index groups
#define ADSIGRP_SYMTAB                      0xF000
#define ADSIGRP_SYMNAME                     0xF001
#define ADSIGRP_SYMVAL                      0xF002

#define ADSIGRP_SYM_HNDBYNAME               0xF003
#define ADSIGRP_SYM_VALBYNAME               0xF004
#define ADSIGRP_SYM_VALBYHND                0xF005
#define ADSIGRP_SYM_RELEASEHND              0xF006
#define ADSIGRP_SYM_INFOBYNAME              0xF007
#define ADSIGRP_SYM_VERSION                 0xF008
#define ADSIGRP_SYM_INFOBYNAMEEX            0xF009

#define ADSIGRP_SYM_DOWNLOAD                0xF00A
#define ADSIGRP_SYM_UPLOAD                  0xF00B
#define ADSIGRP_SYM_UPLOADINFO              0xF00C
#define ADSIGRP_SYM_DOWNLOAD2               0xF00D
#define ADSIGRP_SYM_DT_UPLOAD               0xF00E
#define ADSIGRP_SYM_UPLOADINFO2             0xF00F

#define ADSIGRP_SYMNOTE                     0xF010      /**< notification of named handle */

/**
 * AdsRW  IOffs list size or 0 (=0 -> list size == WLength/3*sizeof(ULONG))
 * @param W: {list of IGrp, IOffs, Length}
 * @param R: if IOffs != 0 then {list of results} and {list of data}
 * @param R: if IOffs == 0 then only data (sum result)
 */
#define ADSIGRP_SUMUP_READ                  0xF080

/**
 * AdsRW  IOffs list size
 * @param W: {list of IGrp, IOffs, Length} followed by {list of data}
 * @param R: list of results
 */
#define ADSIGRP_SUMUP_WRITE                 0xF081

/**
 * AdsRW  IOffs list size
 * @param W: {list of IGrp, IOffs, RLength, WLength} followed by {list of data}
 * @param R: {list of results, RLength} followed by {list of data}
 */
#define ADSIGRP_SUMUP_READWRITE             0xF082

/**
 * AdsRW  IOffs list size
 * @param W: {list of IGrp, IOffs, Length}
 */
#define ADSIGRP_SUMUP_READEX                0xF083

/**
 * AdsRW  IOffs list size
 * @param W: {list of IGrp, IOffs, Length}
 * @param R: {list of results, Length} followed by {list of data (returned lengths)}
 */
#define ADSIGRP_SUMUP_READEX2               0xF084

/**
 * AdsRW  IOffs list size
 * @param W: {list of IGrp, IOffs, Attrib}
 * @param R: {list of results, handles}
 */
#define ADSIGRP_SUMUP_ADDDEVNOTE            0xF085

/**
 * AdsRW  IOffs list size
 * @param W: {list of handles}
 * @param R: {list of results, Length} followed by {list of data}
 */
#define ADSIGRP_SUMUP_DELDEVNOTE            0xF086

#define ADSIGRP_IOIMAGE_RWIB                0xF020      /**< read/write input byte(s) */
#define ADSIGRP_IOIMAGE_RWIX                0xF021      /**< read/write input bit */
#define ADSIGRP_IOIMAGE_RISIZE              0xF025      /**< read input size (in byte) */
#define ADSIGRP_IOIMAGE_RWOB                0xF030      /**< read/write output byte(s) */
#define ADSIGRP_IOIMAGE_RWOX                0xF031      /**< read/write output bit */
#define ADSIGRP_IOIMAGE_ROSIZE              0xF035      /**< read output size (in byte) */
#define ADSIGRP_IOIMAGE_CLEARI              0xF040      /**< write inputs to null */
#define ADSIGRP_IOIMAGE_CLEARO              0xF050      /**< write outputs to null */
#define ADSIGRP_IOIMAGE_RWIOB               0xF060      /**< read input and write output byte(s) */

#define ADSIGRP_DEVICE_DATA                 0xF100      /**< state, name, etc... */
#define ADSIOFFS_DEVDATA_ADSSTATE           0x0000      /**< ads state of device */
#define ADSIOFFS_DEVDATA_DEVSTATE           0x0002      /**< device state */

////////////////////////////////////////////////////////////////////////////////
// Global Return codes
#define ERR_GLOBAL                          0x0000

#define GLOBALERR_TARGET_PORT               (0x06 + ERR_GLOBAL) /**< target port not found, possibly the ADS Server is not started */
#define GLOBALERR_MISSING_ROUTE             (0x07 + ERR_GLOBAL) /**< target machine not found, possibly missing ADS routes */
#define GLOBALERR_NO_MEMORY                 (0x19 + ERR_GLOBAL) /**< No memory */
#define GLOBALERR_TCP_SEND                  (0x1A + ERR_GLOBAL) /**< TCP send error */

////////////////////////////////////////////////////////////////////////////////
// Router Return codes
#define ERR_ROUTER                          0x0500

#define ROUTERERR_NOTREGISTERED             (0x07 + ERR_ROUTER) /**< Port not registered */
#define ROUTERERR_NOMOREQUEUES              (0x08 + ERR_ROUTER) /**< The maximum number of Ports reached */

////////////////////////////////////////////////////////////////////////////////
// ADS Return codes
#define ADSERR_NOERROR               0x00 // No error.
#define ADSERR_INTERNAL              0x01 // Internal error.
#define ADSERR_NORTIME               0x02 // No real-time.
#define ADSERR_ALLOCLOCKEDMEM        0x03 // Allocation locked – memory error.
#define ADSERR_INSERTMAILBOX         0x04 // Mailbox full – the ADS message could not be sent. Reducing the number of ADS messages per cycle will help.
#define ADSERR_WRONGRECEIVEHMSG      0x05 // Wrong HMSG.
#define ADSERR_TARGETPORTNOTFOUND    0x06 // Target port not found – ADS server is not started or is not reachable.
#define ADSERR_TARGETMACHINENOTFOUND 0x07 // Target computer not found – AMS route was not found.
#define ADSERR_UNKNOWNCMDID          0x08 // Unknown command ID.
#define ADSERR_BADTASKID             0x09 // Invalid task ID.
#define ADSERR_NOIO                  0x0A // No IO.
#define ADSERR_UNKNOWNAMSCMD         0x0B // Unknown AMS command.
#define ADSERR_WIN32ERROR            0x0C // Win32 error.
#define ADSERR_PORTNOTCONNECTED      0x0D // Port not connected.
#define ADSERR_INVALIDAMSLENGTH      0x0E // Invalid AMS length.
#define ADSERR_INVALIDAMSNETID       0x0F // Invalid AMS Net ID.
#define ADSERR_LOWINSTLEVEL          0x10 // Installation level is too low –TwinCAT 2 license error.
#define ADSERR_NODEBUGINTAVAILABLE   0x11 // No debugging available.
#define ADSERR_PORTDISABLED          0x12 // Port disabled – TwinCAT system service not started.
#define ADSERR_PORTALREADYCONNECTED  0x13 // Port already connected.
#define ADSERR_AMSSYNC_W32ERROR      0x14 // AMS Sync Win32 error.
#define ADSERR_AMSSYNC_TIMEOUT       0x15 // AMS Sync Timeout.
#define ADSERR_AMSSYNC_AMSERROR      0x16 // AMS Sync error.
#define ADSERR_AMSSYNC_NOINDEXINMAP  0x17 // No index map for AMS Sync available.
#define ADSERR_INVALIDAMSPORT        0x18 // Invalid AMS port.
#define ADSERR_NOMEMORY              0x19 // No memory.
#define ADSERR_TCPSEND               0x1A // TCP send error.
#define ADSERR_HOSTUNREACHABLE       0x1B // Host unreachable.
#define ADSERR_INVALIDAMSFRAGMENT    0x1C // Invalid AMS fragment.
#define ADSERR_TLSSEND               0x1D // TLS send error – secure ADS connection failed.
#define ADSERR_ACCESSDENIED          0x1E // Access denied – secure ADS access denied.


#define ERR_ADSERRS                         0x0700

#define ADSERR_DEVICE_ERROR                 (0x00 + ERR_ADSERRS) /**< Error class < device error > */
#define ADSERR_DEVICE_SRVNOTSUPP            (0x01 + ERR_ADSERRS) /**< Service is not supported by server */
#define ADSERR_DEVICE_INVALIDGRP            (0x02 + ERR_ADSERRS) /**< invalid indexGroup */
#define ADSERR_DEVICE_INVALIDOFFSET         (0x03 + ERR_ADSERRS) /**< invalid indexOffset */
#define ADSERR_DEVICE_INVALIDACCESS         (0x04 + ERR_ADSERRS) /**< reading/writing not permitted */
#define ADSERR_DEVICE_INVALIDSIZE           (0x05 + ERR_ADSERRS) /**< parameter size not correct */
#define ADSERR_DEVICE_INVALIDDATA           (0x06 + ERR_ADSERRS) /**< invalid parameter value(s) */
#define ADSERR_DEVICE_NOTREADY              (0x07 + ERR_ADSERRS) /**< device is not in a ready state */
#define ADSERR_DEVICE_BUSY                  (0x08 + ERR_ADSERRS) /**< device is busy */
#define ADSERR_DEVICE_INVALIDCONTEXT        (0x09 + ERR_ADSERRS) /**< invalid context (must be InWindows) */
#define ADSERR_DEVICE_NOMEMORY              (0x0A + ERR_ADSERRS) /**< out of memory */
#define ADSERR_DEVICE_INVALIDPARM           (0x0B + ERR_ADSERRS) /**< invalid parameter value(s) */
#define ADSERR_DEVICE_NOTFOUND              (0x0C + ERR_ADSERRS) /**< not found (files, ...) */
#define ADSERR_DEVICE_SYNTAX                (0x0D + ERR_ADSERRS) /**< syntax error in comand or file */
#define ADSERR_DEVICE_INCOMPATIBLE          (0x0E + ERR_ADSERRS) /**< objects do not match */
#define ADSERR_DEVICE_EXISTS                (0x0F + ERR_ADSERRS) /**< object already exists */
#define ADSERR_DEVICE_SYMBOLNOTFOUND        (0x10 + ERR_ADSERRS) /**< symbol not found */
#define ADSERR_DEVICE_SYMBOLVERSIONINVALID  (0x11 + ERR_ADSERRS) /**< symbol version invalid, possibly caused by an 'onlinechange' -> try to release handle and get a new one */
#define ADSERR_DEVICE_INVALIDSTATE          (0x12 + ERR_ADSERRS) /**< server is in invalid state */
#define ADSERR_DEVICE_TRANSMODENOTSUPP      (0x13 + ERR_ADSERRS) /**< AdsTransMode not supported */
#define ADSERR_DEVICE_NOTIFYHNDINVALID      (0x14 + ERR_ADSERRS) /**< Notification handle is invalid, possibly caussed by an 'onlinechange' -> try to release handle and get a new one */
#define ADSERR_DEVICE_CLIENTUNKNOWN         (0x15 + ERR_ADSERRS) /**< Notification client not registered */
#define ADSERR_DEVICE_NOMOREHDLS            (0x16 + ERR_ADSERRS) /**< no more notification handles */
#define ADSERR_DEVICE_INVALIDWATCHSIZE      (0x17 + ERR_ADSERRS) /**< size for watch to big */
#define ADSERR_DEVICE_NOTINIT               (0x18 + ERR_ADSERRS) /**< device not initialized */
#define ADSERR_DEVICE_TIMEOUT               (0x19 + ERR_ADSERRS) /**< device has a timeout */
#define ADSERR_DEVICE_NOINTERFACE           (0x1A + ERR_ADSERRS) /**< query interface failed */
#define ADSERR_DEVICE_INVALIDINTERFACE      (0x1B + ERR_ADSERRS) /**< wrong interface required */
#define ADSERR_DEVICE_INVALIDCLSID          (0x1C + ERR_ADSERRS) /**< class ID is invalid */
#define ADSERR_DEVICE_INVALIDOBJID          (0x1D + ERR_ADSERRS) /**< object ID is invalid */
#define ADSERR_DEVICE_PENDING               (0x1E + ERR_ADSERRS) /**< request is pending */
#define ADSERR_DEVICE_ABORTED               (0x1F + ERR_ADSERRS) /**< request is aborted */
#define ADSERR_DEVICE_WARNING               (0x20 + ERR_ADSERRS) /**< signal warning */
#define ADSERR_DEVICE_INVALIDARRAYIDX       (0x21 + ERR_ADSERRS) /**< invalid array index */
#define ADSERR_DEVICE_SYMBOLNOTACTIVE       (0x22 + ERR_ADSERRS) /**< symbol not active, possibly caussed by an 'onlinechange' -> try to release handle and get a new one */
#define ADSERR_DEVICE_ACCESSDENIED          (0x23 + ERR_ADSERRS) /**< access denied */
#define ADSERR_DEVICE_LICENSENOTFOUND       (0x24 + ERR_ADSERRS) /**< no license found -> Activate license for TwinCAT 3 function*/
#define ADSERR_DEVICE_LICENSEEXPIRED        (0x25 + ERR_ADSERRS) /**< license expired */
#define ADSERR_DEVICE_LICENSEEXCEEDED       (0x26 + ERR_ADSERRS) /**< license exceeded */
#define ADSERR_DEVICE_LICENSEINVALID        (0x27 + ERR_ADSERRS) /**< license invalid */
#define ADSERR_DEVICE_LICENSESYSTEMID       (0x28 + ERR_ADSERRS) /**< license invalid system id */
#define ADSERR_DEVICE_LICENSENOTIMELIMIT    (0x29 + ERR_ADSERRS) /**< license not time limited */
#define ADSERR_DEVICE_LICENSEFUTUREISSUE    (0x2A + ERR_ADSERRS) /**< license issue time in the future */
#define ADSERR_DEVICE_LICENSETIMETOLONG     (0x2B + ERR_ADSERRS) /**< license time period to long */
#define ADSERR_DEVICE_EXCEPTION             (0x2C + ERR_ADSERRS) /**< exception in device specific code -> Check each device transistions */
#define ADSERR_DEVICE_LICENSEDUPLICATED     (0x2D + ERR_ADSERRS) /**< license file read twice */
#define ADSERR_DEVICE_SIGNATUREINVALID      (0x2E + ERR_ADSERRS) /**< invalid signature */
#define ADSERR_DEVICE_CERTIFICATEINVALID    (0x2F + ERR_ADSERRS) /**< public key certificate */

#define ADSERR_CLIENT_ERROR                 (0x40 + ERR_ADSERRS) /**< Error class < client error > */
#define ADSERR_CLIENT_INVALIDPARM           (0x41 + ERR_ADSERRS) /**< invalid parameter at service call */
#define ADSERR_CLIENT_LISTEMPTY             (0x42 + ERR_ADSERRS) /**< polling list is empty */
#define ADSERR_CLIENT_VARUSED               (0x43 + ERR_ADSERRS) /**< var connection already in use */
#define ADSERR_CLIENT_DUPLINVOKEID          (0x44 + ERR_ADSERRS) /**< invoke id in use */
#define ADSERR_CLIENT_SYNCTIMEOUT           (0x45 + ERR_ADSERRS) /**< timeout elapsed -> Check ADS routes of sender and receiver and your [firewall setting](http://infosys.beckhoff.com/content/1033/tcremoteaccess/html/tcremoteaccess_firewall.html?id=12027) */
#define ADSERR_CLIENT_W32ERROR              (0x46 + ERR_ADSERRS) /**< error in win32 subsystem */
#define ADSERR_CLIENT_TIMEOUTINVALID        (0x47 + ERR_ADSERRS) /**< Invalid client timeout value */
#define ADSERR_CLIENT_PORTNOTOPEN           (0x48 + ERR_ADSERRS) /**< ads dll */
#define ADSERR_CLIENT_NOAMSADDR             (0x49 + ERR_ADSERRS) /**< ads dll */
#define ADSERR_CLIENT_SYNCINTERNAL          (0x50 + ERR_ADSERRS) /**< internal error in ads sync */
#define ADSERR_CLIENT_ADDHASH               (0x51 + ERR_ADSERRS) /**< hash table overflow */
#define ADSERR_CLIENT_REMOVEHASH            (0x52 + ERR_ADSERRS) /**< key not found in hash table */
#define ADSERR_CLIENT_NOMORESYM             (0x53 + ERR_ADSERRS) /**< no more symbols in cache */
#define ADSERR_CLIENT_SYNCRESINVALID        (0x54 + ERR_ADSERRS) /**< invalid response received */
#define ADSERR_CLIENT_SYNCPORTLOCKED        (0x55 + ERR_ADSERRS) /**< sync port is locked */


#endif  // __ADSDEF_H__
