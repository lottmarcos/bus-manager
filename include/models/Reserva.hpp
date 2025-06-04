#include "Viagem.hpp"

class Reserva {
    private:
        Viagem *viagem;
        string cpf;
        double valorPassagem;
        Parada *origem;
        Parada *destino;
        bool ativa;

    public:
        // construtores
        Reserva(Viagem *viagem, string cpf, Parada* origem, Parada* destino);
        
        // outros metdos 
        void cancelarReserva();
        
        // getteres e setteres
        Viagem* getViagem();

        string getCPF();

        double getValorPassagem();

        Parada* getOrigem();

        Parada* getDestino();

        Data getData();

        bool estaAtiva();
};
