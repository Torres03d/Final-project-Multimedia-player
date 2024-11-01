#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
{
    ui->setupUi(this);

    // Conectar botones a las funciones
    connect(ui->btnPlay, &QPushButton::clicked, this, &MainWindow::playSong);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::pauseSong);
    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::stopSong);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::loadSongs);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playSong()
{
    QListWidgetItem *currentItem = ui->listWidget->currentItem();
    if (currentItem) {
        QString filePath = currentItem->data(Qt::UserRole).toString();
        player->setSource(QUrl::fromLocalFile(filePath));
        player->play();
    }
}

void MainWindow::pauseSong()
{
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
    }
}

void MainWindow::stopSong()
{
        if (player->playbackState() == QMediaPlayer::PlayingState || player->playbackState() == QMediaPlayer::PausedState) {
            player->stop();


    }
}

void MainWindow::loadSongs()
{
    songList = QFileDialog::getOpenFileNames(this, tr("Selecciona canciones"), "", tr("Audio Files (*.mp3 *.wav)"));
    ui->listWidget->clear();

    for (const QString &filePath : songList) {
        QListWidgetItem *item = new QListWidgetItem(QFileInfo(filePath).fileName());
        item->setData(Qt::UserRole, filePath); // Guardar la ruta completa
        ui->listWidget->addItem(item);
    }
}

