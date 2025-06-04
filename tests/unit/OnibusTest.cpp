#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

TEST(OnibusTest, InicializarOnibusComAtributosCorretosSemValorKm) {
    Onibus onibus("XYZ9876", 40, 60.0);
    ASSERT_EQ(onibus.getPlaca(), "XYZ9876");
    ASSERT_EQ(onibus.getNumAssentos(), 40);
    ASSERT_DOUBLE_EQ(onibus.getVelocidadeMedia(), 60.0);
    ASSERT_DOUBLE_EQ(onibus.getValorKm(), 5.0);
}

TEST(OnibusTest, InicializarOnibusComAtributosCorretosComValorKm) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_EQ(onibus.getPlaca(), "XYZ9876");
    ASSERT_EQ(onibus.getNumAssentos(), 40);
    ASSERT_DOUBLE_EQ(onibus.getVelocidadeMedia(), 60.0);
    ASSERT_DOUBLE_EQ(onibus.getValorKm(), 10.0);
}

TEST(OnibusTest, InicializarOnibusComPlacaIncorretaComValorKm) {
    ASSERT_THROW(Onibus onibus("", 40, 60.0, 10.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComNumAssentosIncorretoComValorKm) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 0, 60.0, 10.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComVelocidadeMediaIncorretaComValorKm) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 40, 0.0, 10.0), invalid_argument);
}

TEST(OnibusTest, MudaPlacaDeOnibusComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_EQ(onibus.getPlaca(), "XYZ9876");

    onibus.setPlaca("ABC1234");
    ASSERT_EQ(onibus.getPlaca(), "ABC1234");
}

TEST(OnibusTest, MudaNumAssentosDeOnibusComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_EQ(onibus.getNumAssentos(), 40);
    
    onibus.setNumAssentos(55);
    ASSERT_EQ(onibus.getNumAssentos(), 55);
}

TEST(OnibusTest, MudaVelocidadeMediaDeOnibusComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_DOUBLE_EQ(onibus.getVelocidadeMedia(), 60.0);
    
    onibus.setVelocidadeMedia(80.0);
    ASSERT_DOUBLE_EQ(onibus.getVelocidadeMedia(), 80.0);
}

TEST(OnibusTest, MudaValorKmDeOnibusComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_DOUBLE_EQ(onibus.getValorKm(), 10.0);
    
    onibus.setValorKm(5.0);
    ASSERT_DOUBLE_EQ(onibus.getValorKm(), 5.0);
}

TEST(OnibusTest, MudaPlacaDeOnibusInvalidaComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_EQ(onibus.getPlaca(), "XYZ9876");

    ASSERT_THROW(onibus.setPlaca(""), invalid_argument);
}

TEST(OnibusTest, MudaNumAssentosDeOnibusInvalidoComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_EQ(onibus.getNumAssentos(), 40);
    
    ASSERT_THROW(onibus.setNumAssentos(0), invalid_argument);
}

TEST(OnibusTest, MudaVelocidadeMediaDeOnibusInvalidaComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_DOUBLE_EQ(onibus.getVelocidadeMedia(), 60.0);
    
    ASSERT_THROW(onibus.setVelocidadeMedia(0), invalid_argument);
}

TEST(OnibusTest, MudaValorKmDeOnibusInvalidoComSetters) {
    Onibus onibus("XYZ9876", 40, 60.0, 10.0);
    ASSERT_DOUBLE_EQ(onibus.getValorKm(), 10.0);
    
    ASSERT_THROW(onibus.setValorKm(0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComPlacaVazia) {
    ASSERT_THROW(Onibus onibus("", 40, 60.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComNumAssentosNegativo) {
    ASSERT_THROW(Onibus onibus("XYZ9876", -40, 60.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComVelocidadeMediaNegativa) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 40, -60.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComValorKmNegativo) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 40, 60.0, -10.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComNumAssentosIgualAZero) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 0, 60.0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComVelocidadeMediaIgualAZero) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 40, 0), invalid_argument);
}

TEST(OnibusTest, InicializarOnibusComValorKmIgualAZero) {
    ASSERT_THROW(Onibus onibus("XYZ9876", 40, 60.0, 0), invalid_argument);
}