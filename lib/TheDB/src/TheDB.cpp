#include "TheDB.hpp"

TheDB::TheDB() : aClient(ssl_client), user_auth(DB_API_KEY, DB_USER_EMAIL, DB_USER_PASSWORD, 3000)
{
}

void TheDB::setup()
{
    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);
    set_ssl_client_insecure_and_buffer(ssl_client);
    Serial.println("Initializing app...");
    initializeApp(aClient, app, getAuth(user_auth), auth_debug_print, "🔐 authTask");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DB_DATABASE_URL);
    dataReady = false;
    data = "";
    requestRunning = false;
}

void TheDB::loop()
{
    app.loop();
}

bool TheDB::ready()
{
    return app.ready();
}

// Set some SSL client for skipping server certificate verification.
void TheDB::set_ssl_client_insecure_and_buffer(WiFiClientSecure &client)
{
    client.setInsecure();
}

// Debug information printing
void TheDB::auth_debug_print(AsyncResult &aResult)
{
    if (aResult.isEvent())
    {
        Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.eventLog().message().c_str(), aResult.eventLog().code());
    }

    if (aResult.isDebug())
    {
        Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
    }

    if (aResult.isError())
    {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
    }
}

// Token type information printing
void TheDB::print_token_type(FirebaseApp &app)
{
    Firebase.printf("Auth Token: %s\n", app.getToken().c_str());
    firebase_token_type type = app.getTokenType();
    if (type == token_type_access)
        Serial.println("Type: access token");
    else if (type == token_type_id)
        Serial.println("Type: ID token");
    else if (type == token_type_legacy)
        Serial.println("Type: legacy token");
    else if (type == token_type_no)
        Serial.println("Type: no token");
}

void TheDB::requestData(String value)
{
    if (requestRunning)
        return;
    dataReady = false;
    data = "";
    if (!app.ready())
    {
        Serial.println("/!\\ Database not ready");
        return;
    }
    requestRunning = true;
    Serial.println("DB request: " + value);
    delay(1000);
    String result = Database.get<String>(aClient, value);
    // To make sure that we actually get the result or error.
    if (aClient.lastError().code() == 0)
    {
        Serial.println("DB: Success to obtain data");
        delay(1000);
        Serial.println("DB value: " + result);
        delay(1000);
        dataReady = true;
        data = result;
    }
    else
    {
        Firebase.printf("Error, msg: %s, code: %d\n", aClient.lastError().message().c_str(), aClient.lastError().code());
        requestRunning = false;
    }
}

String TheDB::getData()
{
    return data;
    dataReady = false;
}

bool TheDB::requestInProgress()
{
    return requestRunning;
}

bool TheDB::dataAvailable()
{
    return dataReady;
}