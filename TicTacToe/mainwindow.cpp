#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool ok;
    player1.name = QInputDialog::getText(this, tr("Player One"), tr("Entrer Votre Nom"), QLineEdit::Normal, "", &ok);

    if(player1.name.size()==0)
        player1.name = "Player 1";

    player2.name = QInputDialog::getText(this, tr("Player Two"), tr("Entrer Votre Nom"), QLineEdit::Normal, "", &ok);

    if(player2.name.size()==0)
        player2.name = "Player 1";

    player1.score = 0;
    player1.piece = 'X';

    player2.score = 0;
    player2.piece = 'O';

    playerTurn = 1;


    initialiseGrille(' ');
    updatescore();
    updateStatus();
    updateBoard();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBoard()
{
    ui->pushButton_1->setText(QString(grille[0][0]));
    ui->pushButton_2->setText(QString(grille[0][1]));
    ui->pushButton_3->setText(QString(grille[0][2]));
    ui->pushButton_4->setText(QString(grille[1][0]));
    ui->pushButton_5->setText(QString(grille[1][1]));
    ui->pushButton_6->setText(QString(grille[1][2]));
    ui->pushButton_7->setText(QString(grille[2][0]));
    ui->pushButton_8->setText(QString(grille[2][1]));
    ui->pushButton_9->setText(QString(grille[2][2]));

}

void MainWindow::playerAction(int x, int y)
{

    if (playerTurn == 1)
    {
        grille[y][x] = player1.piece;
        playerTurn = 2;
        updateStatus();
        updateBoard();
    }
    else
    {
        grille[y][x] = player2.piece;
        playerTurn = 1;
        updateStatus();
        updateBoard();
    }
}

bool MainWindow::MoveAvailible()
{
    for(int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if(grille[x][y] == ' ')
                return true;
        }
    }
    return false;
}

void MainWindow::FreezeBoard()
{
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
}

void MainWindow::UnFreezeBoard()
{

    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_9->setEnabled(true);
}

void MainWindow::updateStatus()
{
    if (PlayerWon(player1))
    {
        ui->label_status->setText(player1.name + " WON!");
        Gagnant = 1;
        player1.score++;
        FreezeBoard();
        updatescore();
        return;
    }
    if (PlayerWon(player2))
    {
        ui->label_status->setText(player2.name + " WON!");
        Gagnant = 2;
        player2.score++;
        FreezeBoard();
        updatescore();
        return;
    }

    if (!MoveAvailible())
    {
        ui->label_status->setText("Tie Game");
        return;
    }

    if (playerTurn == 1)
        ui->label_status->setText(player1.name + "'s turn");
    else
        ui->label_status->setText(player2.name + "'s turn");
}

bool MainWindow::PlayerWon(Player player)
{

    //Vertical
    if(grille[0][0] == player.piece && grille[1][0] == player.piece && grille[2][0] == player.piece)
    {
        grille[0][0] = true;
        grille[1][0] = true;
        grille[2][0] = true;
        return true;

    }
    else if(grille[0][1] == player.piece && grille[1][1] == player.piece && grille[2][1] == player.piece)
    {
        grille[0][1] = true;
        grille[1][1] = true;
        grille[2][1] = true;
        return true;

    }
    else if(grille[0][2] == player.piece && grille[1][2] == player.piece && grille[2][2] == player.piece)
    {
        grille[0][2] = true;
        grille[1][2] = true;
        grille[2][2] = true;
        return true;

    }

    //Diagonal
    else if(grille[0][0] == player.piece && grille[1][1] == player.piece && grille[2][2] == player.piece)
    {
        grille[0][0] = true;
        grille[1][1] = true;
        grille[2][2] = true;
        return true;

    }
    else if(grille[2][0] == player.piece && grille[1][1] == player.piece && grille[0][2] == player.piece)
    {
        grille[2][0] = true;
        grille[1][1] = true;
        grille[0][2] = true;
        return true;
    }

    //Horizontal
    else if(grille[0][0] == player.piece && grille[1][1] == player.piece && grille[2][2] == player.piece)
    {
        grille[0][0] = true;
        grille[1][1] = true;
        grille[2][2] = true;
        return true;
    }
    else if(grille[0][0] == player.piece && grille[0][1] == player.piece && grille[0][2] == player.piece)
    {
        grille[0][0] = true;
        grille[0][1] = true;
        grille[0][2] = true;
        return true;
    }
    else if(grille[1][0] == player.piece && grille[1][1] == player.piece && grille[1][2] == player.piece)
    {
        grille[1][0] = true;
        grille[1][1] = true;
        grille[1][2] = true;
        return true;
    }
    else if(grille[2][0] == player.piece && grille[2][1] == player.piece && grille[2][2] == player.piece)
    {
        grille[2][0] = true;
        grille[2][1] = true;
        grille[2][2] = true;
        return true;
    }

    return false;
}


void MainWindow::on_pushButton_1_clicked()
{
    playerAction(0, 0);
}

void MainWindow::on_pushButton_2_clicked()
{
    playerAction(1, 0);
}

void MainWindow::on_pushButton_3_clicked()
{
    playerAction(2, 0);
}

void MainWindow::on_pushButton_4_clicked()
{
    playerAction(0, 1);
}

void MainWindow::on_pushButton_5_clicked()
{
    playerAction(1, 1);
}

void MainWindow::on_pushButton_6_clicked()
{
    playerAction(2, 1);
}

void MainWindow::on_pushButton_7_clicked()
{
    playerAction(0, 2);
}

void MainWindow::on_pushButton_8_clicked()
{
    playerAction(1, 2);
}

void MainWindow::on_pushButton_9_clicked()
{
    playerAction(2, 2);
}

void MainWindow::initialiseGrille(char value)
{
    for(int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            grille[y][x] = value;
        }
    }
}

void MainWindow::GrilleWin()
{
    for(int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            grilleWin[y][x] = false;
        }
    }
}

void MainWindow::updatescore()
{
    ui->label_1->setText(QString(player1.piece) + ": " + player1.name + " - " + QString::number(player1.score));
    ui->label_2->setText(QString::number(player2.score) + " - " + player2.name + " :" + QString(player2.piece));
}

void MainWindow::on_pushButton_clicked()
{
    Gagnant = 0;
    playerTurn = 1;
    initialiseGrille(' ');
    GrilleWin();
    updateBoard();
    UnFreezeBoard();
    updateStatus();
}
