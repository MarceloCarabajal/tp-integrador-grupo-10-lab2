#pragma once
#include <iostream>

void printLogo();
void notifSound();
bool sendEmail(std::string to, std::string subject, std::string body);
void coutCentered(std::string str);
int getLongestLine(std::string str);
void setWorkingDirectory();