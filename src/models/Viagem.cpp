#include "Viagem.hpp"
#include <iostream>


Viagem::Viagem(Data data) : data(data){
    origem = nullptr;
    destino = nullptr;
    onibus = nullptr;
}

Viagem::Viagem(Parada* origem, Parada* destino, Onibus* onibus, Data data) : data(data){
        if(origem == nullptr) {
            throw invalid_argument("Origem não pode ser nula");
        }
        if(destino == nullptr) {
            throw invalid_argument("Destino não pode ser nulo");
        }
        if(onibus == nullptr) {
            throw invalid_argument("Onibus não pode ser nulo");
        }

        this->origem = origem;
        this->destino = destino;
        this->onibus = onibus;
        this->numAssentosLivres = onibus->getNumAssentos();
}

bool Viagem::verificarDisponibilidade() {
    return numAssentosLivres > 0;
}

bool Viagem::incluiOTrecho(Parada* origem, Parada* destino) {
    return origem->getDistanciaPartida() >= this->origem->getDistanciaPartida() &&
           destino->getDistanciaPartida() <= this->destino->getDistanciaPartida();
}

double Viagem::calcularTempoViagemCompleta() {
    return origem->calcularDistancia(*destino) / onibus->getVelocidadeMedia();
}

double Viagem::calcularTempoTrecho(Parada* origem, Parada* destino) {
    return origem->calcularDistancia(*destino) / onibus->getVelocidadeMedia();
}

Parada* Viagem::getOrigem() {
    return origem;
}

void Viagem::setOrigem(Parada* origem) {
    if(origem == nullptr) {
        throw invalid_argument("Origem não pode ser nula");
    }
    this->origem = origem;
}

Parada* Viagem::getDestino() {
    return destino;
}

void Viagem::setDestino(Parada* destino) {
    if(destino == nullptr) {
        throw invalid_argument("Destino não pode ser nulo");
    }
    this->destino = destino;
}

Onibus* Viagem::getOnibus() {
    return onibus;
}

void Viagem::setOnibus(Onibus* onibus) {
    if(onibus == nullptr) {
        throw invalid_argument("Onibus não pode ser nulo");
    }
    this->onibus = onibus;
    this->numAssentosLivres = onibus->getNumAssentos();
}

void Viagem::setNumAssentosLivres(int numAssentosLivres) {
    this->numAssentosLivres = numAssentosLivres;
}

int Viagem::getNumAssentosLivres() {
    return numAssentosLivres;
}

void Viagem::ocuparAssento() {
    if(this->numAssentosLivres == 0) {
        throw invalid_argument("Não há assentos livres");
    }
    this->numAssentosLivres--;
}

void Viagem::desocuparAssento() {
    if(this->numAssentosLivres == this->onibus->getNumAssentos()){
        throw invalid_argument("Não há assentos ocupados");
    }
    this->numAssentosLivres++;
}

Data Viagem::getData() {
    return data;
}

void Viagem::setData(Data data) {
    this->data = data;
}
