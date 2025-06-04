#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

TEST(ParadaTest, InicializarParadaComAtributosCorretos) {
    Parada novaParada("Nova Parada", 10.0);
    ASSERT_DOUBLE_EQ(novaParada.getId(), 1);
    ASSERT_EQ(novaParada.getNome(), "Nova Parada");
    ASSERT_DOUBLE_EQ(novaParada.getDistanciaPartida(), 10.0);
}

TEST(ParadaTest, InicializarParadaComNomeVazio) {
    ASSERT_THROW(Parada parada("", 10.0), invalid_argument);
}

TEST(ParadaTest, InicializarParadaComDistanciaNegativa) {
    ASSERT_THROW(Parada parada("Parada", -10.0), invalid_argument);
}

TEST(ParadaTest, CalcularDistanciaEntreParadasSentidoIda) {
    Parada origem("Origem", 10.0);
    Parada destino("Destino", 50.0);
    ASSERT_DOUBLE_EQ(origem.calcularDistancia(destino), 40.0);
}

TEST(ParadaTest, CalcularDistanciaEntreParadasSentidoVolta) {
    Parada origem("Origem", 60.0);
    Parada destino("Destino", 20.0);
    ASSERT_DOUBLE_EQ(origem.calcularDistancia(destino), 40.0);
}

TEST(ParadaTest, CalcularDistanciaEntreParadasMesmaPosicao) {
    Parada origem("Origem", 100.0);
    Parada destino("Destino", 100.0);
    ASSERT_THROW(origem.calcularDistancia(destino), invalid_argument);
}

TEST(ParadaTest, VerificarParadaEAposOutra) {
    Parada origem("Origem", 10.0);
    Parada destino("Destino", 50.0);
    ASSERT_TRUE(origem.eApos(destino));
}

TEST(ParadaTest, AlterarNomeParadaComNomeValido) {
    Parada parada("Origem", 0.0);
    parada.setNome("Nova Origem");
    ASSERT_EQ(parada.getNome(), "Nova Origem");
}

TEST(ParadaTest, AlterarNomeParadaComNomeVazio) {
    Parada parada("Origem", 0.0);
    ASSERT_THROW(parada.setNome(""), invalid_argument);
}

TEST(ParadaTest, DefinirDistanciaParadaComDistanciaValida) {
    Parada parada("Origem", 0.0);
    parada.setDistanciaPartida(200.0);
    ASSERT_DOUBLE_EQ(parada.getDistanciaPartida(), 200.0);
}

TEST(ParadaTest, DefinirDistanciaParadaComDistanciaNegativa) {
    Parada parada("Origem", 0.0);
    ASSERT_THROW(parada.setDistanciaPartida(-10.0), invalid_argument);
}