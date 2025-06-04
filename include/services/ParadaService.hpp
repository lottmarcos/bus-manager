#ifndef PARADASERVICE_HPP
#define PARADASERVICE_HPP

#include "Database.hpp"
#include "Parada.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class ParadaService {
    private:
        Database &db;

    public:
        void verificarEInicializarTabela();
        explicit ParadaService(Database &database);
        int adicionarParada(const Parada &parada);
        Parada* buscarParadaPorId(int id);
        std::vector<Parada> listarTodasParadas();
        void atualizarParada(const Parada &parada);
        void deletarParada(int id);
};

#endif
