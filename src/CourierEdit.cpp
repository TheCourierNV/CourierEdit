#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent) : QMainWindow(parent) {
    title = new QLabel("CourierEdit");
    editor = new QPlainTextEdit();

    setup_menus();
    setup_buttons();
    setup_layouts();

    qDebug() << "CourierEdit init";
}

void CourierEdit::setup_menus() {
    setup_file_menu();
    setup_text_menu();
}

void CourierEdit::setup_file_menu() {
    QMenu *file_menu = menuBar()->addMenu("Files");

    QAction *open_file = file_menu->addAction("Open");
    QAction *save_file = file_menu->addAction("Save");

    connect(open_file, &QAction::triggered, this, &CourierEdit::open_file);
    connect(save_file, &QAction::triggered, this, &CourierEdit::save_file);
}

void CourierEdit::setup_text_menu() {
    QMenu *text_menu = menuBar()->addMenu("Text");
    QMenu *case_menu = text_menu->addMenu("Change case");

    QAction *make_uppercase = case_menu->addAction("Make uppercase");
    QAction *make_lowercase = case_menu->addAction("Make lowercase");
    QAction *flip_case = case_menu->addAction("Flip case");

    connect(make_uppercase, &QAction::triggered, this,
            &CourierEdit::make_uppercase);
    connect(make_lowercase, &QAction::triggered, this,
            &CourierEdit::make_lowercase);
    connect(flip_case, &QAction::triggered, this, &CourierEdit::flip_case);
}

void CourierEdit::setup_layouts() {
    central_widget = new QWidget;
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
    button_layout->addWidget(save_file_button);
    button_layout->addWidget(quit_button);

    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
}

QPushButton *CourierEdit::make_button(const QString &text,
                                      void (CourierEdit::*&&on_press)()) {
    QPushButton *new_button = new QPushButton(text);

    connect(new_button, &QPushButton::pressed, this, on_press);

    return new_button;
}

void CourierEdit::setup_buttons() {
    print_button = make_button("Print", &CourierEdit::print_content);
    uppercase_button =
        make_button("Make uppercase", &CourierEdit::make_uppercase);
    lowercase_button =
        make_button("Make lowercase", &CourierEdit::make_lowercase);
    flip_case_button = make_button("Flip case", &CourierEdit::flip_case);
    open_file_button = make_button("Open a file", &CourierEdit::open_file);
    save_file_button = make_button("Save file", &CourierEdit::save_file);
    quit_button = make_button("Quit", &CourierEdit::quit_application);
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

void CourierEdit::save_file() {
    QString file_name = QFileDialog::getSaveFileName();

    qDebug() << "Selected save location: " << file_name;

    QFile *selected_file = new QFile(file_name);

    selected_file->open(QFile::WriteOnly);
    selected_file->write(editor->toPlainText().toUtf8());
    selected_file->close();
}
