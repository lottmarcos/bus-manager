#include "OnibusService.hpp"
#include <sstream>

OnibusService::OnibusService(Database &database) : db(database) {}

void OnibusService::verificarEInicializarTabela() {
    std::string checkTableQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='Onibus';";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), checkTableQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta para verificar tabela.");
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        db.initializeTables();  
    }

    sqlite3_finalize(stmt);
}

int OnibusService::adicionarOnibus(const Onibus &onibus) {
    verificarEInicializarTabela();
    std::stringstream query;
    query << "INSERT INTO Onibus (placa, num_assentos, velocidade_media, valor_km) VALUES ('"
          << onibus.getPlaca() << "', " << onibus.getNumAssentos() << ", " << onibus.getVelocidadeMedia()
          << ", " << onibus.getValorKm() << ");";
    db.execute(query.str());
    return sqlite3_last_insert_rowid(db.getConnection());
}

Onibus* OnibusService::buscarOnibusPorId(int id) {
    verificarEInicializarTabela();
    std::stringstream query;
    query << "SELECT * FROM Onibus WHERE id = " << id << ";";
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta.");
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int idRecuperado = sqlite3_column_int(stmt, 0);
        std::string placa = (const char*)sqlite3_column_text(stmt, 1);
        int numAssentos = sqlite3_column_int(stmt, 2);
        double velocidadeMedia = sqlite3_column_double(stmt, 3);
        double valorKm = sqlite3_column_double(stmt, 4);

        Onibus* onibus = new Onibus(idRecuperado, placa, numAssentos, velocidadeMedia, valorKm);

        sqlite3_finalize(stmt);
        return onibus;
    }

    sqlite3_finalize(stmt);
    return nullptr;
}

std::vector<Onibus> OnibusService::listarTodosOnibus() {
    std::vector<Onibus> onibusList;
    const std::string query = "SELECT * FROM Onibus;";
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta: " + std::string(sqlite3_errmsg(db.getConnection())));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);

        const char* placa = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        if (!placa) {
            placa = ""; 
        }

        int num_assentos = sqlite3_column_int(stmt, 2);
        double velocidade_media = sqlite3_column_double(stmt, 3);
        double valor_km = sqlite3_column_double(stmt, 4);

        Onibus onibus(id, placa, num_assentos, velocidade_media, valor_km);
        onibusList.push_back(onibus);
    }

    sqlite3_finalize(stmt);
    return onibusList;
}

void OnibusService::atualizarOnibus(const Onibus &onibus) {
    verificarEInicializarTabela();
    std::stringstream query;
    query << "UPDATE Onibus SET placa = '" << onibus.getPlaca()
          << "', num_assentos = " << onibus.getNumAssentos()
          << ", velocidade_media = " << onibus.getVelocidadeMedia()
          << ", valor_km = " << onibus.getValorKm()
          << " WHERE id = " << onibus.getId() << ";";
    db.execute(query.str());
}

void OnibusService::deletarOnibus(int id) {
    verificarEInicializarTabela();
    std::stringstream query;
    query << "DELETE FROM Onibus WHERE id = " << id << ";";
    db.execute(query.str());
}
