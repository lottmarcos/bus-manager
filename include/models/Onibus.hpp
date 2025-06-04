#include <string>

using namespace std;
#pragma once

class Onibus {
    private:
        int id;
        string placa;
        int numAssentos;
        double velocidadeMedia;
        double valorKm;

    public:
    // construtores
    Onibus(string placa, int numAssentos, double velocidadeMedia); // valor padrão: 5,00
    Onibus(string placa, int numAssentos, double velocidadeMedia, double valorKm);
    Onibus(int id, string placa, int numAssentos, double velocidadeMedia, double valorKm);

    // getters e setters
    int getId() const;
    
    string getPlaca() const;
    void setPlaca(string placa);
    
    int getNumAssentos() const;
    void setNumAssentos(int numAssentos);
    
    double getVelocidadeMedia() const;
    void setVelocidadeMedia(double velocidadeMedia);
    
    double getValorKm() const;
    void setValorKm(double valorKm);
};
