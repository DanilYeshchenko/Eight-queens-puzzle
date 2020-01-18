#include "help.h"

Help::Help(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Довідник");
    setFixedSize(402, 400);

    text = "     Дана програма створена спеціально для вирішення  го-\n"
           "ловоломки про 8 ферзів.  Завдання  полягає  в  тому,  щоб\n"
           "на  шаховій  дошці   розмістити  8  ферзів  таким  чином,\n"
           "щоб  не  один  ферзь  не перетинався один з одним.  Ферзь\n"
           "(королева) ходить по горизонталі, вертикалі і діагоналі.\n"
           "     В даному  додатку  застосовується два рівня складно-\n"
           "сті на вибір: низький  та  високий.   Змінити режим можна\n"
           "за допомогою натискання на кнопку \"Складність\".\n"
           "     На низьком рівні складності комп'ютер  не  дозволить\n"
           "вам  зробити помилку,  попереджаючи вас про невірний хід.\n"
           "Коли на дошці  буде  виставлено 8 ферзів, система повідо-\n"
           "мить вас про перемогу.\n"
           "     На високому рівні  складності  вам необхідно розста-\n"
           "вити  на  шаховій  дошці  8  ферзів, після чого натиснути\n"
           "кнопку \"Перевірити\",  й  система  выдасть  вам  ваш\n"
           "результат.\n"
           "      Кнопка \"Скасувати хід\" скасовує ваш останній хід.\n"
           "      Кнопка \"Очистити поле\" прибирає всіх ферзів.";

    layout = new QGridLayout();

    title = new QLabel("Довідник");
    title->setStyleSheet("font: 16pt;"
                         "font-family: Times New Roman");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title, 1, 1, 1, 2);

    label = new QLabel(text);
    label->setStyleSheet("font: 11pt;"
                         "font-family: Times New Roman;");
    layout->addWidget(label, 2, 1, 1, 2);

    btnExamples = new QPushButton("Рішення");
    connect(btnExamples, SIGNAL(clicked()),
            this, SLOT(examples()));
    layout->addWidget(btnExamples, 3, 1);

    btnAuthor = new QPushButton("Автор");
    connect(btnAuthor, SIGNAL(clicked()),
            this, SLOT(author()));
    layout->addWidget(btnAuthor, 3, 2);

    btnBack = new QPushButton("Назад");
    connect(btnBack, SIGNAL(clicked()),
            this, SLOT(back()));
    btnBack->hide();
    layout->addWidget(btnBack, 3, 1, 1, 2);

    setLayout(layout);
}

void Help::examples()
{
    title->hide();
    label->setText("      Варіанти рішень:\n"
                   "A4, B1, C5, D8, E6, F3, G7, H2\n"
                   "A4, B7, C3, D8, E2, F5, G1, H6\n"
                   "A6, B4, C2, D8, E5, F7, G1, H3\n"
                   "A4, B2, C5, D8, E6, F1, G3, H7\n"
                   "A4, B2, C7, D3, E6, F8, G1, H5\n"
                   "A4, B2, C7, D3, E6, F8, G5, H1\n"
                   "A3, B5, C2, D8, E6, F4, G7, H1\n"
                   "A4, B1, C5, D8, E2, F7, G3, H6\n"
                   "A4, B8, C1, D5, E7, F2, G6, H3\n"
                   "A4, B2, C7, D5, E1, F8, G6, H3\n");
    label->setAlignment(Qt::AlignCenter);
    btnExamples->hide();
    btnAuthor->hide();
    btnBack->show();
}

void Help::author()
{
    title->hide();
    label->setText("Версія програми: 1.0.0.1\nАвторські права: Данил Єщенко");
    label->setAlignment(Qt::AlignCenter);
    btnExamples->hide();
    btnAuthor->hide();
    btnBack->show();
}

void Help::back()
{
    title->show();
    label->setText(text);
    label->setAlignment(Qt::AlignTop);
    btnExamples->show();
    btnAuthor->show();
    btnBack->hide();
}

Help::~Help()
{

}
