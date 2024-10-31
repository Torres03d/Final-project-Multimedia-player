#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    Player->setAudioOutput(audioOutput);

    // Inicializacion video widget
    videoWidget = ui->videoWidget;
    albumArtLabel = new QLabel(this);
    albumArtLabel->setAlignment(Qt::AlignCenter);
    albumArtLabel->hide();
    mediaTitleLabel = ui->label_Title;

    // Configurar iconos iniciales
    ui->pushButton_Play->setCheckable(true);
    ui->pushButton_Volume->setCheckable(true);
    ui->pushButton_Play->setIcon(QIcon(":/Icons/play.png"));
    ui->pushButton_Volume->setIcon(QIcon(":/Icons/volume.png"));

    // Configurar timer para actualización del tiempo
    timeUpdateTimer = new QTimer(this);
    timeUpdateTimer->setInterval(1000); // Actualiza cada 1000 ms
    connect(timeUpdateTimer, &QTimer::timeout, this, &MainWindow::updateCurrentTimeDisplay);
    timeUpdateTimer->start();

    // Conectar señales del Player
    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    isUpdatingSlider = false;

    connect(ui->horizontalSlider_Duration, &QSlider::sliderPressed, this, &MainWindow::on_horizontalSlider_Duration_sliderPressed);
    connect(ui->horizontalSlider_Duration, &QSlider::sliderReleased, this, &MainWindow::on_horizontalSlider_Duration_sliderReleased);
}

// Destructor de la clase MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Funcion para manejar los eventos de presión
void MainWindow::on_horizontalSlider_Duration_sliderPressed()
{
    isUpdatingSlider = true; // Evita actualizaciones mientras se arrastra
}

// Funciones para manejar los eventos de liberación
void MainWindow::on_horizontalSlider_Duration_sliderReleased()
{
    isUpdatingSlider = false;
    int value = ui->horizontalSlider_Duration->value();
    Player->setPosition(value * 1000); // Actualiza la posición del reproductor
}

// Funcion que ayuda a actualizar el contador de tiempo
void MainWindow::durationChanged(quint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
    updateTotalTime(mDuration);
}

// Función para cuando la posición del medio cambia
void MainWindow::positionChanged(quint64 duration)
{
    if (!isUpdatingSlider && !ui->horizontalSlider_Duration->isSliderDown())
    {
        ui->horizontalSlider_Duration->setValue(duration / 1000);
        updateCurrentTime(duration / 1000); // Añadido para mantener etiquetas sincronizadas
    }
}

// Funcion que actualiza el contador de tiempo
void MainWindow::updateCurrentTime(qint64 current)
{
    QTime currentTime((current / 3600), (current / 60) % 60, (current % 60));
    QString format = (currentTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Current_Time->setText(currentTime.toString(format));
}

// Funcion para el tiempo_total
void MainWindow::updateTotalTime(qint64 total)
{
    QTime totalTime((total / 3600) % 60, (total / 60) % 60, (total % 60));
    QString format = (totalTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Total_Time->setText(totalTime.toString(format));
}

// Funcion para abrir el buscador de archivos para seleccionar un archivo multimedia
void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Media"), "",
                                                    tr("Multimedia Files (*.mp3 *.mp4 *.wav *.avi)"));
    if (fileName.isEmpty())
        return;

    bool isVideo = fileName.endsWith(".mp4") || fileName.endsWith(".avi");
    displayMedia(fileName, isVideo);
}

// Funcion para mostrar el archivo multimedia
void MainWindow::displayMedia(const QString& fileName, bool isVideo)
{
    if (isVideo)
    {
        videoWidget->show();
        albumArtLabel->hide();
        Player->setVideoOutput(videoWidget);
    }
    else
    {
        videoWidget->hide();
        albumArtLabel->show();
        QPixmap albumArt(":/images/default_album_art.jpg"); // Placeholder
        albumArtLabel->setPixmap(albumArt.scaled(albumArtLabel->size(), Qt::KeepAspectRatio));
        Player->setVideoOutput(nullptr);
    }
    Player->setSource(QUrl::fromLocalFile(fileName));
    mediaTitleLabel->setText(QFileInfo(fileName).baseName());
}

// Maneja el click en el botón de play
void MainWindow::on_pushButton_Play_clicked()
{
    if (ui->pushButton_Play->isChecked())
    {
        IS_Pause = false;
        Player->play();
        ui->pushButton_Play->setIcon(QIcon(":/Icons/pause.png"));
    }
    else
    {
        IS_Pause = true;
        Player->pause();
        ui->pushButton_Play->setIcon(QIcon(":/Icons/play.png"));
    }
}

// Maneja el click en el botón de stop
void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
    disconnect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::updateTime); // Desconectar actualización de tiempo en stop
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if (ui->pushButton_Volume->isChecked())
    {
        IS_Muted = true;
        audioOutput->setMuted(true);
        ui->pushButton_Volume->setIcon(QIcon(":/Icons/mute.png"));
    }
    else
    {
        IS_Muted = false;
        audioOutput->setMuted(false);
        ui->pushButton_Volume->setIcon(QIcon(":/Icons/volume.png"));
    }
}

// Maneja el boton en el volumen
void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);  // Ajusta el volumen
}

// Maneja el cambio en la posición de la barra de reproducción
void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    // Asegúrate de no actualizar la posición si el deslizador está siendo arrastrado
    if (IS_Pause || ui->horizontalSlider_Duration->isSliderDown())
    {
        Player->setPosition(value * 1000);
    }
}

// Retrocede la reproducción
void MainWindow::on_pushButton_Seek_Backward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() - 20);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}

// Avanza la reproducción
void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() + 20);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}

// Funcion que realiza la conversion del contador
void MainWindow::updateCurrentTimeDisplay()
{
    // Solo actualizar visualmente si hay cambios significativos
    qint64 current = Player->position();
    if (!ui->horizontalSlider_Duration->isSliderDown())
    {
        ui->horizontalSlider_Duration->blockSignals(true);
        ui->horizontalSlider_Duration->setValue(current / 1000);
        ui->horizontalSlider_Duration->blockSignals(false);
    }
    updateCurrentTime(current / 1000);
}

//funcion que actualiza el tiempo actual
void MainWindow::updateTime()
{
    qint64 current = Player->position() / 1000;
    updateCurrentTime(current);
}
