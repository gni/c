#include <stdio.h>
#include <sqlite3.h>

void execute_query(sqlite3 *db, const char *sql) {
    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("test.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    execute_query(db, "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, name TEXT);");
    execute_query(db, "INSERT INTO users(name) VALUES('Alice');");
    execute_query(db, "INSERT INTO users(name) VALUES('Bob');");

    printf("Users in database:\n");
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM users;", -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d, Name: %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return 0;
}
