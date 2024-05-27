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
    // TODO: Crea automaticamente i menù categoria
    QMenu *application_menu = menuBar()->addMenu("App");
    QMenu *file_menu = menuBar()->addMenu("Files");
    QMenu *text_menu = menuBar()->addMenu("Text");
    QMenu *case_menu = text_menu->addMenu("Change case");

    for (auto action : actions) {
        auto [action_name, action_slot, action_category] = action;

        QMenu *category_menu;

        switch (action_category) {
        case ActionCategory::ApplicationControl: {
            category_menu = application_menu;
            break;
        }
        case ActionCategory::TextCase: {
            category_menu = case_menu;
            break;
        }
        case ActionCategory::File: {
            category_menu = file_menu;
            break;
        }

        // TODO: Pensare meglio come gestire il caso dove una categoria non
        // ha un menù
        default:
            continue;
        }

        make_menu(action_name, category_menu, action_slot);
    }
}

void CourierEdit::make_menu(const QString &action_name, QMenu *parent_menu,
                            void (CourierEdit::*action_slot)()) {
    QAction *new_action = parent_menu->addAction(action_name);
    connect(new_action, &QAction::triggered, this, action_slot);
}

void CourierEdit::setup_layouts() {
    central_widget = new QWidget;
    main_layout = new QVBoxLayout;
    button_layout = new QHBoxLayout;

    main_layout->addWidget(title);
    main_layout->addWidget(editor);
    main_layout->addLayout(button_layout);

    for (auto button : buttons) {
        button_layout->addWidget(button);
    }

    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
}

QPushButton *CourierEdit::make_button(const QString &text,
                                      void (CourierEdit::*on_press)()) {
    QPushButton *new_button = new QPushButton(text);

    connect(new_button, &QPushButton::pressed, this, on_press);

    return new_button;
}

void CourierEdit::setup_buttons() {
    for (auto &action : actions) {
        auto [button_name, button_slot, _] = action;

        buttons.append(make_button(button_name, button_slot));
    }
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
