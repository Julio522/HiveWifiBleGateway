// Fill in  your WiFi networks SSID and password
#define SECRET_SSID "SETUP-F958"
#define SECRET_PASS "class8133crumbs"

#define DEVICE_NAME "HiveWifiGateway1003"
#define TIMEZONE "America/Los_Angeles"

// Provide official timezone names
// https://en.wikipedia.org/wiki/List_of_tz_database_time_zones

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "a1z0b41nupaw6g-ats.iot.us-west-1.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(-----BEGIN CERTIFICATE-----
MIIC7DCCAdSgAwIBAgIUPpdizW8Syftv0zx8Yh1EGfjhvOowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDYxMDE0MTEy
M1oXDTQ5MTIzMTIzNTk1OVowfDELMAkGA1UEBhMCVVMxDzANBgNVBAgTBk5ldmFk
YTESMBAGA1UEBxMJTGFzIFZlZ2FzMRQwEgYDVQQKEwtIaXZlTWVkaWNhbDEUMBIG
A1UECxMLRW5naW5lZXJpbmcxHDAaBgNVBAMTE0hpdmVXaWZpR2F0ZXdheTEwMDMw
WTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARjlwA6DmkhlKuRY5lV1Tu/HrzOqM2o
USItFuOWNLm/bv75iQXOxVnRXSGZAVtqUyyvoOhBkdkrTZenUHpVlVsco2AwXjAf
BgNVHSMEGDAWgBRgoMpQGEp8o/3y6PCohqjisSs/gTAdBgNVHQ4EFgQUY2RRaYS2
YqRmKVjyVoH/hvvRUCIwDAYDVR0TAQH/BAIwADAOBgNVHQ8BAf8EBAMCB4AwDQYJ
KoZIhvcNAQELBQADggEBAMDBsxJtiNJN0uR/tssvmv+0OzhbNsOUPg/vYB1KZ5Qs
DYLQnVvUAGf0GXtYEOpt8IKrYZe7kjM/OTu30HwlE5BOfz6L5Bb1ce0d1us2S83K
MavXjPx8Dt+HR0nOi+26bhAVCS6wnBPmI7QTWdshVSJ5bwKVTe8K6R79NQgk7o1s
h9bPBoOgP/pGTT49vB3yo1vf4Ht8Ro3HcuApaPNq1T9t6UHwyadX+9YCAM+ywjdz
ArIylRjqn4grPc0ORr5ZnOEZjfMXq18AG4KjXbzyhfLOGgw7aMWZjtM9H+pVPs71
oJoYZajq50rpRMvC+OnQ3itK0b9ddlhKP7AvbpEGZiI=
-----END CERTIFICATE-----)";
