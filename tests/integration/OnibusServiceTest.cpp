#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

class OnibusServiceTeste : public ::testing::Test {
protected:
    Database* db;
    OnibusService* onibusService;

    void SetUp() override {
        db = new Database(":memory:");
        db->initializeTables();
        onibusService = new OnibusService(*db);
    }

    void TearDown() override {
        delete onibusService;
        delete db;
    }
};

TEST_F(OnibusServiceTeste, AdicionarOnibus_QuandoAdicionaOnibus_EntaoRetornaOnibusComSucesso) {
    int id = onibusService->adicionarOnibus(Onibus("ABC1234", 50, 60.0, 2.5));

    Onibus* onibus = onibusService->buscarOnibusPorId(id);

    ASSERT_TRUE(onibus != nullptr);
    ASSERT_EQ(onibus->getId(), id);
    ASSERT_EQ(onibus->getNumAssentos(), 50);
    ASSERT_DOUBLE_EQ(onibus->getVelocidadeMedia(), 60.0);
    ASSERT_DOUBLE_EQ(onibus->getValorKm(), 2.5);
    ASSERT_EQ(onibus->getPlaca(), "ABC1234");

    delete onibus;
}

TEST_F(OnibusServiceTeste, BuscarOnibusPorId_QuandoIdInvalido_EntaoRetornaNulo) {
    Onibus* onibus = onibusService->buscarOnibusPorId(999);

    ASSERT_TRUE(onibus == nullptr);

    delete onibus;
}

TEST_F(OnibusServiceTeste, DeletarOnibus_QuandoDeletaOnibus_EntaoOnibusNaoERecuperado) {
    int id = onibusService->adicionarOnibus(Onibus("ABC1234", 50, 60.0, 2.5));

    Onibus* onibus = onibusService->buscarOnibusPorId(id);

    ASSERT_TRUE(onibus != nullptr);

    onibusService->deletarOnibus(id);
    onibus = onibusService->buscarOnibusPorId(id);

    ASSERT_TRUE(onibus == nullptr);

    delete onibus;
}

TEST_F(OnibusServiceTeste, ListarOnibus_QuandoOnibusCadastrados_EntaoRetornaListaDeOnibus) {
    onibusService->adicionarOnibus(Onibus("ABC1234", 50, 60.0, 2.5));
    onibusService->adicionarOnibus(Onibus("XYZ9876", 60, 70.0, 3.0));

    std::vector<Onibus> onibusList = onibusService->listarTodosOnibus();

    ASSERT_EQ(onibusList.size(), 2);

    ASSERT_EQ(onibusList[0].getPlaca(), "ABC1234");
    ASSERT_EQ(onibusList[1].getPlaca(), "XYZ9876");
}

TEST_F(OnibusServiceTeste, ListarOnibus_QuandoFalhaNoBanco_EntaoLancaExcecao) {
    db->execute("DROP TABLE Onibus;");  // Força a falha no banco de dados

    ASSERT_THROW({
        onibusService->listarTodosOnibus();
    }, std::runtime_error);
}