#include "db-utils.h"
#include "crow_all.h"
#include "utils.h"
#include <cassandra.h>

int main()
{
    crow::SimpleApp app; // define crow application

    //define endpoint at the root directory
    CROW_ROUTE(app, "/")
    ([]() {
        CROW_LOG_INFO << "Short url: " << shortenUrl("www.apple.com");
        addRecord("short", "looooong");
        return getRecord("short");
    });

    // more json example
    CROW_ROUTE(app, "/create_new_url")
    ([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        CROW_LOG_DEBUG << x;
        std::ostringstream os;
        std::string fullUrl = preProcessUrl(x["url"].s()); 
        std::string shortenedUrl = shortenUrl(fullUrl);
        bool rc = addRecord(shortenedUrl, fullUrl);
        if (!rc)
            return crow::response(500, "Failed to insert record into Database");
        CROW_LOG_DEBUG << "Shortened url: " << shortenedUrl;
        return crow::response(shortenedUrl);
    });


    CROW_ROUTE(app, "/<string>")
    ([](const crow::request& req, crow::response& res, std::string shortUrl) {
        CROW_LOG_INFO << "Will check DB for: " << shortUrl;
        std::string fullUrl = getRecord(shortUrl);
        CROW_LOG_INFO << "Found record of the following: " << fullUrl;
        CROW_LOG_INFO << "http://" + fullUrl;
        res.redirect("http://" + fullUrl);
        res.end();
    });

 
    // enables all log
    app.loglevel(crow::LogLevel::DEBUG);
    // set the port, set the app to run on multiple threads, and run the app
    app
        .port(18080)
        .multithreaded()
        .run();
}