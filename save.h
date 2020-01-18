#ifndef SAVE_H
#define SAVE_H

#include "section.h"

class Save
{
    short sMistake, sRow, sColumn;
public:
    Save();

    void createSave(short mistake, short r, short c);

    short getSMistake() const;
    short getSRowSection() const;
    short getSColumnSection() const;
};

#endif // SAVE_H
