#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>

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
    void playSong();
    void pauseSong();
    void stopSong();
    void loadSongs();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QStringList songList; // Lista de archivos de canciones
};

#endif // MAINWINDOW_H
