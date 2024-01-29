#include <QDebug>

#include "CourierEdit.h"

CourierEdit::CourierEdit(QWidget *parent)
    : QWidget(parent), print_button(this), quit_button(this), label(this),
      editor(this) {
    label.setText("CourierEdit");
    print_button.setText("Print");
    quit_button.setText("Quit");

    // TODO: Investigare i layout: https://doc.qt.io/qt-6/layout.html
    label.move(0, 0);
    editor.move(0, 100);
    print_button.move(0, 200);
    quit_button.move(100, 200);

    connect(&print_button, &QPushButton::pressed, this,
            &CourierEdit::print_data);
    connect(&editor, &QLineEdit::editingFinished, this,
            &CourierEdit::update_data);
    connect(&quit_button, &QPushButton::pressed, this,
            &CourierEdit::quit_application);

    qDebug() << "CourierEdit init";
}

void CourierEdit::print_data() { qDebug() << "Data: " << data; }

void CourierEdit::update_data() { data = editor.text(); }

void CourierEdit::quit_application() {
    // TODO: Investigare come comunicare con QApplication
    // Forse con il puntatore globale qApp (anche se è brutto)?
    // O forse creando un mio oggetto "CourierApp" che contiene QApplication?
    qDebug() << "Quit (not implemented)";
}
