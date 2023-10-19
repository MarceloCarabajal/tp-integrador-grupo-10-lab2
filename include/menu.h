#ifndef MENU_INCLUDED
#define MENU_INCLUDED

const int DEFAULT_BG = rlutil::BLACK;

class Menu {
private:
    int totalOptions, currentOption;
    std::string *options;

public:
    void addOption(std::string option, int optNumber) int askOption();
    void printMenu(int selected);
    void printHighlighted(std::string text, bool highlight, int color = 14,
                          int x = 0, int y = 0);
};

#endif /* MENU_INCLUDED */
