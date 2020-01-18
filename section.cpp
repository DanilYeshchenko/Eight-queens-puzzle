#include "section.h"

Section::Section()
{
    button = new QPushButton();
    queen = false;
}

    /* Getters */
QPushButton* Section::getButton() const
{
    return button;
}
bool Section::getQueen() const
{
    return queen;
}

    /* Setters */
void Section::setQueen(bool q)
{
    queen = q;
}
void Section::setStyle(short typeStyle)
{
    QString style = "QPushButton{border: 1px grove black;"
                    "border-style: outset;"
                    "font: 28pt;";
    if(typeStyle % 2 == 0){
        button->setStyleSheet(style + "background-color: #F4A460;}"
                                      "QPushButton:hover{background-color: #48D1CC;}");
    }
    else {
        button->setStyleSheet(style + "background-color: #FFDAB9;}"
                                      "QPushButton:hover{background-color: #AFEEEE;}");
    }
}
