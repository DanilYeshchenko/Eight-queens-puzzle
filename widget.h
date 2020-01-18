#ifndef WIDGET_H
#define WIDGET_H

#include "section.h"
#include "save.h"
#include "help.h"
#include <QWidget>
#include <QtWidgets>

class Widget : public QWidget
{
    Q_OBJECT
    bool difficulty = 0;
    short countQueen = 0,
          countSave = 0,
          mistake = 0;
    Section sections[8][8];
    Save saves[8];
    Help helpWindow;
    QGridLayout *layout;
    QLabel *lab1_8[8], *labA_H[8];
    QLabel *label;
    QPushButton *btnCheck, *btnCancel,
                *btnClear, *btnDifficulty,
                *btnHelp;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void createCoordinates(QLabel *label[], short symbol, short w, bool rowOrColumn);
    void createBoard();
    void putButtonInLayout(QPushButton *button, short row);
    void makeSave(short r, short c);
    bool checkQueen(short r, short c);

private slots:
    void tryPutQueen(short r, short c);
    void checkWin();
    void cancel();
    void clear();
    void changeDifficulty();
    void openHelpWindow();
};

#endif // WIDGET_H
