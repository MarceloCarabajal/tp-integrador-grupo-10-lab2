#pragma once
#include <iostream>

void printLogo();
bool sendEmail(std::string to, std::string subject, std::string body,
               bool isHTML = false);
void coutCentered(std::string str);
int getLongestLine(std::string str);