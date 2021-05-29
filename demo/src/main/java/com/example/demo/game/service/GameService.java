package com.example.demo.game.service;


import com.example.demo.game.model.Game;
import com.example.demo.game.model.Joueur;
import com.example.demo.game.repository.JoueurRepository;
import org.springframework.stereotype.Service;

@Service
public class GameService {

    private final JoueurRepository joueurRepository;

    public GameService(JoueurRepository joueurRepository) {
        this.joueurRepository = joueurRepository;
    }

    public Game setPlayer(Game game, String player) {

        if(game.joueur1 == null){
            System.out.println("setplayer");
            game.setPlayerOne(player);
            game.setPlayerTurn(1);
        } else {
            game.setPlayerTwo(player);
        }
        System.out.println(game.joueur1); //affiche info du premier joueur
        System.out.println(game.joueur1.piece);
        System.out.println(game.joueur2); //affiche info du second joueur
        System.out.println(game);
        return game;
    }

    public Game getGameinfo(Game game){
        return game;
    }

    public void updateGrille(Game game, int x, int y)
    {
        game.updateGrille(x, y);
    }


    public void GeneratePlayers(){
        Joueur joueur = new Joueur("Jean", 0, "O");
        joueurRepository.save(joueur);
        joueur = new Joueur("Toto", 0, "X");
        joueurRepository.save(joueur);
    }

    public void AddPlayer(Game game){

        if (game.joueur1 != null && game.joueur2 == null)
        {
            Joueur joueur = new Joueur(game.joueur1.name, game.joueur1.score, game.joueur1.piece);
            joueurRepository.save(joueur);
        } else if (game.joueur1 != null && game.joueur2 != null) {
            Joueur joueur = new Joueur(game.joueur2.name, game.joueur2.score, game.joueur2.piece);
            joueurRepository.save(joueur);
        }
    }


}