#include <iostream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

// Estados posibles de la máquina de Moore
enum Estado {
    COMENTARIO,
    NOMBRE,
    TELEFONO,
    CORREO,
    NIT,
    FECHA,
    HORA,
    FINAL
};

// Función para validar el nombre (formato Nombre Apellido)
bool esNombreValido(const string& input) {
    return regex_match(input, regex("[A-Z][a-z]+\\s[A-Z][a-z]+"));
}

// Función para validar los comentarios (puede contener letras, espacios, comas o puntos)
bool esComentarioValido(const string& input) {
    return regex_match(input, regex("([A-Z]+|[a-z]+|\\s|,|\\.+[a-z])*"));
}

// Función para procesar el número de teléfono (solo dígitos)
bool esTelefonoValido(const string& input) {
    return regex_match(input, regex("[0-9]{8}"));
}

// Función para validar el correo electrónico
bool esCorreoValido(const string& input) {
    return regex_match(input, regex("[a-z]+@[a-z]+(\\.[a-z]+)+"));
}

// Función para validar el NIT 
bool esNitValido(const string& input) {
    return regex_match(input, regex("[0-9]{8}-[0-9]"));
}

// Función para validar la fecha (formato DD/MM/YY)
bool esFechaValida(const string& input) {
    return regex_match(input, regex("\\d{2}/\\d{2}/\\d{2}"));
}

// Función para validar la hora (formato HH:MM AM/PM)
bool esHoraValida(const string& input) {
    return regex_match(input, regex("[0-1][0-9]:[0-5][0-9](AM|PM)"));
}

// Procesar archivo separado por "&" (simulando un archivo de entrada)
void procesarEntrada(const string& datos) {
    Estado estado = NOMBRE; // Estado inicial
    stringstream ss(datos);
    string token;

    // Separar los datos por el delimitador '&'
    while (getline(ss, token, '&')) {
        switch (estado) {
        case NOMBRE:
            if (esNombreValido(token)) {
                cout << "Nombre: " << token << endl;
                estado = COMENTARIO;
            }
            else {
                cout << "Nombre invalido: " << token << endl;
                estado = FINAL;
            }
            break;

        case COMENTARIO:
            if (esComentarioValido(token)) {
                cout << "Comentario: " << token << endl;
                estado = TELEFONO;
            }
            else {
                cout << "Comentario invalido: " << token << endl;
                estado = FINAL;
            }
            break;

        case TELEFONO:
            if (esTelefonoValido(token)) {
                cout << "Telefono: " << token << endl;
                estado = CORREO;
            }
            else {
                cout << "Telefono invalido: " << token << endl;
                estado = FINAL;
            }
            break;

        case CORREO:
            if (esCorreoValido(token)) {
                cout << "Correo electronico: " << token << endl;
                estado = NIT;
            }
            else {
                cout << "Correo invalido: " << token << endl;
                estado = FINAL;
            }
            break;

        case NIT:
            if (esNitValido(token)) {
                cout << "NIT: " << token << endl;
                estado = FECHA;
            }
            else {
                cout << "NIT invalido: " << token << endl;
                estado = FINAL;
            }
            break;

        case FECHA:
            if (esFechaValida(token)) {
                cout << "Fecha: " << token << endl;
                estado = HORA;
            }
            else {
                cout << "Fecha invalida: " << token << endl;
                estado = FINAL;
            }
            break;

        case HORA:
            if (esHoraValida(token)) {
                cout << "Hora: " << token << endl;
                estado = FINAL;
            }
            else {
                cout << "Hora invalida: " << token << endl;
            }
            break;

        case FINAL:
            cout << "Procesamiento completado." << endl;
            return;
        }
    }
}

int main() {
    // Simulación de datos de entrada separados por '&'
    string entrada = "Yasmely Aldana&Hola como estas&33895645&yasmelysfarinas@gmail.com&89547625-9&09/09/24&14:30AM";

    // Procesar la entrada
    procesarEntrada(entrada);

    return 0;
}

