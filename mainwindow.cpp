#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , playlist(new QMediaPlaylist(this)) // Inicializamos la lista de reproducción
{
    ui->setupUi(this);

    // Configuramos la lista de reproducción en el reproductor
    player->setPlaylist(playlist);

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
    if (playlist->isEmpty()) {
        return; // Si la lista de reproducción está vacía, no hacemos nada
    }
    player->play();
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
    ui->playlist->clear();
    playlist->clear(); // Limpiamos la lista de reproducción

    for (const QString &filePath : songList) {
        // Añadimos cada archivo a la lista de reproducción
        playlist->addMedia(QUrl::fromLocalFile(filePath));

        // Mostramos el nombre del archivo en la interfaz
        QListWidgetItem *item = new QListWidgetItem(QFileInfo(filePath).fileName());
        item->setData(Qt::UserRole, filePath); // Guardar la ruta completa
        ui->playlist->addItem(item);
    }

    playlist->setCurrentIndex(0); // Empezamos desde la primera canción
}
