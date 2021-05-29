package com.example.demo.game.model;

public class JoueurDto {

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public String getPiece() {
        return piece;
    }

    public void setPiece(String piece) {
        this.piece = piece;
    }

    public String name;
    public Integer score;
    public String piece;

    public JoueurDto(String name, int score, String piece)
    {
        this.name = name;
        this.score = score;
        this.piece = piece;
    }

}
