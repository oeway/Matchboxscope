void initWifiAP(const char *ssid) {
  Serial.print("Network SSID (AP): ");
  Serial.println(ssid);

  WiFi.softAP(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}



void joinWifi(const char *ssid, const char *password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int nConnectTrials = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    nConnectTrials += 1;
    if (nConnectTrials > 10)
      ESP.restart();
    // we can even make the ESP32 to sleep
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        



void autoconnectWifi(){
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
    

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wm.resetSettings();
    wm.setHostname(hostname);
    //wm.setConfigPortalBlocking(false);
     wm.setConfigPortalTimeout(60); // auto close configportal after n seconds

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect(mSSIDAP); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        initWifiAP(mSSIDAP);
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...");
    }

}
