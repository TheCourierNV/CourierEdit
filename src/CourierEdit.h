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

    enum class ActionCategory {
        File,
        ApplicationControl,
        // TODO: Trova modo per implementare sotto-categorie
        TextCase,
    };

    const QList<
        std::tuple<const char *, void (CourierEdit::*)(), ActionCategory>>
        actions = {
            {
                "Print",
                &CourierEdit::print_content,
                ActionCategory::ApplicationControl,
            },
            {
                "Make uppercase",
                &CourierEdit::make_uppercase,
                ActionCategory::TextCase,
            },
            {
                "Make lowercase",
                &CourierEdit::make_lowercase,
                ActionCategory::TextCase,
            },
            {
                "Flip case",
                &CourierEdit::flip_case,
                ActionCategory::TextCase,
            },
            {
                "Open a file",
                &CourierEdit::open_file,
                ActionCategory::File,
            },
            {
                "Save file",
                &CourierEdit::save_file,
                ActionCategory::File,
            },
            {
                "Quit",
                &CourierEdit::quit_application,
                ActionCategory::ApplicationControl,
            },
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
