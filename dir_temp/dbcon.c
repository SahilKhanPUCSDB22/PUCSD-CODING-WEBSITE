#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <postgres_ext.h>

void exit_nicely(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

int main() {
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

    char *command="select * from students where stud_id=$1::bigint";
    const char *params[2]={"56","jagdale"};

    res =PQexecParams(conn,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

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
            printf("%s\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    // Free the result
    PQclear(res);

    // Close the connection
    PQfinish(conn);

    return 0;
}

