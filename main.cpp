#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear una instancia de MainWindow
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Reproductor de Música");  // Opcional: Establece el título de la ventana
    mainWindow.show();

    // Ejecutar la aplicación
    return app.exec();
}

