#include "widget.h"
#include "help.h"
#include <QApplication>

void Widget::createCoordinates(QLabel *label[], short symbol, short w, bool rowOrColumn)
{
    for (short i = 0; i < 8; i++) {
        label[i] = new QLabel(QChar(symbol + i));
        label[i]->setFixedSize(QSize(w, 14));
        label[i]->setStyleSheet("font: 14px;");
        label[i]->setAlignment(Qt::AlignCenter);
        if(rowOrColumn == 0) layout->addWidget(label[i], 1+i, 0);
        else layout->addWidget(label[i], 0, 1+i);
    }
}

void Widget::createBoard()
{
    short n = 1;
    for (short i = 0; i < 8; i++, n--) {
        for (short j = 0; j < 8; j++, n++) {
            sections[i][j].getButton()->setFixedSize(QSize(40, 40));
            sections[i][j].setStyle(n);
            layout->addWidget(sections[i][j].getButton(), 1+i, 1+j);
            connect(sections[i][j].getButton(), &QPushButton::clicked,
                    this, [=] () { tryPutQueen(i, j); });
        }
    }
}

void Widget::putButtonInLayout(QPushButton *button, short row)
{
    button->setFixedSize(QSize(140, 35));
    layout->addWidget(button, row, 10, 2, 4);
}

void Widget::makeSave(short r, short c)
{
    countSave++;
    saves[countSave].createSave(mistake, r, c);
}

bool Widget::checkQueen(short r, short c){
    for (short i = 0; i < 8; i++) {
        if(sections[r][i].getQueen() == 1) return 0;
        if(sections[i][c].getQueen() == 1) return 0;
        if(r-i >= 0 && c-i >= 0) if(sections[r-i][c-i].getQueen() == 1) return 0;
        if(r-i >= 0 && c+i < 8) if(sections[r-i][c+i].getQueen() == 1) return 0;
        if(r+i < 8 && c-i >= 0) if(sections[r+i][c-i].getQueen() == 1) return 0;
        if(r+i < 8 && c+i < 8) if(sections[r+i][c+i].getQueen() == 1) return 0;
    }
    return 1;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("8 Ферзів");

    layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);

        /* Координаты */
    createCoordinates(lab1_8, 49, 20, 0);
    createCoordinates(labA_H, 65, 40, 1);

        /* Доска */
    createBoard();

    label = new QLabel("Ласкаво просимо!\nЯкщо ви відкрили цю програму вперше,"
                       "\nскористайтесь довідником (кнопка \"?\")");
    label->setFixedSize(QSize(360, 60));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label, 18, 0, 2, 13);

        /* Кнопки */
    btnCheck = new QPushButton("Перевірити");
    connect(btnCheck, SIGNAL(clicked()),
            this, SLOT(checkWin()));
    btnCheck->setEnabled(false);
    putButtonInLayout(btnCheck, 1);

    btnCancel = new QPushButton("Скасувати хід");
    connect(btnCancel, SIGNAL(clicked()),
            this, SLOT(cancel()));
    btnCancel->setEnabled(false);
    putButtonInLayout(btnCancel, 3);

    btnClear = new QPushButton("Очистити поле");
    connect(btnClear, SIGNAL(clicked()),
            this, SLOT(clear()));
    btnClear->setEnabled(false);
    putButtonInLayout(btnClear, 5);

    btnDifficulty = new QPushButton("Складність: Низька");
    connect(btnDifficulty, SIGNAL(clicked()),
            this, SLOT(changeDifficulty()));
    putButtonInLayout(btnDifficulty, 7);

    btnHelp = new QPushButton("?");
    btnHelp->setFixedSize(QSize(24, 24));
    btnHelp->setStyleSheet("QPushButton{background-color: #4169E0;"
                           "border: 2px grove black;"
                           "border-style:outset;"
                           "border-radius: 12px;"
                           "font: 15px;"
                           "color: white;}"
                           "QPushButton:hover{background-color: #6495ED}");
    connect(btnHelp, SIGNAL(clicked()),
            this, SLOT(openHelpWindow()));
    layout->addWidget(btnHelp, 0, 13, 1, 1);

    setLayout(layout);
}

    /* SLOTS */
void Widget::tryPutQueen(short r, short c)
{
    if(sections[r][c].getQueen() == 0){
        if(countQueen < 8){
            bool possibility = checkQueen(r, c);
            if(possibility == 1 || difficulty == 1){
                sections[r][c].getButton()->setText(QString::fromUtf8("\u265B"));
                sections[r][c].setQueen(true); countQueen++;
                if(countQueen > 1) makeSave(r, c);
                if(possibility == 0) mistake++;
                btnCancel->setEnabled(true); btnClear->setEnabled(true);
                if(countQueen == 8 && difficulty == 0) label->setText("Вітаємо, ви здобули перемогу!");
                else label->setText("Ферзь був поставлений в клітку " + QString(QChar(65+c)) + QString(QChar(49+r)));
            }
            else label->setText("Сюди не можна поставити ферзя");
        }
        else if (difficulty == 1) label->setText("Ви вже розмістили максимальну кількість ферзів,"
                            "\nнатисніть кнопку \"Перевірити\", щоб дізнатися свій результат");
    }
    else label->setText("Місце зайнято");
}

void Widget::checkWin()
{
    if(countQueen < 8) label->setText("Ви ще не розмістили всіх ферзів");
    else if(mistake > 0) label->setText("Ви допустили помилку,"
                                         "\nперевірте ще раз розташування поставлених ферзів");
    else label->setText("Вітаємо, ви здобули перемогу!");
}

void Widget::cancel()
{
    if (countQueen == 1) clear();
    else {
        mistake = saves[countSave].getSMistake();
        sections[saves[countSave].getSRowSection()][saves[countSave].getSColumnSection()].setQueen(false);
        sections[saves[countSave].getSRowSection()][saves[countSave].getSColumnSection()].getButton()->setText(QString::fromUtf8(""));
        countSave--;
        countQueen--;
    }
    label->setText("Дія скасована");
}

void Widget::clear()
{
    mistake = 0;
    countSave = 0;
    countQueen = 0;
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            sections[i][j].getButton()->setText("");
            sections[i][j].setQueen(false);
        }
    }
    btnCancel->setEnabled(false);
    btnClear->setEnabled(false);
    label->setText("Очищення завершено");
}

void Widget::changeDifficulty()
{
    if (countQueen == 8) clear();
    if (countQueen > 0) label->setText("Спочатку завершіть почату гру,"
                                                           "\nабо виконайте очищення");
    else if (difficulty == 0){

        difficulty = 1;
        btnDifficulty->setText("Складність: Висока");
        btnCheck->setEnabled(true);
        label->setText("Ви змінили рівень складності\nз низького на високий");
    }
    else {
        difficulty = 0;
        btnDifficulty->setText("Складність: Низька");
        btnCheck->setEnabled(false);
        label->setText("Ви змінили рівень складності\nз високого на низький");
    }
}

void Widget::openHelpWindow()
{
    helpWindow.show();
}

Widget::~Widget()
{

}
