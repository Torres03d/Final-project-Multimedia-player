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

    // Initialize video widget
    videoWidget = new QVideoWidget(this);
    videoWidget->setGeometry(ui->groupBox_Display->geometry());
    videoWidget->hide();

    // Initialize album art label
    albumArtLabel = new QLabel(this);
    albumArtLabel->setGeometry(ui->groupBox_Display->geometry());
    albumArtLabel->setAlignment(Qt::AlignCenter);
    albumArtLabel->hide();

    // Initialize media title label
    mediaTitleLabel = ui->label_Title;

    // Connect signals to slots
    connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::durationChanged(quint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
    updateTotalTime(mDuration);
}

void MainWindow::positionChanged(quint64 duration)
{
    if (!ui->horizontalSlider_Duration->isSliderDown())
    {
        ui->horizontalSlider_Duration->setValue(duration / 1000);
    }
    updateCurrentTime(duration / 1000);
}

void MainWindow::updateCurrentTime(qint64 current)
{
    QTime currentTime((current / 3600) % 60, (current / 60) % 60, (current % 60));
    QString format = (currentTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Current_Time->setText(currentTime.toString(format));
}

void MainWindow::updateTotalTime(qint64 total)
{
    QTime totalTime((total / 3600) % 60, (total / 60) % 60, (total % 60));
    QString format = (totalTime.hour() > 0) ? "hh:mm:ss" : "mm:ss";
    ui->label_Total_Time->setText(totalTime.toString(format));
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select the File"), "", tr("Media Files (*.mp3 *.mp4)"));
    displayMedia(fileName, fileName.endsWith(".mp4"));
}

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

void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
}

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

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);  // Adjust volume
}

void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value * 1000);
}

void MainWindow::on_pushButton_Seek_Backward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() - 20);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}

void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() + 20);
    Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
}
