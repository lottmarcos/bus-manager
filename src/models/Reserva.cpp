#include "Reserva.hpp"
#include <iostream>

Reserva::Reserva(Viagem *viagem, string cpf, Parada* origem, Parada* destino)
    : viagem(viagem), cpf(cpf), origem(origem), destino(destino) {
        if(viagem == nullptr) {
            throw invalid_argument("Viagem não pode ser nula");
        }
        if(cpf.empty()) {
            throw invalid_argument("CPF não pode ser vazio");
        }
        if(origem == nullptr) {
            throw invalid_argument("Origem não pode ser nula");
        }
        if(destino == nullptr) {
            throw invalid_argument("Destino não pode ser nulo");
        }

        this->valorPassagem = origem->calcularDistancia(*destino) * viagem->getOnibus()->getValorKm();
        this->ativa = true;
        this->viagem->ocuparAssento();
}

void Reserva::cancelarReserva() {
    this->ativa = false;
    this->viagem->desocuparAssento();
}


Viagem* Reserva::getViagem() {
    return viagem;
}

string Reserva::getCPF() {
    return cpf;
}

double Reserva::getValorPassagem() {
    return valorPassagem;
}

Parada* Reserva::getOrigem() {
    return origem;
}

Parada* Reserva::getDestino() {
    return destino;
}

Data Reserva::getData() {
    return viagem->getData();
}

bool Reserva::estaAtiva() {
    return ativa;
}
