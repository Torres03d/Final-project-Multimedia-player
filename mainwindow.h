#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTime(); // stot para actializar el contador
    void durationChanged(quint64 duration); // Llamada cuando la duración cambia
    void positionChanged(quint64 duration); // Llamada cuando la posición cambia
    void on_pushButton_Play_clicked(); // Maneja la reproducción
    void on_pushButton_Stop_clicked(); // Maneja el botón de stop
    void on_pushButton_Volume_clicked(); // Cambia el volumen
    void on_horizontalSlider_Volume_valueChanged(int value); // Cambia la posición de reproducción
    void on_horizontalSlider_Duration_valueChanged(int value); // Cambia duración reproducción
    void on_action_Open_triggered(); // Abre el diálogo de archivo
    void on_pushButton_Seek_Backward_clicked(); // Retrocede 10 segundos
    void on_pushButton_Seek_Forward_clicked(); // Avanza 10 segundos
    void updateCurrentTimeDisplay(); // Nueva función para actualizar el tiempo actual

private:
    Ui::MainWindow *ui; // Interfaz de usuario
    bool isUpdatingSlider; // flag
    QMediaPlayer *Player; // Reproductor de medios
    QVideoWidget *Video; // Widget para mostrar video
    QAudioOutput *audioOutput; // Salida de audio
    quint64 mDuration; // Duración del archivo
    bool IS_Pause = true; // Estado de pausa
    bool IS_Muted = false; // Estado de mute
    QTimer *timeUpdateTimer; // Timer para actualizar el tiempo
    void updateDuration(quint64 Duration); // Actualiza la duración
    void updateCurrentTime(qint64 current); // Actualiza el tiempo actual
    void updateTotalTime(qint64 total); // Actualiza el tiempo total
    QLabel *mediaTitleLabel;
    QVideoWidget *videoWidget;
    QLabel *albumArtLabel;
    void displayMedia(const QString& fileName, bool isVideo);
};

#endif // MAINWINDOW_H
