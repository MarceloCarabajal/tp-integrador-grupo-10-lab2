#ifndef EMAILTEMPLATE_INCLUDED
#define EMAILTEMPLATE_INCLUDED

#include <iostream>

#include "Date.h"

class EmailTemplate {
private:
    std::string _templateFile;
    std::string _HTMLData = "";
    void getHTMlTemplate();
    bool replaceParameter(std::string paramKey, std::string newValue);

public:
    EmailTemplate(std::string templateFile);
    bool setEmailData(std::string recipientName, std::string bodyTitle,
                      Date expDate);
    std::string getHTML();
};

#endif /* EMAILTEMPLATE_INCLUDED */
