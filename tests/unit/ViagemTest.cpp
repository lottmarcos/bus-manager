#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

TEST(ViagemTest, InicializarViagemComAtributosCorretos) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    Viagem viagem(&origem, &destino, &onibus, data);

    ASSERT_EQ(viagem.getOrigem()->getNome(), "Origem");
    ASSERT_EQ(viagem.getDestino()->getNome(), "Destino");
    ASSERT_EQ(viagem.getOnibus()->getPlaca(), "XYZ9876");
    ASSERT_EQ(viagem.getData().getAno(), 2024);
    ASSERT_EQ(viagem.getData().getMes(), 1);
    ASSERT_EQ(viagem.getData().getDia(), 1);
}

TEST(ViagemTest, InicializarViagemComOrigemNula) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    ASSERT_THROW(Viagem viagem(nullptr, &destino, &onibus, data), invalid_argument);
}

TEST(ViagemTest, InicializarViagemComDestinoNulo) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Data data(1, 1, 2024);

    ASSERT_THROW(Viagem viagem(&origem, nullptr, &onibus, data), invalid_argument);
}

TEST(ViagemTest, InicializarViagemComOnibusNulo) {
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    ASSERT_THROW(Viagem viagem(&origem, &destino, nullptr, data), invalid_argument);
}

TEST(ViagemTest, AlterarViagemComOrigemNulaComSetter) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    Viagem viagem(&origem, &destino, &onibus, data);

    ASSERT_THROW(viagem.setOrigem(nullptr), invalid_argument);
}

TEST(ViagemTest, AlterarViagemComDestinoNuloComSetter) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    Viagem viagem(&origem, &destino, &onibus, data);

    ASSERT_THROW(viagem.setDestino(nullptr), invalid_argument);
}

TEST(ViagemTest, AlterarViagemComOnibusNuloComSetter) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    Viagem viagem(&origem, &destino, &onibus, data);

    ASSERT_THROW(viagem.setOnibus(nullptr), invalid_argument);
}

TEST(ViagemTest, MudarDataDaViagemComSetter) {
    Data data(1, 1, 2024);
    Viagem viagem(data);
    ASSERT_EQ(viagem.getData(), data);

    Data data2(20, 02, 2025);
    viagem.setData(data2);
    ASSERT_EQ(viagem.getData(), data2);
}

TEST(ViagemTest, VerificarDisponibilidadeDeAssentos) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);
    ASSERT_TRUE(viagem.verificarDisponibilidade());
}

TEST(ViagemTest, VerificarSeIncluiTrechoIncluso) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);
    Parada novaParada("Nova Parada", 200.0);
    ASSERT_TRUE(viagem.incluiOTrecho(&origem, &novaParada));
}

TEST(ViagemTest, VerificarSeIncluiTrechoNaoIncluso) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);
    Parada novaParada("Nova Parada", 500.0);
    ASSERT_FALSE(viagem.incluiOTrecho(&origem, &novaParada));
}

TEST(ViagemTest, CalcularTempoViagemCompleta) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);
    ASSERT_DOUBLE_EQ(viagem.calcularTempoViagemCompleta(), 400.0 / 60.0);
}

TEST(ViagemTest, CalcularTempoTrecho) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);
    Parada novaParada("Nova Parada", 200.0);
    ASSERT_DOUBLE_EQ(viagem.calcularTempoTrecho(&origem, &novaParada), 200.0 / 60.0);
}

TEST(ViagemTest, OcuparAssentoComAssentosDisponiveis) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);
    viagem.ocuparAssento();
    ASSERT_EQ(viagem.getNumAssentosLivres(), 39);
}

TEST(ViagemTest, OcuparAssentoSemAssentosDisponiveis) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);

    viagem.setNumAssentosLivres(0);
    ASSERT_THROW(viagem.ocuparAssento(), invalid_argument);
}