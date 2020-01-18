#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QtWidgets>

class Help : public QWidget
{
    Q_OBJECT
    QString text;
    QGridLayout *layout;
    QLabel *title;
    QLabel *label;
    QPushButton *btnExamples;
    QPushButton *btnAuthor;
    QPushButton *btnBack;

public:
    Help(QWidget *parent = nullptr);
    ~Help();

private slots:
    void examples();
    void author();
    void back();
};

#endif // HELP_H
