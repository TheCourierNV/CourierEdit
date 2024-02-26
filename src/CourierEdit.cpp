#include <QApplication>
#include <QDebug>
#include <QFileDialog>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent) : QWidget(parent) {
    title = new QLabel("CourierEdit");
    editor = new QPlainTextEdit();

    setup_buttons();
    setup_layouts();

    qDebug() << "CourierEdit init";
}

void CourierEdit::setup_layouts() {
    main_layout = new QVBoxLayout;
    button_layout = new QHBoxLayout;

    main_layout->addWidget(title);
    main_layout->addWidget(editor);
    main_layout->addLayout(button_layout);

    button_layout->addWidget(print_button);
    button_layout->addWidget(uppercase_button);
    button_layout->addWidget(lowercase_button);
    button_layout->addWidget(flip_case_button);
    button_layout->addWidget(open_file_button);
    button_layout->addWidget(quit_button);

    this->setLayout(main_layout);
}

void CourierEdit::setup_buttons() {
    print_button = new QPushButton("Print");
    uppercase_button = new QPushButton("Make uppercase");
    lowercase_button = new QPushButton("Make lowercase");
    flip_case_button = new QPushButton("Flip case");
    open_file_button = new QPushButton("Open a file");
    quit_button = new QPushButton("Quit");

    connect(print_button, &QPushButton::pressed, this,
            &CourierEdit::print_content);
    connect(uppercase_button, &QPushButton::pressed, this,
            &CourierEdit::make_uppercase);
    connect(lowercase_button, &QPushButton::pressed, this,
            &CourierEdit::make_lowercase);
    connect(flip_case_button, &QPushButton::pressed, this,
            &CourierEdit::flip_case);
    connect(open_file_button, &QPushButton::pressed, this,
            &CourierEdit::open_file);
    connect(quit_button, &QPushButton::pressed, this,
            &CourierEdit::quit_application);
}

void CourierEdit::print_content() {
    qDebug() << "Content: " << editor->toPlainText();
}

void CourierEdit::quit_application() {
    qDebug() << "Quitting";
    QApplication::quit();
}

void CourierEdit::make_uppercase() {
    editor->setPlainText(editor->toPlainText().toUpper());
}

void CourierEdit::make_lowercase() {
    editor->setPlainText(editor->toPlainText().toLower());
}

void CourierEdit::flip_case() {
    QString new_text;

    for (QChar letter : editor->toPlainText()) {
        if (letter.isLower()) {
            letter = letter.toUpper();
        } else if (letter.isUpper()) {
            letter = letter.toLower();
        }

        new_text.append(letter);
    }

    editor->setPlainText(new_text);
}

void CourierEdit::open_file() {
    QFileDialog::getOpenFileContent(
        "", [this](const QString &file_name, const QByteArray &file_contents) {
            if (file_name.isEmpty()) {
                title->clear();
                editor->clear();
                qDebug() << "Failed to open the file, somehow";
            } else {
                title->setText(file_name);
                editor->setPlainText(file_contents);
                qDebug() << "Successfully opened: " << file_name;
            }
        });
}
