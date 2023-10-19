#include "Person.h"

/**
 * @brief Establece el nombre de la persona.
 * @param name El nombre de la persona.
 */
void Person::setName(std::string name) { _name = name; }

/**
 * @brief Obtiene el nombre de la persona.
 * @return El nombre de la persona.
 */
std::string Person::getName() { return _name; }

/**
 * @brief Establece el apellido de la persona.
 * @param lastname El apellido de la persona.
 */
void Person::setLastname(std::string lastname) { _lastname = lastname; }

/**
 * @brief Obtiene el apellido de la persona.
 * @return El apellido de la persona.
 */
std::string Person::getLastname() { return _lastname; }
