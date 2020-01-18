#ifndef SECTION_H
#define SECTION_H

#include <QPushButton>

class Section
{
    QPushButton *button;
    bool queen;
public:
    Section();

    QPushButton* getButton() const;
    bool getQueen() const;

    void setQueen(bool q);
    void setStyle(short typeStyle);
};

#endif // SECTION_H
