#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class CourierEdit : public QWidget {
    Q_OBJECT
  public:
    CourierEdit(QWidget *parent = nullptr);
    void print_content();

  public slots:
    void make_uppercase();
    void make_lowercase();
    void flip_case();
    void quit_application();
    void open_file();

  private:
    QVBoxLayout main_layout;
    QHBoxLayout button_layout;

    QPlainTextEdit editor;

    QLabel title;

    QPushButton print_button;
    QPushButton uppercase_button;
    QPushButton lowercase_button;
    QPushButton flip_case_button;
    QPushButton open_file_button;
    QPushButton quit_button;

  private:
    void setup_buttons();
    void setup_layouts();
};
