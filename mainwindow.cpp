#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    Player->setAudioOutput(audioOutput);

    // Inicializacion video widget
    videoWidget = new QVideoWidget(this);
    videoWidget->setGeometry(ui->groupBox_Display->geometry());
    videoWidget->hide();

    // Inicializacion album art label
    albumArtLabel = new QLabel(this);
    albumArtLabel->setGeometry(ui->groupBox_Display->geometry());
    albumArtLabel->setAlignment(Qt::AlignCenter);
    albumArtLabel->hide();

    // Inicializacion media title label
    mediaTitleLabel = ui->label_Title;

    // Señales de Coneccion para los slots
    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);


}

// Destructor de la clase MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Función para cuando la duración del medio cambia
void MainWindow::durationChanged(quint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
    updateTotalTime(mDuration);
}

// Función para cuando la posición del medio cambia
void MainWindow::positionChanged(quint64 duration)
{
    if (!ui->horizontalSlider_Duration->isSliderDown())
    {
        ui->horizontalSlider_Duration->setValue(duration / 1000);
    }
    updateCurrentTime(duration / 1000);
}

// Funcion para el contador de tiempo
void MainWindow::updateCurrentTime(qint64 current)
{
    QTime currentTime((current / 3600) % 60, (current / 60) % 60, (current % 60));
    QString format = (currentTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Current_Time->setText(currentTime.toString(format));
}

// Funcion para el tiempo total
void MainWindow::updateTotalTime(qint64 total)
{
    QTime totalTime((total / 3600) % 60, (total / 60) % 60, (total % 60));
    QString format = (totalTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Total_Time->setText(totalTime.toString(format));
}

// Abre el buscador de archivos para seleccionar un archivo multimedia
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
    if (IS_Pause == true)
    {
        IS_Pause = false;
        Player->play();
        ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        IS_Pause = true;
        Player->pause();
        ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

 // Maneja el click en el botón de stop
void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
}

// Maneja el boton en el volumen
void MainWindow::on_pushButton_Volume_clicked()
{
    if (IS_Muted == false)
    {
        IS_Muted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        audioOutput->setMuted(true);
    }
    else
    {
        IS_Muted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        audioOutput->setMuted(false);
    }
}

// Maneja el cambio en la posición de reproducción
void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);  // Ajusta el volumen
}

// Maneja el cambio en el volumen
void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value * 1000);
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
