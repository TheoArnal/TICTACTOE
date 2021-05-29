package com.example.demo.game.model;


import javax.persistence.*;


@Entity
public class Joueur {

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

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    public String name;
    public Integer score;
    public String piece;



    public Joueur(String name, int score, String piece)
    {
        this.name = name;
        this.score = score;
        this.piece = piece;
    }

    @Override
    public String toString(){
        return "Joueur{" +
                "nom ='" + name + '\'' +
                ", score='" + score + '\'' +
                ", piece='" + piece + '\'' +
                "}";
    }

}
