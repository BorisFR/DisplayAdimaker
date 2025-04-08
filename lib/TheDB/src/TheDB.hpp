#ifndef THE_DB_HPP
#define THE_DB_HPP

#include "../../../src/CONFIG.hpp"
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

class TheDB
{
public:
    TheDB();
    void setup();
    void loop();
    bool ready();
    void requestData(String value);
    String getData();
    bool requestInProgress();
    bool dataAvailable();

private:
    WiFiClientSecure ssl_client;
    FirebaseApp app;
    RealtimeDatabase Database;
    AsyncResult databaseResult;
    bool taskComplete = false;
    bool dataReady;
    String data;
    bool requestRunning;

    using AsyncClient = AsyncClientClass;
    // AsyncClient aClient(ssl_client);
    AsyncClient aClient;
    // UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD, 3000 /* expire period in seconds (<3600) */);
    UserAuth user_auth;

    static void auth_debug_print(AsyncResult &aResult);
    void set_ssl_client_insecure_and_buffer(WiFiClientSecure &client);
    static void print_token_type(FirebaseApp &app);
};

#endif