#include <string>

using namespace std;
#pragma once

class Parada {
    private:
        int id;
        string nome;
        double distanciaPartida;

    public:
        static int contadorId;

        // construtores
        Parada(string nome, double distanciaPartida);
        
        // outros metodos
        double calcularDistancia(Parada destino) const;
        bool eApos(Parada destino) const; // verifica se o destino está após o objeto

        // getters e setters
        int getId() const;
        void setId(int id);

        string getNome() const;
        void setNome(string nome);

        double getDistanciaPartida() const;
        void setDistanciaPartida(double distanciaPartida);
};