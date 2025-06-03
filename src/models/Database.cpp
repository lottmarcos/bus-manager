#include "Database.hpp"
#include <iostream>
#include <stdexcept>
#include <sqlite3.h>

Database::Database(const std::string &name) : dbName(name) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Erro ao abrir banco de dados.");
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::execute(const std::string &query) {
    char *errorMessage = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::string error = "Erro ao executar query: " + std::string(errorMessage);
        sqlite3_free(errorMessage);
        throw std::runtime_error(error);
    }
}

void Database::initializeTables() {
    const std::string createTables = R"(
        CREATE TABLE IF NOT EXISTS Data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            dia INTEGER NOT NULL,
            mes INTEGER NOT NULL,
            ano INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Onibus (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            placa TEXT NOT NULL,
            num_assentos INTEGER NOT NULL,
            velocidade_media REAL NOT NULL,
            valor_km REAL NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Parada (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT NOT NULL,
            distancia_partida REAL NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Viagem (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            origem_id INTEGER NOT NULL,
            destino_id INTEGER NOT NULL,
            onibus_id INTEGER NOT NULL,
            data_id INTEGER NOT NULL,
            num_assentos_livres INTEGER NOT NULL,
            FOREIGN KEY(origem_id) REFERENCES Parada(id),
            FOREIGN KEY(destino_id) REFERENCES Parada(id),
            FOREIGN KEY(onibus_id) REFERENCES Onibus(id),
            FOREIGN KEY(data_id) REFERENCES Data(id)
        );

        CREATE TABLE IF NOT EXISTS Reserva (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            viagem_id INTEGER NOT NULL,
            cpf TEXT NOT NULL,
            origem_id INTEGER NOT NULL,
            destino_id INTEGER NOT NULL,
            valor_passagem REAL NOT NULL,
            FOREIGN KEY(viagem_id) REFERENCES Viagem(id),
            FOREIGN KEY(origem_id) REFERENCES Parada(id),
            FOREIGN KEY(destino_id) REFERENCES Parada(id)
        );
    )";

    execute(createTables);
}

sqlite3* Database::getConnection() const {
    return db;
}