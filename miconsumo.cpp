/*
 * =====================================================================
 * PROGRAMA: MiConsumo - cuanto me cuesta la energia de mi casa
 * CURSO:    Programacion Orientada a Objetos - IU Digital - 2026-2
 * =====================================================================
 *
 * ENUNCIADO:
 * Con El Nino 2026 la energia subio. Este programa calcula cuanto
 * consume y cuanto cuesta cada equipo de una casa durante una semana:
 *   1. Clase Equipo: nombre, potencia y un VECTOR con las horas de uso
 *      de cada dia de la semana.
 *   2. Clase Hogar: tiene un VECTOR DE OBJETOS Equipo y una MATRIZ con
 *      el consumo en kWh de cada equipo (columna) en cada dia (fila).
 *   3. Reporte: consumo y costo por dia, por equipo, dia mas caro,
 *      equipo que mas gasta y proyeccion mensual.
 *
 * AMPLIACION (evidencia de aprendizaje):
 *   - Equipo: horasSemana(), diaDeMayorUso(), reducirHoras()
 *   - Hogar : diaMasBarato(), porcentajeEquipo(), promedioDiario(),
 *             simularAhorro(), verEquipo()
 *   - Menu  : opcion 6 carga MI casa; opcion 7 simula un ahorro;
 *             opcion 8 muestra un equipo
 *
 * NOTA: los mensajes no llevan tildes ni enie porque la consola de
 * Windows puede mostrarlos mal.
 * =====================================================================
 */

// ---------------------------------------------------------------------
// LIBRERIAS (#include): codigo ya escrito que reutilizamos
// ---------------------------------------------------------------------
#include <iostream>   // cout (escribir en pantalla) y cin (leer del teclado)
#include <string>     // el tipo string, para guardar textos
#include <iomanip>    // setw (ancho de columna) y setprecision (decimales):
                      // sirven para que la tabla quede alineada

// Sin esta linea habria que escribir std::cout, std::string, etc.
using namespace std;

// ---------------------------------------------------------------------
// CONSTANTES: tamanos de los vectores y de la matriz
// const = su valor NO puede cambiar mientras el programa corre.
// Si se cambia aqui, cambia en todo el programa.
// ---------------------------------------------------------------------
const int DIAS = 7;          // filas de la matriz: lunes a domingo
const int MAX_EQUIPOS = 4;   // columnas de la matriz: equipos de la casa

