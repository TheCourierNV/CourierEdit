#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <tuple>

class CourierEdit : public QMainWindow {
    Q_OBJECT
  public:
    CourierEdit(QWidget *parent = nullptr);

  public slots:
    void flip_case();
    void make_lowercase();
    void make_uppercase();
    void open_file();
    void print_content();
    void quit_application();
    void save_file();

  private:
    QHBoxLayout *button_layout;
    QVBoxLayout *main_layout;

    QPlainTextEdit *editor;

    QWidget *central_widget;

    QLabel *title;

    const QList<std::tuple<const char *, void (CourierEdit::*)()>> actions = {
        {"Print", &CourierEdit::print_content},
        {"Make uppercase", &CourierEdit::make_uppercase},
        {"Make lowercase", &CourierEdit::make_lowercase},
        {"Flip case", &CourierEdit::flip_case},
        {"Open a file", &CourierEdit::open_file},
        {"Save file", &CourierEdit::save_file},
        {"Quit", &CourierEdit::quit_application},
    };

    QList<QPushButton *> buttons;

  private:
    void setup_buttons();
    void setup_layouts();
    void setup_menus();
    void setup_file_menu();
    void setup_text_menu();

    QPushButton *make_button(const QString &text,
                             void (CourierEdit::*on_press)());
};
