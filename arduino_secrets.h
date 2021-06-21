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
const char SECRET_CERTIFICATE[] = R"(-----BEGIN CERTIFICATE-----
MIIC7jCCAdagAwIBAgIVAP22ZUek+S/XS1ZVfvrLw/a+hbD1MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTA2MTAxMzMx
NTZaFw00OTEyMzEyMzU5NTlaMH0xCzAJBgNVBAYTAlVTMQ8wDQYDVQQIEwZOZXZh
ZGExEjAQBgNVBAcTCUxhcyBWZWdhczEVMBMGA1UEChMMSGl2ZSBNZWRpY2FsMRQw
EgYDVQQLEwtFbmdpbmVlcmluZzEcMBoGA1UEAxMTSGl2ZVdpZmlHYXRld2F5MTAw
MjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABFf0p0gkFPhhn3EQx92ErxdO679v
4vhy33pD986zYBsij7N7yxkql7mWP/104CBkluC9eV5zcsqJ0Er8EhU7+H+jYDBe
MB8GA1UdIwQYMBaAFGCgylAYSnyj/fLo8KiGqOKxKz+BMB0GA1UdDgQWBBRYLPXg
UQ4tUfOhKx/YNDeN5qYm4DAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDAN
BgkqhkiG9w0BAQsFAAOCAQEAK/bvcYi18JUxz1vrx6S/P2XTVpDpjVwVi6MWIhoA
ot4uAnF96OEhmkAZ+Nl4lEXeTi0gLSuR4S3YrwYKWDdAHGqPfIy8wK4h+oUL35zE
y4VomrjVo6Ty3D8MAnGDXjtdpcYrjsX3MqeDAADopXU7pavsyb58MrUsZ/1s5H7n
gsZpjhBbPMy8vUqudHqJk1PUWk05y0UCtM29+1JRWanpLEQZXZaUNAzFJB94N0Hs
iVT/QKf3tMzPYiGED9hQZtlliui+UoHWU2KRsmZcFSgqJQVayZAvSdOq24VjP+xl
z9G5sj/yph2zNo1JGAuzMXfsXKDXjBIowGwm8JZvbRIaSQ==
-----END CERTIFICATE-----
)";
