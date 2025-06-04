
#include <iostream>

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    // construtores
    Data(int dia, int mes, int ano);

    // getteres e setteres
    int getDia();
    void setDia(int dia);

    int getMes();
    void setMes(int mes);

    int getAno();
    void setAno(int ano);

    // sobrecarga de operadores
    bool operator==(const Data &other) const;

    bool operator!=(const Data &other) const;

    bool operator<(const Data &other) const;

    bool operator<=(const Data &other) const;

    bool operator>(const Data &other) const;

    bool operator>=(const Data &other) const;

    friend ostream &operator<<(ostream &out, const Data &data) ;

    friend istream &operator>>(istream &in, Data &data);
};