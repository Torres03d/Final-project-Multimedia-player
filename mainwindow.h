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

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void showVolumeSlider(); //LLamada para mostrar la barra de volumen
    void hideVolumeSlider(); //LLamada para ocultar la barra de volumen
    void on_horizontalSlider_Duration_sliderPressed(); // Llamada cuando se cambia la barra de duracion
    void on_horizontalSlider_Duration_sliderReleased(); // Llamada ajustar el audio al precionar barra de duracion
    void updateTime(); // Slot para actualizar el contador
    void durationChanged(quint64 duration); // Llamada cuando la duración cambia
    void positionChanged(quint64 duration); // Llamada cuando la posición cambia
    void on_pushButton_Play_clicked(); // Maneja la reproducción
    void on_pushButton_Repeat_clicked(); // Maneja el botón de repeticion
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
    QVideoWidget *videoWidget; // Widget para mostrar video
    QAudioOutput *audioOutput; // Salida de audio
    quint64 mDuration; // Duración del archivo
    bool IS_Pause; // Estado de pausa
    bool IS_Muted; // Estado de mute
    QTimer *timeUpdateTimer; // Timer para actualizar el tiempo
    QLabel *mediaTitleLabel;
    QLabel *albumArtLabel;
    void displayMedia(const QString& fileName, bool isVideo);
    void updateCurrentTime(qint64 current); // Declaración de la función updateCurrentTime
    void updateTotalTime(qint64 total); // Declaración de la función updateTotalTime
};

#endif // MAINWINDOW_H
