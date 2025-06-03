#include "Onibus.hpp"
#include <iostream>

Onibus::Onibus(string placa, int numAssentos, double velocidadeMedia){    
        if(placa.empty()) {
            throw invalid_argument("Placa não pode ser vazia");
        }
        if(numAssentos <= 0) {
            throw invalid_argument("Número de assentos livres precisa ser maior que zero");
        }
        if(velocidadeMedia <= 0) {
            throw invalid_argument("Velocidade média precisa ser maior que zero");
        }

        this->id = 0;
        this->placa = placa;
        this->numAssentos = numAssentos;
        this->velocidadeMedia = velocidadeMedia;
        this->valorKm = 5.0;
    }

Onibus::Onibus(string placa, int numAssentos, double velocidadeMedia, double valorKm){    
        if(placa.empty()) {
            throw invalid_argument("Placa não pode ser vazia");
        }
        if(numAssentos <= 0) {
            throw invalid_argument("Número de assentos precisa ser maior que zero");
        }
        if(velocidadeMedia <= 0) {
            throw invalid_argument("Velocidade média não pode ser negativa");
        }
        if(valorKm <= 0) {
            throw invalid_argument("Valor por km precisa ser maior que zero");
        }

        this->id = 0;
        this->placa = placa;
        this->numAssentos = numAssentos;
        this->velocidadeMedia = velocidadeMedia;
        this->valorKm = valorKm;
    }

    Onibus::Onibus(int id, string placa, int numAssentos, double velocidadeMedia, double valorKm){      
        if(id <= 0) {
            throw invalid_argument("Id precisa ser maior que zero");
        }
        if(placa.empty()) {
            throw invalid_argument("Placa não pode ser vazia");
        }
        if(numAssentos <= 0) {
            throw invalid_argument("Número de assentos precisa ser maior que zero");
        }
        if(velocidadeMedia <= 0) {
            throw invalid_argument("Velocidade média não pode ser negativa");
        }
        if(valorKm <= 0) {
            throw invalid_argument("Valor por km precisa ser maior que zero");
        }

        this->id = id;
        this->placa = placa;
        this->numAssentos = numAssentos;
        this->velocidadeMedia = velocidadeMedia;
        this->valorKm = valorKm;
    }

int Onibus::getId() const {
    return id;
}

string Onibus::getPlaca() const {
    return placa;
}

void Onibus::setPlaca(string placa) {
    if(placa.empty()) {
        throw invalid_argument("Placa não pode ser vazia");
    }
    this->placa = placa;
}

int Onibus::getNumAssentos() const {
    return numAssentos;
}

void Onibus::setNumAssentos(int numAssentos) {
    if(numAssentos <= 0) {
        throw invalid_argument("Número de assentos precisa ser maior que zero");
    }
    this->numAssentos = numAssentos;
}

double Onibus::getVelocidadeMedia() const {
    return velocidadeMedia;
}

void Onibus::setVelocidadeMedia(double velocidadeMedia) {
    if(velocidadeMedia <= 0) {
        throw invalid_argument("Velocidade média não pode ser negativa");
    }
    this->velocidadeMedia = velocidadeMedia;
}

double Onibus::getValorKm() const {
    return valorKm;
}

void Onibus::setValorKm(double valorKm) {
    if(valorKm <= 0) {
        throw invalid_argument("Valor por km precisa ser maior que zero");
    }
    this->valorKm = valorKm;
}
