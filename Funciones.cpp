#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidget>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QRandomGenerator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Inicialización de componentes
        MPlayer = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        dirmodel = new QFileSystemModel(this);

        // Configuración de la lista de reproducción
        playlistWidget = new QListWidget(this);
        currentIndex = -1;
        isShuffleEnabled = false;

        // Conectar señales y slots
        connect(MPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
        connect(playlistWidget, &QListWidget::doubleClicked, this, &MainWindow::on_playlistWidget_doubleClicked);
    }

private slots:
    // Función para cargar archivos de un directorio en la lista de reproducción
    void updatePlaylist(const QString &directory) {
        playlistWidget->clear(); // Limpia la lista de reproducción actual
        playlist.clear();
        originalPlaylist.clear();

        QDir dir(directory);
        QStringList filters = {"*.mp3", "*.mp4", "*.m4a", "*.wav"};
        QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

        for (const QFileInfo &file : files) {
            playlistWidget->addItem(file.fileName()); // Muestra el nombre en la lista
            playlist.append(file.filePath()); // Agrega la ruta completa al vector de reproducción
        }

        if (isShuffleEnabled) {
            applyShuffle(); // Si está habilitado el modo aleatorio, mezcla la lista
        }
    }

    // Función para reproducir el archivo seleccionado
    void playFile(const QString &filePath) {
        MPlayer->setAudioOutput(audioOutput);
        MPlayer->setSource(QUrl::fromLocalFile(filePath));
        MPlayer->play();
        currentIndex = playlist.indexOf(filePath); // Actualiza el índice actual
        playlistWidget->setCurrentRow(currentIndex); // Resalta el archivo actual
    }

    // Reproduce el archivo en la posición actual de la lista
    void on_playlistWidget_doubleClicked(const QModelIndex &index) {
        QString filePath = playlist.at(index.row());
        playFile(filePath);
    }

    // Función para reproducir el archivo siguiente en la lista
    void on_btnNext_clicked() {
        if (currentIndex < playlist.size() - 1) {
            currentIndex++;
            playFile(playlist.at(currentIndex));
        }
    }

    // Función para reproducir el archivo anterior en la lista
    void on_btnPrev_clicked() {
        if (currentIndex > 0) {
            currentIndex--;
            playFile(playlist.at(currentIndex));
        }
    }

    // Función para mezclar la lista de reproducción
    void on_btnShuffle_clicked() {
        isShuffleEnabled = !isShuffleEnabled;
        if (isShuffleEnabled) {
            applyShuffle();
        } else {
            restoreOriginalPlaylist();
        }
    }

    // Aplica el modo aleatorio a la lista de reproducción
    void applyShuffle() {
        originalPlaylist = playlist;
        QStringList tempPlaylist = playlist;
        playlist.clear();

        while (!tempPlaylist.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(tempPlaylist.size());
            playlist.append(tempPlaylist.takeAt(randomIndex));
        }

        // Actualiza la lista visual
        updatePlaylistWidget();
    }

    // Restaura el orden original de la lista de reproducción
    void restoreOriginalPlaylist() {
        playlist = originalPlaylist;
        updatePlaylistWidget();
    }

    // Actualiza la vista visual de la lista de reproducción
    void updatePlaylistWidget() {
        playlistWidget->clear();
        for (const QString &file : playlist) {
            QFileInfo fileInfo(file);
            playlistWidget->addItem(fileInfo.fileName());
        }
    }

    // Controla el comportamiento de reproducción al final de un medio
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia && currentIndex < playlist.size() - 1) {
            currentIndex++;
            playFile(playlist.at(currentIndex));
        }
    }

private:
    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
    QListWidget *playlistWidget;
    QFileSystemModel *dirmodel;
    QStringList playlist;
    QStringList originalPlaylist;
    int currentIndex;
    bool isShuffleEnabled;
};
