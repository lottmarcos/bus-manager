#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

TEST(ReservaTest, InicializarReservaComAtributosCorretos) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);

    Reserva reserva(&viagem, "12345678901", origem, destino);
    ASSERT_EQ(reserva.getOrigem()->getNome(), "Origem");
    ASSERT_EQ(reserva.getDestino()->getNome(), "Destino");
    ASSERT_EQ(reserva.getViagem()->getOrigem()->getNome(), "Origem");
    ASSERT_EQ(reserva.getViagem()->getDestino()->getNome(), "Destino");
    ASSERT_EQ(reserva.getViagem()->getOnibus()->getPlaca(), "XYZ9876");
    ASSERT_EQ(reserva.getData().getAno(), 2024);
    ASSERT_EQ(reserva.getData().getMes(), 1);
    ASSERT_EQ(reserva.getData().getDia(), 1);
    ASSERT_EQ(reserva.getCPF(), "12345678901");
    ASSERT_DOUBLE_EQ(reserva.getValorPassagem(), 400.0 * 10.0);
}

TEST(ReservaTest, InicializarReservaComViagemNula) {
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    ASSERT_THROW(Reserva reserva(nullptr, "12345678901", &origem, &destino), invalid_argument);
}

TEST(ReservaTest, InicializarReservaComCPFNulo) {
    Onibus* onibus = new Onibus("XYZ9876", 40, 60.0, 10.0);
    Parada* origem = new Parada("Origem", 0.0);
    Parada* destino = new Parada("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(origem);
    viagem.setOnibus(onibus);
    viagem.setDestino(destino);

    ASSERT_THROW(Reserva reserva(&viagem, "", origem, destino), invalid_argument);
}

TEST(ReservaTest, InicializarReservaComOrigemNula) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);
    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);

    ASSERT_THROW(Reserva reserva(&viagem, "12345678901", nullptr, &destino), invalid_argument);
}

TEST(ReservaTest, InicializarReservaComDestinoNulo) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);
    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);

    ASSERT_THROW(Reserva reserva(&viagem, "12345678901", &origem, nullptr), invalid_argument);
}

TEST(ReservaTest, CancelarReserva) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);
    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);

    Reserva reserva(&viagem, "12345678901", &origem, &destino);
    reserva.cancelarReserva();
    ASSERT_EQ(viagem.getNumAssentosLivres(), 40);
    ASSERT_EQ(reserva.estaAtiva(), false);
}

TEST(ViagemTest, CancelarAssentoSemAssentoOcupado) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    Parada origem("Origem", 0.0);
    Parada destino("Destino", 400.0);
    Data data(1, 1, 2024);

    
    Viagem viagem(data);
    viagem.setOrigem(&origem);
    viagem.setOnibus(&onibus);
    viagem.setDestino(&destino);
    ASSERT_THROW(viagem.desocuparAssento(), invalid_argument);
}