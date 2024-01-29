#include <QApplication>

#include "CourierEdit.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    CourierEdit courier_edit;
    courier_edit.show();

    return app.exec();
}
