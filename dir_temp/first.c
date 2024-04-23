#include <sys/types.h> /* size_t, ssize_t */
#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include <kcgi.h>
#include <stdio.h>
#include "style.c"
#include <stdlib.h>
#include <libpq-fe.h>

void exit_nicely(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

int main(void) {
    struct kreq r;
    const char *page = "index";
    if (khttp_parse(&r, NULL, 0, &page, 1, 0) != KCGI_OK)
        return 1;
    khttp_head(&r, kresps[KRESP_STATUS],"%s", khttps[KHTTP_200]);
    khttp_head(&r, kresps[KRESP_CONTENT_TYPE],"%s", kmimetypes[KMIME_TEXT_HTML]);
    khttp_body(&r);
    khttp_puts(&r,"<html>\n<title>Sahil</title>\n<h1>Sahil Khan</h1>\n");
    khttp_puts(&r,style2); 

    const char *conninfo = "dbname=pucsd_hackerrank user=postgres password=1234";
    PGconn *conn;
    PGresult *res;

    // Establish a connection to the database
    conn = PQconnectdb(conninfo);

    // Check to see that the backend connection was successfully made
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    // Execute a query
    res = PQexec(conn, "SELECT * FROM sahil");

    // Check for errors during query execution
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query execution failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    // Process the query results
    int rows = PQntuples(res);
    int cols = PQnfields(res);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            khttp_puts(&r , PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    // Free the result
    PQclear(res);

    // Close the connection
    PQfinish(conn);

    khttp_free(&r);
    return 0;

}

