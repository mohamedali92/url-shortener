#include "db-utils.h"


void getRecord(std::string &full_url, std::string shortUrl)
{
    std::string connectionString = std::getenv("DATABASE_URL");
    pqxx::connection c{connectionString};
    pqxx::work w(c);

    c.prepare("select_from_urls", "SELECT full_url "
                                  "FROM urls "
                                  "WHERE short_url=$1");
    pqxx::row r = w.exec_prepared1("select_from_urls", shortUrl);
    w.commit();

    full_url = r["full_url"].c_str();
    std::cout << full_url << std::endl;

}

void addRecord(std::string shortUrl, std::string fullUrl)
{
    std::string connectionString = std::getenv("DATABASE_URL");
    pqxx::connection c{connectionString};
    pqxx::work w(c);

    c.prepare("insert_into_urls", "INSERT INTO urls (short_url, full_url) "
                                  "VALUES ($1, $2) "
                                  "ON CONFLICT (short_url) DO NOTHING");
    w.exec_prepared("insert_into_urls", shortUrl, fullUrl);
    w.commit();
}


//int main()
//{
//    try
//    {
//        std::string full_url{};
//        addRecord("test", "test");
//        getRecord(full_url, "f");
//    }
//    catch (std::exception const &e)
//    {
//        std::cerr << e.what() << std::endl;
//        return 1;
//    }
//
//    return 0;
//}