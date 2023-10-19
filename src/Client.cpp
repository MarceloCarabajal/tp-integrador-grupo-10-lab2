#include "Client.h"

/**
 * @brief Establece la dirección del cliente.
 * @param address La dirección del cliente.
 */
void Client::setAddress(std::string address) { _address = address; }

/**
 * @brief Obtiene la dirección del cliente.
 * @return La dirección del cliente.
 */
std::string Client::getAddress() { return _address; }

/**
 * @brief Establece el teléfono del cliente.
 * @param phone El número de teléfono del cliente.
 */
void Client::setPhone(std::string phone) { _phone = phone; }

/**
 * @brief Obtiene el teléfono del cliente.
 * @return El número de teléfono del cliente.
 */
std::string Client::getPhone() { return _phone; }

/**
 * @brief Establece el correo electrónico del cliente.
 * @param email El correo electrónico del cliente.
 */
void Client::setEmail(std::string email) { _email = email; }

/**
 * @brief Obtiene el correo electrónico del cliente.
 * @return El correo electrónico del cliente.
 */
std::string Client::getEmail() { return _email; }
