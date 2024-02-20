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

  public slots:
    void flip_case();
    void make_lowercase();
    void make_uppercase();
    void open_file();
    void print_content();
    void quit_application();

  private:
    QHBoxLayout button_layout;
    QVBoxLayout main_layout;

    QPlainTextEdit editor;

    QLabel title;

    QPushButton flip_case_button;
    QPushButton lowercase_button;
    QPushButton open_file_button;
    QPushButton print_button;
    QPushButton quit_button;
    QPushButton uppercase_button;

  private:
    void setup_buttons();
    void setup_layouts();
};
