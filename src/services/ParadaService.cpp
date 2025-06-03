#include "ParadaService.hpp"
#include <sstream>

ParadaService::ParadaService(Database &database) : db(database) {}

void ParadaService::verificarEInicializarTabela() {
    std::string checkTableQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='Parada';";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), checkTableQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta para verificar tabela.");
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        db.initializeTables();
    }

    sqlite3_finalize(stmt);
}

int ParadaService::adicionarParada(const Parada &parada) {
    verificarEInicializarTabela();

    std::stringstream query;
    query << "INSERT INTO Parada (nome, distancia_partida) VALUES ('"
          << parada.getNome() << "', " << parada.getDistanciaPartida() << ");";
    db.execute(query.str());
    return sqlite3_last_insert_rowid(db.getConnection());
}

Parada* ParadaService::buscarParadaPorId(int id) {
    verificarEInicializarTabela();

    std::stringstream query;
    query << "SELECT * FROM Parada WHERE id = " << id << ";";
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta.");
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int idRecuperado = sqlite3_column_int(stmt, 0);
        std::string nome = (const char*)sqlite3_column_text(stmt, 1);
        double distanciaPartida = sqlite3_column_double(stmt, 2);

        Parada* parada = new Parada(nome, distanciaPartida);
        parada->setId(idRecuperado);

        sqlite3_finalize(stmt);
        return parada;
    }

    sqlite3_finalize(stmt);
    return nullptr;
}

std::vector<Parada> ParadaService::listarTodasParadas() {
    verificarEInicializarTabela();

    std::vector<Parada> paradaList;
    const std::string query = "SELECT * FROM Parada;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db.getConnection(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta.");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string nome = (const char*)sqlite3_column_text(stmt, 1);
        double distanciaPartida = sqlite3_column_double(stmt, 2);

        Parada parada(nome, distanciaPartida);
        parada.setId(id);
        paradaList.push_back(parada);
    }

    sqlite3_finalize(stmt);
    return paradaList;
}

void ParadaService::atualizarParada(const Parada &parada) {
    verificarEInicializarTabela();

    std::stringstream query;
    query << "UPDATE Parada SET nome = '" << parada.getNome()
          << "', distancia_partida = " << parada.getDistanciaPartida()
          << " WHERE id = " << parada.getId() << ";";
    db.execute(query.str());
}

void ParadaService::deletarParada(int id) {
    verificarEInicializarTabela();

    std::stringstream query;
    query << "DELETE FROM Parada WHERE id = " << id << ";";
    db.execute(query.str());
}
