#include <QApplication>
#include <QDebug>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent) : QWidget(parent), main_layout(this) {
    main_layout.addWidget(&title);
    main_layout.addWidget(&editor);
    main_layout.addLayout(&button_layout);

    button_layout.addWidget(&print_button);
    button_layout.addWidget(&quit_button);

    title.setText("CourierEdit");

    print_button.setText("Print");
    quit_button.setText("Quit");

    connect(&print_button, &QPushButton::pressed, this,
            &CourierEdit::print_content);
    connect(&quit_button, &QPushButton::pressed, this,
            &CourierEdit::quit_application);

    qDebug() << "CourierEdit init";
}

void CourierEdit::print_content() {
    qDebug() << "Content: " << editor.toPlainText();
}

void CourierEdit::quit_application() {
    qDebug() << "Quitting";
    QApplication::quit();
}
