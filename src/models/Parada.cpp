#include "Parada.hpp"
#include <iostream>

int Parada::contadorId = 0;

Parada::Parada(string nome, double distanciaPartida)
    : nome(nome), distanciaPartida(distanciaPartida) {
        id = ++contadorId;
        if (nome.empty()) {
            throw invalid_argument("Nome da parada nao pode ser nulo");
        }
        if (distanciaPartida < 0) {
            throw invalid_argument("Distancia de partida nao pode ser negativa");
        }
}

double Parada::calcularDistancia(Parada destino) const {
    if (distanciaPartida == destino.getDistanciaPartida()) {
        throw invalid_argument("Paradas estão no mesmo ponto");
    }

    return abs(destino.getDistanciaPartida() - distanciaPartida);
}

int Parada::getId() const {
    return id;
}

void Parada::setId(int id) {
    this->id = id;
}

bool Parada::eApos(Parada destino) const {
    return distanciaPartida < destino.getDistanciaPartida();
}

string Parada::getNome() const {
    return nome;
}

void Parada::setNome(string nome) {
    if (nome.empty()) {
        throw invalid_argument("Nome da parada nao pode ser nulo");
    }
    this->nome = nome;
}

double Parada::getDistanciaPartida() const {
    return distanciaPartida;
}

void Parada::setDistanciaPartida(double distanciaPartida) {
    if (distanciaPartida < 0) {
        throw invalid_argument("Distancia de partida nao pode ser negativa");
    }
    this->distanciaPartida = distanciaPartida;
}
