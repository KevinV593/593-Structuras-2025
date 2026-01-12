#ifndef VALIDACION_HPP
#define VALIDACION_HPP

#include <string>

class Validacion {
public:
    static int ingresarEntero(std::string mensaje);

private:
    static bool validarEntero(std::string numero);
};

#endif