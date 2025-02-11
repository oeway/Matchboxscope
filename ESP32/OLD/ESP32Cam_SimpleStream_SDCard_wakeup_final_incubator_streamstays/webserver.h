#pragma once

// C++ standard libraries
#include <functional>

// ESP32 vendor libraries
#include <WebServer.h>
#include <FS.h>

// Local header file
//#include "camera.h"
#include "illumination.h"

#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_camera.h"
#include "img_converters.h"
#include "Arduino.h"

typedef struct {
  httpd_req_t *req;
  size_t len;
} jpg_chunking_t;

#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";


class RefocusingServer {
  public:
    explicit RefocusingServer(int port, FS &fs, Camera &camera, std::function<void(void)> on_enable) :
      server(port), fs(fs), camera(camera), on_enable(on_enable) {}

    void init();
    void serve();

  private:
    WebServer server;
    FS &fs;
    Camera &camera;
    std::function<void(void)> on_enable;

    // Route handlers
    void handleIndex();
    void handleBootstrapMin();
    void handleBootstrapAll();
    void handleBmp();
    void handleJpgLo();
    void handleJpgHi();
    void handleJpg();
    void handleMjpeg();
    void handleEnable();

    // Utilities
    void addHandler(const char *uri, WebServer::THandlerFunction fn);
    void serveJpg();
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
