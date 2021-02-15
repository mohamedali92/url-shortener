#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

//#include "db-utils.h"
#include <cassandra.h>
#include <stdexcept>
#include <dse.h>

struct Url_
{
    const char *shortUrl;
    const char *fullUrl;
};

typedef struct Url_ Url;

void print_error(CassFuture *future)
{
    const char *message;
    size_t message_length;
    cass_future_error_message(future, &message, &message_length);
    fprintf(stderr, "Error: %.*s\n", (int)message_length, message);
}

CassCluster *create_cluster(const char *hosts)
{
    CassCluster *cluster = cass_cluster_new();
    cass_cluster_set_contact_points(cluster, hosts);
    cass_cluster_set_dse_plaintext_authenticator(cluster, "cassandra", "cassandra");
    return cluster;
}

CassError connect_session(CassSession *session, const CassCluster *cluster)
{
    CassError rc = CASS_OK;
    CassFuture *future = cass_session_connect(session, cluster);

    cass_future_wait(future);
    rc = cass_future_error_code(future);
    if (rc != CASS_OK)
    {
        print_error(future);
    }
    cass_future_free(future);

    return rc;
}

CassError execute_query(CassSession *session, const char *query)
{
    CassError rc = CASS_OK;
    CassFuture *future = NULL;
    CassStatement *statement = cass_statement_new(query, 0);

    future = cass_session_execute(session, statement);
    cass_future_wait(future);

    rc = cass_future_error_code(future);
    if (rc != CASS_OK)
    {
        print_error(future);
    }

    cass_future_free(future);
    cass_statement_free(statement);

    return rc;
}

CassError insert_into_urls(CassSession *session, const char *key, const Url *url)
{
    CassError rc = CASS_OK;
    CassStatement *statement = NULL;
    CassFuture *future = NULL;
    const char *query =
        "INSERT INTO url_shortener.urls (short_url, full_url) VALUES (?, ?);";

    statement = cass_statement_new(query, 2);

    cass_statement_bind_string(statement, 0, key);
    cass_statement_bind_string(statement, 1, url->fullUrl);

    future = cass_session_execute(session, statement);
    cass_future_wait(future);

    rc = cass_future_error_code(future);
    if (rc != CASS_OK)
    {
        print_error(future);
    }

    cass_future_free(future);
    cass_statement_free(statement);

    return rc;
}

CassError select_from_urls(CassSession *session, const char *key, Url *url)
{
    CassError rc = CASS_OK;
    CassStatement *statement = NULL;
    CassFuture *future = NULL;
    const char *query = "SELECT * FROM url_shortener.urls WHERE short_url = ?";

    statement = cass_statement_new(query, 1);

    cass_statement_bind_string(statement, 0, key);

    future = cass_session_execute(session, statement);
    cass_future_wait(future);

    rc = cass_future_error_code(future);
    if (rc != CASS_OK)
    {
        print_error(future);
    }
    else
    {
        const CassResult *result = cass_future_get_result(future);
        CassIterator *iterator = cass_iterator_from_result(result);

        if (cass_iterator_next(iterator))
        {
            const CassRow *row = cass_iterator_get_row(iterator);
            size_t string_value_length;
            cass_value_get_string(cass_row_get_column(row, 0), &url->shortUrl, &string_value_length);
            cass_value_get_string(cass_row_get_column(row, 1), &url->fullUrl, &string_value_length);
        }

        cass_result_free(result);
        cass_iterator_free(iterator);
    }

    cass_future_free(future);
    cass_statement_free(statement);

    return rc;
}

std::string getRecord(std::string shortUrl)
{
    CassCluster *cluster = NULL;
    CassSession *session = cass_session_new();
    char const *hosts = "127.0.0.1";
    cluster = create_cluster(hosts);

    if (connect_session(session, cluster) != CASS_OK)
    {
        cass_cluster_free(cluster);
        cass_session_free(session);
        throw std::runtime_error("Unable to connect to cassandra cluster");
    }
        
    Url outputUrl;

    select_from_urls(session, shortUrl.c_str(), &outputUrl);

    return std::string(outputUrl.fullUrl);
}

bool addRecord(std::string shortUrl, std::string fullUrl)
{
    CassCluster *cluster = NULL;
    CassSession *session = cass_session_new();
    char const *hosts = "127.0.0.1";

    Url inputUrl = {shortUrl.c_str(), fullUrl.c_str()};

    cluster = create_cluster(hosts);

    if (connect_session(session, cluster) != CASS_OK)
    {
        cass_cluster_free(cluster);
        cass_session_free(session);
        throw std::runtime_error("Unable to connect to cassandra cluster");
    }



    int rc = insert_into_urls(session, inputUrl.shortUrl, &inputUrl);

    if (rc != CASS_OK)
    {
        return false;
    }
    return true;
}


