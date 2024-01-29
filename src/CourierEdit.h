#pragma once

#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QWidget>

class CourierEdit : public QWidget {
    Q_OBJECT
  public:
    CourierEdit(QWidget *parent = nullptr);
    void print_data();

  public slots:
    void update_data();
    void quit_application();

  private:
    QPlainTextEdit editor;
    QLabel label;
    QPushButton print_button;
    QPushButton quit_button;

  private:
    QString data;
};
