#include "db-utils.h"
#include "crow_all.h"
#include "utils.h"


int main()
{
    crow::SimpleApp app; // define crow application

    //define endpoint at the root directory
    CROW_ROUTE(app, "/")
    ([]() {
        CROW_LOG_INFO << "Short url: " << shortenUrl("www.apple.com");
        return shortenUrl("www.apple.com");
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
        try
        {
            addRecord(shortenedUrl, fullUrl);
            CROW_LOG_INFO << "Shortened url: " << shortenedUrl;
            return crow::response(shortenedUrl);
        }

        catch (std::exception const &e)
        {
            CROW_LOG_ERROR << e.what();
            return crow::response(500, "Failed to insert record into Database");
        }
    });


    CROW_ROUTE(app, "/<string>")
    ([](const crow::request& req, crow::response& res, std::string shortUrl) {
        CROW_LOG_INFO << "Will check DB for: " << shortUrl;
        try
        {
            std::string fullUrl{};
            getRecord(fullUrl, shortUrl);
            CROW_LOG_INFO << "Found record of the following: " << fullUrl;
            CROW_LOG_INFO << "Redirecting to -> http://" + fullUrl;
            res.redirect("http://" + fullUrl);

        }
        catch (std::exception const &e)
        {
            CROW_LOG_ERROR << e.what();
            res.code = 404;
        }

        res.end();

    });

 
    // enables all log
    app.loglevel(crow::LogLevel::DEBUG);
    // set the port, set the app to run on multiple threads, and run the app
    char* port = getenv("PORT");
    uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
    cout << "PORT = " << iPort << "\n";
    app.port(iPort).multithreaded().run();
}