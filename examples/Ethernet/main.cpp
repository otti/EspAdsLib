#include <ETH.h>
#include <EspAdsLib.h>

// The SrcAmsAddr can be set here. But we will change it to the current
// IP with the function SrcAmsAddr.Change() in the setup() function
ADS::AmsAddr SrcAmsAddr((char*)"1.1.1.1.1.1", 43609);  // Dummy

// Set AMS Addr of the TwinCAT machine here
ADS::AmsAddr DestAmsAddr((char*)"5.16.3.178.1.1", AMSPORT_R0_PLC_TC3);
ADS::Ads Ads;

// Set IP/Name of your PLC
char IpOfPlc[] = "192.168.0.42";

// Set ethernet phy configuration for your board
#define ETH_ADDR                  1
#define ETH_RESET                 12
#define ETH_MDC_PIN               23
#define ETH_MDIO_PIN              18
#define ETH_TYPE                  ETH_PHY_LAN8720
#define ETH_CLOCK_MODE            ETH_CLOCK_GPIO17_OUT

void setup()
{
  String PlcIp;
  String Ip;

  // Serial
  Serial.begin(115200);
  Serial.println("Starting up ...");

  // Ethernet
  ETH.begin(ETH_ADDR, ETH_RESET, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLOCK_MODE);
  ETH.setHostname("Hostname: ESP_ADS");
  //ETH.config(local_ip, gateway, subnet, dns1, dns2); // Static IP, leave without this line to get IP via DHCP
  while(!((uint32_t)ETH.localIP())){}; // Waiting for IP from DHCP

  Ip = ETH.localIP().toString();
  Serial.println("IP: " + Ip);

  Ip = Ip + ".1.1";
  SrcAmsAddr.Change((char*)Ip.c_str(), 43609);
  Serial.println("SrcAmsAdr: " + Ip);

  Ads.SetAddr(&SrcAmsAddr, &DestAmsAddr, IpOfPlc);
  Ads.Connect();
  Serial.println("ADS connected");
}


uint16_t u16MyVar = 0;
void loop()
{
  Serial.println("Write PLC variable: " + String(u16MyVar));
  Ads.WritePlcVarByName("Main.u16MyVar", &u16MyVar, sizeof(uint16_t));

  Ads.ReadPlcVarByName("Main.u16MyVar", &u16MyVar, sizeof(uint16_t));
  Serial.println("Read  PLC variable: " + String(u16MyVar));

  u16MyVar++;
  delay(2000);
}