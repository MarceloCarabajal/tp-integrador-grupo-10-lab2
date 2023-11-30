#ifndef STATUSBAR_INCLUDED
#define STATUSBAR_INCLUDED

#include <iostream>

/**
 * @class StatusBar
 * @brief Clase que representa una barra de estado.
 *
 * La clase StatusBar se utiliza para mostrar y actualizar el estado de ciertos
 * datos, como la cantidad de vacunas pendientes, la cantidad de aplicaciones
 * pendientes y el nombre del veterinario.
 */
class StatusBar {
private:
    static int _pendingVacc;      /**< Cantidad de vacunas pendientes. */
    static int _pendingApps;      /**< Cantidad de aplicaciones pendientes. */
    static std::string _veteName; /**< Nombre de la veterinaria. */

public:
    /**
     * @brief Actualiza el estado de la barra de estado.
     *
     * Este método se utiliza para actualizar los datos de la barra de estado,
     * como la cantidad de vacunas pendientes, la cantidad de aplicaciones
     * pendientes y el nombre de la veterinaria.
     */
    static void update();

    /**
     * @brief Muestra la barra de estado.
     *
     * Este método se utiliza para mostrar la barra de estado en la interfaz de
     * usuario.
     */
    static void show();
};

#endif /* STATUSBAR_INCLUDED */
