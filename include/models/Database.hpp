#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>

class Database {
    private:
        sqlite3 *db;
        std::string dbName;

    public:
        Database(const std::string &name);
        ~Database();
        void execute(const std::string &query);
        void initializeTables();
        sqlite3* getConnection() const;
};

#endif
