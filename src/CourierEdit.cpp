#include <QApplication>
#include <QDebug>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent) : QWidget(parent), main_layout(this) {
    main_layout.addWidget(&title);
    main_layout.addWidget(&editor);
    main_layout.addLayout(&button_layout);

    button_layout.addWidget(&print_button);
    button_layout.addWidget(&uppercase_button);
    button_layout.addWidget(&lowercase_button);
    button_layout.addWidget(&flip_case_button);
    button_layout.addWidget(&quit_button);

    title.setText("CourierEdit");

    print_button.setText("Print");
    uppercase_button.setText("Make uppercase");
    lowercase_button.setText("Make lowercase");
    flip_case_button.setText("Flip case");
    quit_button.setText("Quit");

    connect(&print_button, &QPushButton::pressed, this,
            &CourierEdit::print_content);
    connect(&uppercase_button, &QPushButton::pressed, this,
            &CourierEdit::make_uppercase);
    connect(&lowercase_button, &QPushButton::pressed, this,
            &CourierEdit::make_lowercase);
    connect(&flip_case_button, &QPushButton::pressed, this,
            &CourierEdit::flip_case);
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

void CourierEdit::make_uppercase() {
    editor.setPlainText(editor.toPlainText().toUpper());
}

void CourierEdit::make_lowercase() {
    editor.setPlainText(editor.toPlainText().toLower());
}

void CourierEdit::flip_case() {
    QString new_text;

    for (QChar letter : editor.toPlainText()) {
        if (letter.isLower()) {
            letter = letter.toUpper();
        } else if (letter.isUpper()) {
            letter = letter.toLower();
        }

        new_text.append(letter);
    }

    editor.setPlainText(new_text);
}
