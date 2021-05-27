#include <QtWidgets>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(640,480);
    
    
    window.setWindowTitle(QApplication::translate("toplevel","Top-level widget"));
    window.show();

    QPushButton *button = new QPushButton(
            "Press me", &window
    );

}
