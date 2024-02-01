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
    void quit_application();

  private:
    QVBoxLayout main_layout;
    QHBoxLayout button_layout;
    QPlainTextEdit editor;

    QLabel title;

    QPushButton print_button;
    QPushButton quit_button;

  private:
};
