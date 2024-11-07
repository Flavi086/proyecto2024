#pragma once
#ifndef DIA_H
#define DIA_H

#include <vector>
#include <iostream>


class Dia {
public:
    virtual ~Dia() {}
    virtual void mostrarEvento() const = 0; 
};


class DiaNormal : public Dia {
public:
    void mostrarEvento() const override {
        std::cout << "Día normal: Todo sigue igual.\n";
    }
};


class DiaEspecial : public Dia {
public:
    void mostrarEvento() const override {
        std::cout << "Día especial: ¡Un evento importante ha ocurrido!\n";
    }
};


class ContadorDias {
private:
    std::vector<Dia*> dias; 
    int diaActual;

public:
    ContadorDias() : diaActual(0) {}

    ~ContadorDias() {
        
        for (Dia* dia : dias) {
            delete dia;
        }
    }

    void agregarDia(Dia* dia) {
        dias.push_back(dia);
    }

    void avanzarDia() {
        if (diaActual < dias.size()) {
            dias[diaActual]->mostrarEvento();
            diaActual++;
        }
        else {
            std::cout << "El juego ha terminado. No hay más días.\n";
        }
    }

    int getDiaActual() const {
        return diaActual;
    }

    bool juegoTerminado() const {
        return diaActual >= dias.size();
    }
};

#endif // DIA_H
