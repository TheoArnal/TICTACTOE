#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QInputDialog>
#include <iostream>

#include <QtGui>
#include <QtNetwork>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    player_Pseudo();



    QNetworkAccessManager man;
    QNetworkRequest req(QUrl("http://localhost:8080/retourneGrille"));
    QString ua("HttpRequestDemo/0.1 (Win64) Qt/5.7");
    req.setHeader(QNetworkRequest::UserAgentHeader, QVariant(ua));
    QNetworkReply* reply = man.get(req);
    QObject::connect(reply, &QNetworkReply::finished, [&](){
        QByteArray read = reply->readAll();

        qDebug() << read;
        std::cout << "Got response:\n" << read.toStdString() << std::endl;

        if(read == "[[\" \",\" \",\" \"],[\" \",\" \",\" \"],[\" \",\" \",\" \"]]")
        {
            initialiseGrille(' ');
        }

        reply->deleteLater();
        reply->close();
    });



        QNetworkAccessManager manPlayer2;
        QNetworkRequest requette(QUrl("http://localhost:8080/recupJoueur2"));
        QString ua1("HttpRequestDemo/0.1 (Win64) Qt/5.7");
        requette.setHeader(QNetworkRequest::UserAgentHeader, QVariant(ua));
        QNetworkReply* reply2 = man.get(requette) ;

        QObject::connect(reply2, &QNetworkReply::finished, [&](){
            QString contenue = reply2->readAll();

            qDebug() << " nom joueur 2 " << contenue;

            player2.name = contenue;

            qDebug() << player2.name;

        });

    bool ok;
    QInputDialog::getText(this, tr("Player Two"), tr("Entrer Votre Nom"), QLineEdit::Normal, "", &ok);


    player2.score = 0;
    if (player.piece == 'X'){
        player2.piece = 'O';
    } else {
        player2.piece = 'X';
    }

    playerTurn = 1;


    updatescore();
    updateStatus();
    updateBoard();



        QNetworkAccessManager manPlayer5;
        QNetworkRequest requette5(QUrl("http://localhost:8080/renvoieCoupAdversaire"));
        QString ua14("HttpRequestDemo/0.1 (Win64) Qt/5.7");
        requette.setHeader(QNetworkRequest::UserAgentHeader, QVariant(ua));
        QNetworkReply* reply5 = man.get(requette) ;

        QEventLoop loop;
        QObject::connect(reply2, &QNetworkReply::finished, [&]()

        {
            QString contenue = reply2->readAll();

            qDebug() << contenue;

        });



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
        grille[y][x] = player.piece;
        playerTurn = 2;
        qDebug() << "player turn : "  << playerTurn;
       // FreezeBoard();
        updateStatus();
        updateBoard();
    }
    else
    {
        grille[y][x] = player2.piece;
        playerTurn = 1;
        qDebug() << "player turn : "  << playerTurn;
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

void MainWindow::player_Pseudo()
{
    QNetworkAccessManager *man3 = new QNetworkAccessManager(this);

    bool ok;
    player.name = QInputDialog::getText(this, tr("Player One"), tr("Entrer Votre Nom"), QLineEdit::Normal, "", &ok);

    if(player.name.size()==0)
        player.name = "Player 1";


    const QUrl url2(QStringLiteral("http://localhost:8080/receptionJoueur"));
    QNetworkRequest request2(url2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString rawJSON = "{\"name\":\"" + player.name + "\"}";

    QByteArray jsonPlayer(rawJSON.toLocal8Bit());
    QNetworkReply *reply3 = man3->post(request2, jsonPlayer);

    QObject::connect(reply3, &QNetworkReply::finished, [=](){
        if(reply3->error() == QNetworkReply::NoError){

            QString contents = QString::fromUtf8(reply3->readAll());
            qDebug() << "content : " << contents;

            if (contents == "X1")
            {
                player.piece = 'X';
                playerTurn = 1;
                qDebug() << "vous etes le premier joueur" ;

            }else{
                player.piece = 'O';
                playerTurn = 1;
                qDebug() << "vous etes le second joueur" ;
            }
            qDebug() << player.piece;

        }
        else{
            QString err = reply3->errorString();
            qDebug() << err;
        }
        reply3->deleteLater();
    });
}

void MainWindow::envoie_position(int x, int y)
{
    QString positionX = QString::number(x);
    QString positionY = QString::number(y);

    QNetworkAccessManager *man3 = new QNetworkAccessManager(this);

    const QUrl url2(QStringLiteral("http://localhost:8080/positiongrille"));
    QNetworkRequest request2(url2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //QString Jsoncoor = "{\"positionX\":\"" + positionX + "\"positionY\":\"" + positionY + "\"}";
    //QString Jsoncoor = "{\"positionX\":\" 2 \"positionY\":\" 0\"}";

     QString data("{\"positionX\":\"" + positionX +"\",\"positionY\":\"" + positionY +"\"}");

//    positionY\":\"" + pos

    QByteArray jsonPositions(data.toLocal8Bit());
    QNetworkReply *reply3 = man3->post(request2, jsonPositions);

    QObject::connect(reply3, &QNetworkReply::finished, [=](){
        if(reply3->error() == QNetworkReply::NoError){}

        QString reponse = QString::fromUtf8(reply3->readAll());
        qDebug() << "reponse : " << reponse;
    });

}


void MainWindow::updateStatus()
{
    if (PlayerWon(player))
    {
        ui->label_status->setText(player.name + " WON!");
        Gagnant = 1;
        player.score++;
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
        ui->label_status->setText(player.name + "'s turn");
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
    envoie_position(0,0);
}

void MainWindow::on_pushButton_2_clicked()
{
    playerAction(1, 0);
    envoie_position(1, 0);
}

void MainWindow::on_pushButton_3_clicked()
{
    playerAction(2, 0);
    envoie_position(2, 0);
}

void MainWindow::on_pushButton_4_clicked()
{
    playerAction(0, 1);
    envoie_position(0, 1);
}

void MainWindow::on_pushButton_5_clicked()
{
    playerAction(1, 1);
    envoie_position(1, 1);
}

void MainWindow::on_pushButton_6_clicked()
{
    playerAction(2, 1);
    envoie_position(2, 1);
}

void MainWindow::on_pushButton_7_clicked()
{
    playerAction(0, 2);
    envoie_position(0, 2);
}

void MainWindow::on_pushButton_8_clicked()
{
    playerAction(1, 2);
    envoie_position(1, 2);
}

void MainWindow::on_pushButton_9_clicked()
{
    playerAction(2, 2);
    envoie_position(2, 2);
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
    ui->label_1->setText(QString(player.piece) + ": " + player.name + " - " + QString::number(player.score));
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

    QNetworkAccessManager *man3 = new QNetworkAccessManager(this);

    const QUrl url2(QStringLiteral("http://localhost:8080/resetGrille"));
    QNetworkRequest request2(url2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     QString data("reset grille");

    QByteArray jsonPositions(data.toLocal8Bit());
    QNetworkReply *reply3 = man3->post(request2, jsonPositions);

    QObject::connect(reply3, &QNetworkReply::finished, [=](){
        if(reply3->error() == QNetworkReply::NoError){}

        QString reponse = QString::fromUtf8(reply3->readAll());
        qDebug() << "reponse : " << reponse;
    });




}
