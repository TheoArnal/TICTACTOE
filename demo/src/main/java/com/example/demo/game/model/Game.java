package com.example.demo.game.model;
import com.example.demo.game.model.Joueur;
import com.fasterxml.jackson.annotation.JsonGetter;

public class Game {

    public String data2 = "yolo";

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    private long id;
    public Boolean grilleWin[][] ;
    public String grille2[][] = {{" "," "," "}, {" "," "," "}, {" "," "," "}} ;
    public int playerTurn;




    public Joueur getJoueur1() {
        return joueur1;
    }

    public void setJoueur1(Joueur joueur1) {
        this.joueur1 = joueur1;
    }

    public Joueur getJoueur2() {
        return joueur2;
    }

    public void setJoueur2(Joueur joueur2) {
        this.joueur2 = joueur2;
    }

    public Joueur joueur1 = null;
    public Joueur joueur2 = null;

    public Game() {

    }

    public void initialiseGrille(String value){
        for(int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                grille2[y][x] = value;
            }
        }
    }

    public void updateGrille(int x, int y)
    {
        if (playerTurn == 1)
        {
            grille2[x][y] = joueur1.piece;
        } else {
            grille2[x][y] = joueur2.piece;
        }

    }

    public void setPlayerOne(String j1)
    {
        if (j1 == ""){
            j1 = "Player 1";
        }
        joueur1 = new Joueur(j1, 0, "X");
    }

    public void setPlayerTwo(String j2){
        if (j2 == ""){
            j2 = "Player 2";
        }
        joueur2 = new Joueur(j2, 0, "0");
    }


    public Boolean[][] getGrilleWin() {
        return grilleWin;
    }

    public void setGrilleWin(Boolean[][] grilleWin) {
        this.grilleWin = grilleWin;
    }

    public int getWinner() {
        return winner;
    }

    public void setWinner(int winner) {
        this.winner = winner;
    }

    public int winner;

    public int getPlayerTurn() {
        return playerTurn;
    }

    public void setPlayerTurn(int playerTurn) {
        this.playerTurn = playerTurn;
    }

    public Game(String[][] grille2, Boolean[][] grilleWin, int winner, int playerTurn, Joueur joueur1, Joueur joueur2) {
        this.grille2 = grille2;
        //this.grilleWin = grilleWin;
        this.winner = winner;
        this.playerTurn = playerTurn;
        this.joueur1 = joueur1;
        this.joueur2 = joueur2;

    }

    @Override
    public String toString() {
        return "Game{" +
                "test='" + data2 + '\'' +
                ", grille=" + grille2+ '\'' +
                ", joueur1=" + joueur1 + '\'' +
                ", joueur2=" + joueur2 + '\'' +
                ", playerTurn=" + playerTurn + '\'' +
                '}';
    }

    public String getData2() { return data2; }
    public void setData2(String Data2) { this.data2 = Data2; }

    @JsonGetter("grille2")
    public String[][] getGrille2() { return grille2; }
    public void setGrille2(String[][] grille2) { this.grille2 = grille2;}

}


