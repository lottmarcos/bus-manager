#include <gtest/gtest.h>
#include "Reserva.hpp"
#include "Database.hpp"
#include "OnibusService.hpp"
#include <iostream>

void assertInvalidDate(int dia, int mes, int ano) {
    EXPECT_THROW(Data(dia, mes, ano), std::invalid_argument);
}

TEST(DataTest, ConstrutorComDataCorreta) {
    EXPECT_NO_THROW(Data(1, 1, 2000));
    EXPECT_NO_THROW(Data(31, 12, 2023));
}

TEST(DataTest, ConstrutorComDataIncorreta) {
    assertInvalidDate(0, 1, 2000);
    assertInvalidDate(32, 1, 2000);
    assertInvalidDate(1, 0, 2000);
    assertInvalidDate(1, 13, 2000);
    assertInvalidDate(1, 1, -1);     
}

TEST(DataTest, CasosLimiteValidos) {
    EXPECT_NO_THROW(Data(31, 1, 2023));
    EXPECT_NO_THROW(Data(28, 2, 2023));
    EXPECT_NO_THROW(Data(29, 2, 2024));
    EXPECT_NO_THROW(Data(30, 4, 2023));
}

TEST(DataTest, AlteracoesValidasComGetteresESetteres) {
    Data data(10, 12, 2023);
    
    data.setDia(15);
    data.setMes(11);
    data.setAno(2022);

    EXPECT_EQ(data.getDia(), 15);
    EXPECT_EQ(data.getMes(), 11);
    EXPECT_EQ(data.getAno(), 2022);
}

TEST(DataTest, AlteracoesInvalidasComGetteresESetteres) {
    Data data(10, 12, 2023);

    EXPECT_THROW(data.setDia(32), std::invalid_argument);
    EXPECT_THROW(data.setMes(13), std::invalid_argument);
    EXPECT_THROW(data.setAno(-1), std::invalid_argument);
}

TEST(DataTest, OperadoresDeIgualdade) {
    Data data1(10, 12, 2023);
    Data data2(11, 12, 2023);
    Data data3(10, 12, 2023);

    EXPECT_TRUE(data1 == data3);
    EXPECT_FALSE(data1 == data2);
}

TEST(DataTest, OperadoresDeDiferenca) {
    Data data1(10, 12, 2023);
    Data data2(11, 12, 2023);
    Data data3(10, 12, 2023);

    EXPECT_FALSE(data1 != data3);
    EXPECT_TRUE(data1 != data2);
}

TEST(DataTest, OperadoresDeMenorOuIgualQue) {
    Data data1(10, 12, 2023);
    Data data2(11, 12, 2023);
    Data data3(10, 12, 2023);

    EXPECT_TRUE(data1 < data2);
    EXPECT_FALSE(data2 < data1);

    EXPECT_TRUE(data1 <= data3);
    EXPECT_TRUE(data1 <= data2);
    EXPECT_FALSE(data2 <= data1);
}

TEST(DataTest, OperadoresDeMaiorOuIgualQue) {
    Data data1(10, 12, 2023);
    Data data2(11, 12, 2023);
    Data data3(10, 12, 2023);

    EXPECT_TRUE(data2 > data1);
    EXPECT_FALSE(data1 > data2);


    EXPECT_TRUE(data2 >= data1);
    EXPECT_TRUE(data1 >= data3);
    EXPECT_FALSE(data1 >= data2);
}


TEST(DataTest, OperacoesDeInput) {
    Data data(10, 12, 2023);

    std::ostringstream oss;
    oss << data;
    EXPECT_EQ(oss.str(), "10/12/2023");
}

TEST(DataTest, OperacoesDeOutnput) {
    Data data(10, 12, 2023);

    std::istringstream issValid("15/11/2022");
    issValid >> data;
    EXPECT_EQ(data.getDia(), 15);
    EXPECT_EQ(data.getMes(), 11);
    EXPECT_EQ(data.getAno(), 2022);

    std::istringstream issInvalid("15-11-2022");
    issInvalid >> data;
    EXPECT_TRUE(issInvalid.fail());
}