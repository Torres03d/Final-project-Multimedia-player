#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QUrl>

class AudioPlayer : public QWidget {
    Q_OBJECT
public:
    AudioPlayer(QWidget *parent = nullptr) : QWidget(parent) {
        // Crear el reproductor de medios
        player = new QMediaPlayer(this);

        // Botón para iniciar la reproducción
        QPushButton *playButton = new QPushButton("Reproducir", this);

        // Conectar el botón a la función de reproducción
        connect(playButton, &QPushButton::clicked, this, &AudioPlayer::playAudio);

        // Layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(playButton);

        setLayout(layout);
        setWindowTitle("Reproductor de Audio");
        resize(200, 100);
    }

private slots:
    void playAudio() {
        // Ruta del archivo de audio (puedes cambiarla por tu archivo de audio local)
        player->setSource(QUrl::fromLocalFile("ruta-de-Thunderstruck.mp3"));
        player->play();
    }

private:
    QMediaPlayer *player;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AudioPlayer window;
    window.show();

    return app.exec();
}
