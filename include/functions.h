#pragma once
#include <iostream>

void printLogo();
void notifSound();
bool sendEmail(std::string to, std::string subject, std::string body);
void coutCenter(std::string str);
int getLongestLine(std::string str);
void setWorkingDirectory();