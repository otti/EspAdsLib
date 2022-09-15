#include <EspAdsLib.h>
#include <WiFi.h>

ADS::AmsAddr SrcAmsAddr((char*)"192.168.0.124.1.1", 43609);
ADS::AmsAddr DestAmsAddr((char*)"5.35.2.16.1.1", AMSPORT_R0_PLC_TC3);
char DestIpAddr[] = "192.168.0.45"; // IP of the TwinCAT target machine

ADS::Ads Ads(&SrcAmsAddr, &DestAmsAddr, DestIpAddr);

char ssid[] = "<MY SSID>";
char password[] = "<MY PASSWORD>";

void setup()
{
    uint16_t u16PlcWrData = 1234;
    uint16_t u16PlcRdData;

    uint16_t u16CoeWrData = 12;
    uint16_t u16CoeRdData;

    uint8_t au8Data[32];

    Serial.begin(115200);
    delay(1000);
    SrcAmsAddr.PrintInfo();

    WifiConnect();

    Ads.Connect();

    // Write the PLC variable 'Main.u16MyVar' to u16PlcWrData (1234)
    Ads.WritePlcVarByName("Main.u16MyVar", &u16PlcWrData, sizeof(uint16_t));

    // Read back the PLC variable 'Main.u16MyVar' to u16PlcRdData
    Ads.ReadPlcVarByName((char*)"Main.u16MyVar", &u16PlcRdData, sizeof(uint16_t));
    Serial.println("PlcRdData: " + String(u16PlcRdData));

    // Read write CoE
    // We have to change the DestAmsAddr and port to the address and port of the EtherCAT slave we want to access
    DestAmsAddr.Change((char*)"5.35.2.16.4.1", 1002);

    Ads.WriteCoe(0x8000, 0x1A, 2, &u16CoeWrData);
    Ads.ReadCoe(0x8000, 0x1A, 2, &u16CoeRdData);
    Serial.println("CoeRdData: " + String(u16CoeRdData));

    Ads.Disconnect();
}

bool WifiConnect(void)
{
    int i = 0;
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        if (++i > 40) // cancel after 40 * 250 ms
        {
          Serial.print("WiFi connection failed ...");
          Serial.print("Restsrting ESP ...");
          ESP.restart();
        }

        delay(250);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    return 1;
}

int state = 0;

void loop()
{
}