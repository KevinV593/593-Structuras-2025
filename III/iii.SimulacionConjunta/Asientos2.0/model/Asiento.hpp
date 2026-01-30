#ifndef ASIENTO_HPP
#define ASIENTO_HPP

class Asiento {
private:
    int id;
    int estado; // 0: Libre, 1: Ocupado

public:
    Asiento(int id) : id(id), estado(0) {}
    
    // Getters y Setters
    int getId() const { return id; }
    int getEstado() const { return estado; }
    void setEstado(int e) { estado = e; }
};

#endif