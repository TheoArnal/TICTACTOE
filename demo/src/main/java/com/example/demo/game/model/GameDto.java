package com.example.demo.game.model;

public class GameDto {

    public int getPlayerTurn() {
        return playerTurn;
    }

    public void setPlayerTurn(int playerTurn) {
        this.playerTurn = playerTurn;
    }

    public Boolean[][] getGrilleWin() {
        return grilleWin;
    }

    public void setGrilleWin(Boolean[][] grilleWin) {
        this.grilleWin = grilleWin;
    }

    public int playerTurn;
    public int winner;

    public int getWinner() {
        return winner;
    }

    public void setWinner(int winner) {
        this.winner = winner;
    }

    public String[][] getGrille() {
        return grille;
    }

    public void setGrille(String[][] grille) {
        this.grille = grille;
    }

    public String grille[][];
    public Boolean grilleWin[][];

    public GameDto(String grille[][], Boolean grilleWin[][], int playerTurn, int winner, String x, String y){
        this.grille = grille;
        this.grilleWin = grilleWin;
        this.playerTurn = playerTurn;
        this.winner = winner;
        this.positionX = x;
        this.positionY = y;
    }

    public String positionX;

    public String getX() {
        return positionX;
    }

    public void setX(String x) {
        this.positionX = x;
    }

    public String getY() {
        return positionY;
    }

    public void setY(String y) {
        this.positionY = y;
    }

    public String positionY;


}