// VECTOR de textos con el nombre de cada dia.
// Sus posiciones (indices) van de 0 a 6: NOMBRE_DIA[0] es "Lun".
const string NOMBRE_DIA[DIAS] = {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"};


// =====================================================================
// CLASE Equipo: un aparato electrico de la casa
// ---------------------------------------------------------------------
// Una CLASE es un MOLDE: define que DATOS (atributos) y que ACCIONES
// (metodos) tendra cada objeto que se cree a partir de ella.
// =====================================================================
class Equipo {

// private: estos atributos solo se pueden usar DENTRO de la clase.
// Desde el main no se pueden tocar directamente (ENCAPSULAMIENTO).
private:
    string nombre;        // Ej.: "Ducha electrica"
    float potenciaW;      // Potencia en vatios (W), tomada de la etiqueta
    float horas[DIAS];    // VECTOR de 7 casillas: horas de uso de cada dia
                          // horas[0] = lunes ... horas[6] = domingo

// public: lo que SI se puede usar desde afuera (desde el main o desde
// otra clase). Son las "puertas" del objeto.
public:

    // -----------------------------------------------------------------
    // CONSTRUCTOR POR DEFECTO (sin parametros)
    // Se ejecuta al crear un Equipo sin datos. Lo EXIGE el vector de
    // objetos de la clase Hogar, que crea 4 equipos "vacios" al inicio.
    // -----------------------------------------------------------------
    Equipo() {
        nombre = "";                    // sin nombre
        potenciaW = 0;                  // sin potencia
        for (int d = 0; d < DIAS; d++) {
            horas[d] = 0;               // cada casilla del vector en cero
        }
    }

    // -----------------------------------------------------------------
    // CONSTRUCTOR CON PARAMETROS
    // n = nombre, p = potencia en W, h = vector con las 7 horas.
    // const float h[DIAS]: recibe un vector y promete NO modificarlo.
    // -----------------------------------------------------------------
    Equipo(string n, float p, const float h[DIAS]) {
        nombre = n;                     // guarda el nombre recibido
        potenciaW = p;                  // guarda la potencia recibida
        for (int d = 0; d < DIAS; d++) {
            horas[d] = h[d];            // copia el vector casilla por casilla
        }
    }

    // GETTER: devuelve el nombre (el atributo es privado, por eso
    // se necesita un metodo publico para leerlo desde afuera)
    string getNombre() {
        return nombre;
    }

    // Muestra el nombre, la potencia y las 7 horas del vector
    void mostrar() {
        cout << nombre << " (" << potenciaW << " W) - horas:";
        for (int d = 0; d < DIAS; d++) {
            cout << " " << horas[d];    // escribe cada casilla del vector
        }
        cout << endl;                   // salto de linea al final
    }
    // -----------------------------------------------------------------
    // Energia de UN dia en kWh = potencia (W) x horas / 1000
    // d es el INDICE del dia: 0 = lunes, 6 = domingo.
    // Se divide entre 1000 porque 1 kW = 1000 W.
    // -----------------------------------------------------------------
    float energiaDia(int d) {
        return potenciaW * horas[d] / 1000;
    }

    // -----------------------------------------------------------------
    // Energia de la SEMANA: recorre el vector y ACUMULA
    // -----------------------------------------------------------------
    float energiaSemana() {
        float total = 0;                // ACUMULADOR: empieza en cero
        for (int d = 0; d < DIAS; d++) {
            total += energiaDia(d);     // suma la energia de cada dia
        }
        return total;                   // entrega el total de la semana
    }

    // -----------------------------------------------------------------
    // NUEVO: total de HORAS de uso de la semana (suma del vector horas)
    // -----------------------------------------------------------------
    float horasSemana() {
        float total = 0;                // ACUMULADOR en cero
        for (int d = 0; d < DIAS; d++) {
            total += horas[d];          // suma las horas de cada dia
        }
        return total;
    }

    // -----------------------------------------------------------------
    // NUEVO: INDICE del dia en que el equipo mas se uso (busqueda del
    // mayor en un vector: supone que es el dia 0 y compara con los demas)
    // Si hay empate, devuelve el primer dia que alcanzo ese maximo.
    // -----------------------------------------------------------------
    int diaDeMayorUso() {
        int mayor = 0;                  // supone: lunes es el mayor
        for (int d = 1; d < DIAS; d++) {
            if (horas[d] > horas[mayor]) {
                mayor = d;              // encontro un dia con mas horas
            }
        }
        return mayor;
    }

    // -----------------------------------------------------------------
    // NUEVO: reduce en "porcentaje" las horas de TODOS los dias.
    // Ejemplo: porcentaje = 20 -> cada dia queda con el 80 % de sus horas
    // (horas x (100 - 20) / 100).
    // -----------------------------------------------------------------
    void reducirHoras(float porcentaje) {
        for (int d = 0; d < DIAS; d++) {
            horas[d] = horas[d] * (100 - porcentaje) / 100;
        }
    }

};  // <- la clase termina en llave y PUNTO Y COMA


// =====================================================================
// CLASE Hogar: la casa, con sus equipos y la matriz de consumo
// ---------------------------------------------------------------------
// COMPOSICION: un Hogar TIENE varios objetos Equipo adentro.
// =====================================================================
class Hogar {
private:
    string nombre;                         // Ej.: "Casa de ejemplo"
    float tarifa;                          // COP por kWh (de la factura)
    Equipo equipos[MAX_EQUIPOS];           // VECTOR DE OBJETOS: 4 casillas,
                                           // cada una es un Equipo completo
    int cantidad;                          // cuantas casillas estan ocupadas
    float consumo[DIAS][MAX_EQUIPOS];      // MATRIZ 7 x 4 con kWh:
                                           // consumo[dia][equipo]

public:
    // CONSTRUCTOR: recibe el nombre de la casa y la tarifa
    Hogar(string n, float t) {
        nombre = n;
        tarifa = t;
        cantidad = 0;                      // la casa empieza sin equipos
    }

    // -----------------------------------------------------------------
    // Cambia el nombre y la tarifa (los digita el usuario en el menu)
    // -----------------------------------------------------------------
    void setDatos(string n, float t) {
        nombre = n;
        tarifa = t;
    }

    // GETTER: cuantos equipos hay guardados en el vector
    int getCantidad() {
        return cantidad;
    }

    // Deja el vector de equipos vacio (para volver a empezar)
    void vaciar() {
        cantidad = 0;
    }

    // Recorre el VECTOR DE OBJETOS y le pide a cada equipo mostrarse
    void mostrarEquipos() {
        cout << defaultfloat << setprecision(6);  // formato normal: quita el que dejan
                                           // mostrarMatriz() y reporte()
        if (cantidad == 0) {
            cout << "Todavia no hay equipos" << endl;
        }
        for (int e = 0; e < cantidad; e++) {
            cout << e << ". ";             // numero de la casilla del vector
            equipos[e].mostrar();          // cada objeto se muestra solo
        }
    }

    // -----------------------------------------------------------------
    // Guarda un equipo en la siguiente casilla libre del vector
    // -----------------------------------------------------------------
    void agregarEquipo(Equipo e) {
        if (cantidad < MAX_EQUIPOS) {      // si todavia hay espacio...
            equipos[cantidad] = e;         // ...lo guarda en la casilla libre
            cantidad++;                    // ...y cuenta un equipo mas
        } else {
            cout << "No caben mas equipos" << endl;  // vector lleno
        }
    }

    // -----------------------------------------------------------------
    // Llena la matriz con CICLOS ANIDADOS:
    // el for de afuera recorre las FILAS (dias) y el de adentro las
    // COLUMNAS (equipos). Cada casilla pide la energia a su objeto Equipo.
    // -----------------------------------------------------------------
    void calcularMatriz() {
        for (int d = 0; d < DIAS; d++) {            // cada fila (dia)
            for (int e = 0; e < cantidad; e++) {    // cada columna (equipo)
                consumo[d][e] = equipos[e].energiaDia(d);
            }
        }
    }

    // -----------------------------------------------------------------
    // Suma de una FILA: se fija el dia d y se recorren las columnas.
    // Resultado: todo lo que consumio la casa ese dia.
    // -----------------------------------------------------------------
    float totalDia(int d) {
        float total = 0;
        for (int e = 0; e < cantidad; e++) {
            total += consumo[d][e];
        }
        return total;
    }

    // -----------------------------------------------------------------
    // Suma de una COLUMNA: se fija el equipo e y se recorren las filas.
    // Resultado: lo que consumio ese equipo en la semana.
    // -----------------------------------------------------------------
    float totalEquipo(int e) {
        float total = 0;
        for (int d = 0; d < DIAS; d++) {
            total += consumo[d][e];
        }
        return total;
    }

    // Suma de TODA la matriz: suma los totales de los 7 dias
    float totalSemana() {
        float total = 0;
        for (int d = 0; d < DIAS; d++) {
            total += totalDia(d);
        }
        return total;
    }

    // -----------------------------------------------------------------
    // Muestra la matriz con el total de cada fila y de cada columna.
    // fixed + setprecision(2): siempre 2 decimales.
    // setw(n): reserva n espacios para el siguiente dato (alinea).
    // -----------------------------------------------------------------
    void mostrarMatriz() {
        cout << fixed << setprecision(2);
        cout << endl << "Consumo en kWh (filas = dias, columnas = equipos)" << endl;

        // Encabezado: "Dia", el nombre de cada equipo y "Total"
        cout << setw(5) << "Dia";
        for (int e = 0; e < cantidad; e++) {
            cout << setw(18) << equipos[e].getNombre();
        }
        cout << setw(10) << "Total" << endl;

        // Una linea por cada fila (dia) de la matriz
        for (int d = 0; d < DIAS; d++) {
            cout << setw(5) << NOMBRE_DIA[d];          // nombre del dia
            for (int e = 0; e < cantidad; e++) {
                cout << setw(18) << consumo[d][e];     // cada casilla
            }
            cout << setw(10) << totalDia(d) << endl;   // suma de la fila
        }

        // Ultima linea: la suma de cada columna (equipo)
        cout << setw(5) << "Total";
        for (int e = 0; e < cantidad; e++) {
            cout << setw(18) << totalEquipo(e);
        }
        cout << setw(10) << totalSemana() << endl;     // total de la matriz
    }

    // -----------------------------------------------------------------
    // Busca la fila con la MAYOR suma.
    // Supone que el mayor es el dia 0 y lo compara con los demas.
    // Devuelve el INDICE del dia, no el valor.
    // -----------------------------------------------------------------
    int diaMasCaro() {
        int mayor = 0;                             // supone: lunes es el mayor
        for (int d = 1; d < DIAS; d++) {           // compara desde el martes
            if (totalDia(d) > totalDia(mayor)) {
                mayor = d;                         // encontro uno mayor
            }
        }
        return mayor;
    }

    // Busca la columna con la MAYOR suma (mismo metodo que diaMasCaro)
    int equipoQueMasGasta() {
        int mayor = 0;
        for (int e = 1; e < cantidad; e++) {
            if (totalEquipo(e) > totalEquipo(mayor)) {
                mayor = e;
            }
        }
        return mayor;
    }

    // -----------------------------------------------------------------
    // NUEVO: busca la fila con la MENOR suma (dia de menor consumo).
    // Es igual a diaMasCaro(), pero con el signo de comparacion al reves.
    // -----------------------------------------------------------------
    int diaMasBarato() {
        int menor = 0;                             // supone: lunes es el menor
        for (int d = 1; d < DIAS; d++) {
            if (totalDia(d) < totalDia(menor)) {
                menor = d;                         // encontro uno menor
            }
        }
        return menor;
    }

    // -----------------------------------------------------------------
    // NUEVO: que % del consumo de la semana es del equipo e (columna e).
    // porcentaje = (total de la columna / total de la matriz) x 100
    // -----------------------------------------------------------------
    float porcentajeEquipo(int e) {
        float total = totalSemana();
        if (total == 0) {                          // evita dividir entre cero
            return 0;
        }
        return totalEquipo(e) / total * 100;
    }

    // -----------------------------------------------------------------
    // NUEVO: consumo promedio por dia en kWh (total de la semana / 7)
    // -----------------------------------------------------------------
    float promedioDiario() {
        return totalSemana() / DIAS;
    }

    // -----------------------------------------------------------------
    // NUEVO: SIMULA que pasaria si se usa menos el equipo e.
    // 1. calcula el costo ANTES  2. reduce las horas del equipo
    // 3. recalcula la matriz     4. calcula el costo DESPUES
    // 5. muestra la diferencia (ahorro) en pesos.
    // Al final RESTAURA las horas originales (usando una copia del
    // equipo), para que la simulacion no dane los datos reales de la casa
    // y se puedan probar varias simulaciones seguidas.
    // -----------------------------------------------------------------
    void simularAhorro(int e, float porcentaje) {
        calcularMatriz();                          // matriz con los datos reales
        float costoAntes = totalSemana() * tarifa;

        Equipo respaldo = equipos[e];              // copia del equipo original
        equipos[e].reducirHoras(porcentaje);       // reduce las horas del equipo
        calcularMatriz();                          // vuelve a llenar la matriz
        float costoDespues = totalSemana() * tarifa;

        equipos[e] = respaldo;                     // restaura las horas reales
        calcularMatriz();                          // y la matriz real

        cout << fixed << setprecision(0);
        cout << endl << "===== SIMULACION: " << equipos[e].getNombre()
             << " con " << porcentaje << "% menos de uso =====" << endl;
        cout << "Costo semanal ANTES:   " << costoAntes << " COP" << endl;
        cout << "Costo semanal DESPUES: " << costoDespues << " COP" << endl;
        cout << "Ahorro en la semana:   " << costoAntes - costoDespues << " COP" << endl;
        cout << "Ahorro proyectado en el mes (x 4): "
             << (costoAntes - costoDespues) * 4 << " COP" << endl;
    }

    // -----------------------------------------------------------------
    // NUEVO: muestra los datos de un equipo (opcion 8 del menu).
    // Usa horasSemana() y diaDeMayorUso() de Equipo y porcentajeEquipo().
    // -----------------------------------------------------------------
    void verEquipo(int e) {
        calcularMatriz();
        cout << fixed << setprecision(1);
        cout << endl << "===== " << equipos[e].getNombre() << " =====" << endl;
        cout << "Horas de uso en la semana: " << equipos[e].horasSemana() << " h" << endl;
        cout << "Dia de mayor uso: " << NOMBRE_DIA[equipos[e].diaDeMayorUso()] << endl;
        cout << "Porcentaje del consumo total: " << porcentajeEquipo(e) << " %" << endl;
    }

    // -----------------------------------------------------------------
    // Reporte: conclusiones a partir de la matriz.
    // Costo = kWh x tarifa.
    // -----------------------------------------------------------------
    void reporte() {
        int dia = diaMasCaro();                  // indice de la fila mayor
        int barato = diaMasBarato();             // indice de la fila menor
        int equipo = equipoQueMasGasta();        // indice de la columna mayor
        float costoSemana = totalSemana() * tarifa;

        cout << fixed << setprecision(0);        // pesos: sin decimales
        cout << endl << "===== REPORTE: " << nombre << " =====" << endl;
        cout << "Tarifa: " << tarifa << " COP/kWh" << endl;
        cout << "Dia mas caro: " << NOMBRE_DIA[dia]
             << " (" << totalDia(dia) * tarifa << " COP)" << endl;
        cout << "Dia mas barato: " << NOMBRE_DIA[barato]
             << " (" << totalDia(barato) * tarifa << " COP)" << endl;
        cout << "Equipo que mas gasta: " << equipos[equipo].getNombre()
             << " (" << totalEquipo(equipo) * tarifa << " COP en la semana)" << endl;
        cout << "Costo de la semana: " << costoSemana << " COP" << endl;
        cout << "Proyeccion del mes (x 4): " << costoSemana * 4 << " COP" << endl;

        // NUEVO: promedio diario, proyeccion en kWh y % de cada equipo
        cout << fixed << setprecision(2);
        cout << "Promedio diario: " << promedioDiario() << " kWh" << endl;
        cout << "Proyeccion del mes en kWh (x 4): " << totalSemana() * 4 << " kWh" << endl;
        cout << "Porcentaje del consumo por equipo:" << endl;
        cout << fixed << setprecision(1);
        for (int e = 0; e < cantidad; e++) {
            cout << "  - " << equipos[e].getNombre() << ": "
                 << porcentajeEquipo(e) << " %" << endl;
        }
    }
};  // <- fin de la clase Hogar


// =====================================================================
// PROGRAMA PRINCIPAL (paso 9: menu con entrada de datos)
// =====================================================================
int main() {
    // Crea el OBJETO casa vacio: el nombre y la tarifa se digitan en el menu
    Hogar casa("Mi casa", 0);
    int opcion;

    // do-while: el menu se repite HASTA que el usuario elija 0
    do {
        cout << endl << "===== MiConsumo =====" << endl;
        cout << "1. Datos de la casa (nombre y tarifa)" << endl;
        cout << "2. Agregar un equipo" << endl;
        cout << "3. Ver los equipos" << endl;
        cout << "4. Ver la matriz de consumo" << endl;
        cout << "5. Ver el reporte" << endl;
        cout << "6. Cargar MI casa (datos reales)" << endl;
        cout << "7. Simular un ahorro" << endl;
        cout << "8. Ver un equipo" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        if (cin.fail()) {                          // si no digito un numero
            cin.clear();                           // limpia el error de cin
            cin.ignore(1000, '\n');                // descarta lo digitado
            opcion = -1;                           // cae en "Opcion no valida"
        }

        // switch: ejecuta el case que coincide con la opcion digitada
        switch (opcion) {

        case 1: {                                  // llaves: variables propias del case
            string nombre;
            float tarifa;
            cout << "Nombre de la casa: ";
            getline(cin >> ws, nombre);            // lee el texto completo, con espacios
            do {                                   // VALIDACION: repite si es invalida
                cout << "Tarifa de su factura (COP por kWh): ";
                cin >> tarifa;
                if (tarifa <= 0) cout << "Dato invalido: la tarifa debe ser mayor que 0" << endl;
            } while (tarifa <= 0);
            casa.setDatos(nombre, tarifa);
            cout << "Datos guardados" << endl;
            break;                                 // sale del switch
        }

        case 2: {
            if (casa.getCantidad() == MAX_EQUIPOS) {
                cout << "Ya hay " << MAX_EQUIPOS << " equipos: no caben mas" << endl;
                break;
            }
            string nombre;
            float potencia;
            float horas[DIAS];                     // VECTOR que llena el usuario
            cout << "Nombre del equipo: ";
            getline(cin >> ws, nombre);
            do {
                cout << "Potencia en vatios (W), segun la etiqueta: ";
                cin >> potencia;
                if (potencia <= 0) cout << "Dato invalido: la potencia debe ser mayor que 0" << endl;
            } while (potencia <= 0);
            // RECORRER el vector para LEER cada casilla desde el teclado
            for (int d = 0; d < DIAS; d++) {
                do {
                    cout << "Horas de uso el " << NOMBRE_DIA[d] << " (0 a 24): ";
                    cin >> horas[d];
                    if (horas[d] < 0 || horas[d] > 24) cout << "Dato invalido: las horas deben estar entre 0 y 24" << endl;
                } while (horas[d] < 0 || horas[d] > 24);
            }
            // Crea el objeto con los datos digitados y lo guarda en la casa
            casa.agregarEquipo(Equipo(nombre, potencia, horas));
            cout << "Equipo agregado" << endl;
            break;
        }

        case 3:
            casa.mostrarEquipos();
            break;

        case 4:
            if (casa.getCantidad() == 0) {
                cout << "Primero agregue equipos (opcion 2 o 6)" << endl;
            } else {
                casa.calcularMatriz();             // llena la matriz con los datos actuales
                casa.mostrarMatriz();
            }
            break;

        case 5:
            if (casa.getCantidad() == 0) {
                cout << "Primero agregue equipos (opcion 2 o 6)" << endl;
            } else {
                casa.calcularMatriz();
                casa.reporte();
            }
            break;

        case 6: {
            // MI casa: potencias de las etiquetas y horas de uso por dia
            // (lunes a domingo). Tarifa: "Valor kWh aplicado" de la factura Enel.
            // Ducha:     110 V x 36 A = 3960 W (etiqueta, 3,96 kW)
            // Nevera:    Mabe 278 L No Frost, 1,2 kWh/dia / 24 h = 50 W promedio
            //            (fuente: ficha del fabricante, 32 a 38 kWh/mes)
            // Televisor: Caixun 32" LED, consumo de energia 38 W (etiqueta)
            // Lavadora:  Mabe semiautomatica, etiqueta: 1,21 kWh/mes en 14 ciclos
            //            = 0,0864 kWh por ciclo -> 86,4 W x 1 "hora" por ciclo
            //            (la lavadora se usa 1 hora = 1 ciclo, una vez por semana)
            float hDucha[DIAS]     = {1, 1.5, 1, 1.5, 1, 2, 2};      // 1 a 2 horas por dia
            float hNevera[DIAS]    = {24, 24, 24, 24, 24, 24, 24};
            float hTelevisor[DIAS] = {4, 0, 5, 0, 6, 6, 6};      // 2 dias de descanso en semana
            float hLavadora[DIAS]  = {0, 0, 0, 0, 0, 1, 0};      // 1 hora, una vez por semana
            casa.vaciar();
            casa.setDatos("Mi casa - Bogota", 875.05);
            casa.agregarEquipo(Equipo("Ducha electrica", 3960, hDucha));
            casa.agregarEquipo(Equipo("Nevera Mabe 278L", 50, hNevera));
            casa.agregarEquipo(Equipo("Televisor 32 LED", 38, hTelevisor));
            casa.agregarEquipo(Equipo("Lavadora Mabe", 86.4, hLavadora));
            cout << "Mi casa cargada: 4 equipos" << endl;
            break;
        }

        case 7: {
            if (casa.getCantidad() == 0) {
                cout << "Primero agregue equipos (opcion 2 o 6)" << endl;
                break;
            }
            int e;
            float porcentaje;
            casa.mostrarEquipos();                 // para que vea el numero de cada equipo
            cout << "Numero del equipo a simular: ";
            cin >> e;
            if (cin.fail() || e < 0 || e >= casa.getCantidad()) {   // el equipo debe existir
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Equipo no valido: debe estar entre 0 y "
                     << casa.getCantidad() - 1 << endl;
                break;
            }
            cout << "Porcentaje de reduccion (1 a 100): ";
            cin >> porcentaje;
            if (cin.fail() || porcentaje < 1 || porcentaje > 100) { // rango valido
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Porcentaje no valido: debe estar entre 1 y 100" << endl;
                break;
            }
            casa.simularAhorro(e, porcentaje);
            break;
        }

        case 8: {
            if (casa.getCantidad() == 0) {
                cout << "Primero agregue equipos (opcion 2 o 6)" << endl;
                break;
            }
            int e;
            casa.mostrarEquipos();
            cout << "Numero del equipo a ver: ";
            cin >> e;
            if (cin.fail() || e < 0 || e >= casa.getCantidad()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Equipo no valido: debe estar entre 0 y "
                     << casa.getCantidad() - 1 << endl;
                break;
            }
            casa.verEquipo(e);
            break;
        }

        case 0:
            cout << "Hasta luego" << endl;
            break;

        default:                                   // cualquier otro numero
            cout << "Opcion no valida" << endl;
        }

    } while (opcion != 0);

    return 0;                // 0 = el programa termino sin errores
}
