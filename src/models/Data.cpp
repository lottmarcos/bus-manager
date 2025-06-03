#include "Data.hpp"
#include <iostream>
#include <stdexcept>

Data::Data(int dia, int mes, int ano) {
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 0) {
        throw invalid_argument("Data invalida.");
    }
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

int Data::getDia() {
    return dia;
}

void Data::setDia(int dia) {
    if (dia < 1 || dia > 31) {
        throw invalid_argument("Dia invalido.");
    }
    this->dia = dia;
}

int Data::getMes() {
    return mes;
}

void Data::setMes(int mes) {
    if (mes < 1 || mes > 12) {
        throw invalid_argument("Mes invalido.");
    }
    this->mes = mes;
}

int Data::getAno() {
    return ano;
}

void Data::setAno(int ano) {
    if (ano < 0) {
        throw invalid_argument("Ano invalido.");
    }
    this->ano = ano;
}

bool Data::operator==(const Data &other) const {
    return dia == other.dia && mes == other.mes && ano == other.ano;
}

bool Data::operator!=(const Data &other) const {
    return !(*this == other);
}

bool Data::operator<(const Data &other) const {
    if (ano < other.ano) return true;
    if (ano == other.ano && mes < other.mes) return true;
    if (ano == other.ano && mes == other.mes && dia < other.dia) return true;
    return false;
}

bool Data::operator<=(const Data &other) const {
    return *this < other || *this == other;
}

bool Data::operator>(const Data &other) const {
    return !(*this <= other);
}

bool Data::operator>=(const Data &other) const {
    return !(*this < other);
}

ostream &operator<<(ostream &out, const Data &data) {
    out << (data.dia < 10 ? "0" : "") << data.dia << "/"
        << (data.mes < 10 ? "0" : "") << data.mes << "/"
        << data.ano;
    return out;
}

istream &operator>>(istream &in, Data &data) {
    char sep1, sep2;
    in >> data.dia >> sep1 >> data.mes >> sep2 >> data.ano;
    if (sep1 != '/' || sep2 != '/') {
        in.setstate(ios::failbit);
    }
    return in;
}
