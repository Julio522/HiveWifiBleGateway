// Fill in  your WiFi networks SSID and password
#define SECRET_SSID "SETUP-F958"
#define SECRET_PASS "class8133crumbs"

#define DEVICE_NAME "HiveWifiGateway1004"
#define TIMEZONE "America/Los_Angeles"

// Provide official timezone names
// https://en.wikipedia.org/wiki/List_of_tz_database_time_zones

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "a1z0b41nupaw6g-ats.iot.us-west-1.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(
-----BEGIN CERTIFICATE-----
MIIC9zCCAd+gAwIBAgIUR1G05oCG7DXS8ekftTYKCuEGkfAwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDYwODA1NTcz
NFoXDTQ5MTIzMTIzNTk1OVowgYYxCzAJBgNVBAYTAlVTMQ8wDQYDVQQIEwZOZXZh
ZGExEjAQBgNVBAcTCUxhcyBWZWdhczEVMBMGA1UEChMMSGl2ZSBtZWRpY2FsMR0w
GwYDVQQLExRTb2Z0d2FyZSBFbmdpbmVlcmluZzEcMBoGA1UEAxMTSGl2ZVdpZmlH
YXRld2F5MTAwMTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABMxTuBjKhjruTVou
mg+MBKau8+L3JUOran3g5pMoy/PCHHtxmkxF3gqOHN5ZTyxr4w0A1KWXTQMneaPi
9F1vc0ajYDBeMB8GA1UdIwQYMBaAFGFtoYpurU8Q6EAcULvWM2FzUnXrMB0GA1Ud
DgQWBBRcsaue+sDOf5c7AO9fo7lq7aM8gDAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB
/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAR3B8RpLNeiEw2/rwn3COcW4Jt49U
ulg4gl2r195Hc+skRcTOoma1BbkFCmLTZCmL9/tT2IC+rdf/WAeAkhImnEWRXdEa
ghlJBLUEjnuh6XT2fxzrPDkklp3DTZ1j+fyXppyWmXN5IkCa2lSMAOXf2ZQ3SoWy
It60wfWtaqcDXjPUmyTPAQAEKBHCWeB44Yob7jRJ7Ge2ivLfkvL1T+kRgbNaTIkG
lLY8ANilOOyIZt4SxRRXhG+I40mbwP/ojvYFjC1g8lK2YVnBoRNK0bsnYFCPnId/
1XjqA2otqvGOSKu+eKH/vRTze25oANuyx7by+aN90nzDK9YIcfhsVniirQ==
-----END CERTIFICATE-----
)";
