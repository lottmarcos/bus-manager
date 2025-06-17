#include <gtest/gtest.h>
#include "Parada.hpp"
#include "Database.hpp"
#include "ParadaService.hpp"
#include <iostream>

class ParadaServiceTeste : public ::testing::Test {
protected:
    Database* db;
    ParadaService* paradaService;

    void SetUp() override {
        db = new Database(":memory:");
        db->initializeTables();
        paradaService = new ParadaService(*db);
    }

    void TearDown() override {
        delete paradaService;
        delete db;
    }
};

TEST_F(ParadaServiceTeste, AdicionarParada_QuandoAdicionaParada_EntaoRetornaParadaComSucesso) {
    int id = paradaService->adicionarParada(Parada("Centro", 5.5));
    Parada* parada = paradaService->buscarParadaPorId(id);

    ASSERT_TRUE(parada != nullptr);
    ASSERT_EQ(parada->getId(), id);
    ASSERT_EQ(parada->getNome(), "Centro");
    ASSERT_DOUBLE_EQ(parada->getDistanciaPartida(), 5.5);

    delete parada;
}

TEST_F(ParadaServiceTeste, DeletarParada_QuandoDeletaParada_EntaoParadaNaoEListada) {
    int id = paradaService->adicionarParada(Parada("Zona Norte", 10.0));
    Parada* parada = paradaService->buscarParadaPorId(id);
    ASSERT_TRUE(parada != nullptr);

    paradaService->deletarParada(id);

    parada = paradaService->buscarParadaPorId(id);
    ASSERT_TRUE(parada == nullptr);

    delete parada;
}

TEST_F(ParadaServiceTeste, ListarTodasParadas_QuandoParadasCadastradas_EntaoRetornaListaDeParadas) {
    paradaService->adicionarParada(Parada("Centro", 5.0));
    paradaService->adicionarParada(Parada("Zona Sul", 15.0));
    paradaService->adicionarParada(Parada("Zona Oeste", 20.0));

    std::vector<Parada> paradaList = paradaService->listarTodasParadas();

    ASSERT_EQ(paradaList.size(), 3);
    ASSERT_EQ(paradaList[0].getNome(), "Centro");
    ASSERT_EQ(paradaList[1].getNome(), "Zona Sul");
    ASSERT_EQ(paradaList[2].getNome(), "Zona Oeste");
}

TEST_F(ParadaServiceTeste, AtualizarParada_QuandoAtualizaParada_EntaoParadaECarregadaComNovosValores) {
    int id = paradaService->adicionarParada(Parada("Terminal", 25.0));
    Parada* parada = paradaService->buscarParadaPorId(id);
    ASSERT_TRUE(parada != nullptr);

    parada->setNome("Terminal Rodoviário");
    parada->setDistanciaPartida(30.0);

    paradaService->atualizarParada(*parada);

    Parada* paradaAtualizada = paradaService->buscarParadaPorId(id);
    ASSERT_TRUE(paradaAtualizada != nullptr);
    ASSERT_EQ(paradaAtualizada->getNome(), "Terminal Rodoviário");
    ASSERT_DOUBLE_EQ(paradaAtualizada->getDistanciaPartida(), 30.0);

    delete parada;
    delete paradaAtualizada;
}

TEST_F(ParadaServiceTeste, BuscarParadaPorId_QuandoIdInvalido_EntaoRetornaNulo) {
    Parada* parada = paradaService->buscarParadaPorId(999);

    ASSERT_TRUE(parada == nullptr);

    delete parada;
}