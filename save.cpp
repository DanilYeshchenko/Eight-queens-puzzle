#include "save.h"

Save::Save()
{

}

void Save::createSave(short mistake, short r, short c)
{
    sMistake = mistake;
    sRow = r;
    sColumn = c;
}

short Save::getSMistake() const
{
    return sMistake;
}
short Save::getSRowSection() const
{
    return sRow;
}
short Save::getSColumnSection() const
{
    return sColumn;
}
