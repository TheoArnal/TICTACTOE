#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct Player{
    QString name;
    int score;
    char piece;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;

    Player player;

    Player player1;
    Player player2;
    int playerTurn;
    int Gagnant;
    QString grille[3][3];
    bool grilleWin[3][3];



    void initialiseGrille(char value);
    void GrilleWin();
    void updatescore();
    void updateBoard();
    void updateStatus();
    bool PlayerWon(Player player);
    void playerAction(int x, int y);
    bool MoveAvailible();

    void FreezeBoard();
    void UnFreezeBoard();
    void player_Pseudo();
    void envoie_position(int x, int y);

};
#endif // MAINWINDOW_H
