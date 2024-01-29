#include <QApplication>
#include <QDebug>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent) : QWidget(parent), main_layout(this) {
    main_layout.addWidget(&label);
    main_layout.addWidget(&editor);
    main_layout.addLayout(&button_layout);

    button_layout.addWidget(&print_button);
    button_layout.addWidget(&quit_button);

    label.setText("CourierEdit");
    print_button.setText("Print");
    quit_button.setText("Quit");

    connect(&print_button, &QPushButton::pressed, this,
            &CourierEdit::print_data);
    // TODO: Investigare se esiste un metodo più efficiente; non dovrebbe essere
    // necessario salvare ad ogni singolo carattere
    connect(&editor, &QPlainTextEdit::textChanged, this,
            &CourierEdit::update_data);
    connect(&quit_button, &QPushButton::pressed, this,
            &CourierEdit::quit_application);

    qDebug() << "CourierEdit init";
}

void CourierEdit::print_data() { qDebug() << "Data: " << data; }

void CourierEdit::update_data() { data = editor.toPlainText(); }

void CourierEdit::quit_application() {
    qDebug() << "Quitting";
    QApplication::quit();
}
