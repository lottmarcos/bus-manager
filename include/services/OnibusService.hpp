#ifndef ONIBUSSERVICE_HPP
#define ONIBUSSERVICE_HPP

#include "Database.hpp"
#include "Onibus.hpp"
#include <vector>
#include <iostream>
#include <optional>

class OnibusService {
    private:
        Database &db;

    public:
        void verificarEInicializarTabela();
        explicit OnibusService(Database &database);
        int adicionarOnibus(const Onibus &onibus);
        Onibus* buscarOnibusPorId(int id);
        std::vector<Onibus> listarTodosOnibus();
        void atualizarOnibus(const Onibus &onibus);
        void deletarOnibus(int id);
};

#endif
