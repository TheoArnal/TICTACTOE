package com.example.demo.game.controller;

import com.example.demo.game.model.Game;
import com.example.demo.game.model.GameDto;
import com.example.demo.game.model.Joueur;
import com.example.demo.game.model.JoueurDto;
import com.example.demo.game.service.GameService;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;


@RestController
public class GameController {

    private Game instance = null;


    GameService gameService;
    public GameController(GameService gameService) { this.gameService = gameService; }

    @RequestMapping(value="/waiting", method = RequestMethod.GET)
    public Game infoGame(Game game) {
        return instance;
    }

    @RequestMapping(value = "/retourneGrille",
                    method = RequestMethod.GET,
                    produces = {"application/json", "application/xml"}
                    )
    public String[][] Grille(){
        System.out.println(instance.grille2);
        return instance.grille2;
    }

    @RequestMapping(value = "/recupJoueur2",
                    method = RequestMethod.GET,
                    produces = {"application/json", "application/xml"})
    public String returnJoueur2()
    {
        if ( instance.joueur1 != null) {
            if (instance.joueur2 == null) {
                return " ";
            } else {
                return instance.joueur1.name;
            }
        } else {
            return " ";
        }
    }

    @RequestMapping(value = "/renvoieCoupAdversaire",
                    method = RequestMethod.GET,
                    produces = {"application/json", "application/xml"})
    public String ReturnCoupAdversaire(){

        //if( instance.playerTurn = )

        return " ";
    }


    @GetMapping("/generatePlayer")
    @ResponseStatus(HttpStatus.OK)
    public void generatePlayers() {
        gameService.GeneratePlayers();
    }

    ////////////////////////////////////////////////////    initialise les joueurs    ///////////////////////////////////////////////////
    @PostMapping(
            value = "/receptionJoueur",
            consumes = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE},
            produces = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE})
    public String receptionJoueur(@RequestBody JoueurDto player) {
        if (instance == null){
            instance = new Game();
        }
        instance = gameService.setPlayer(instance, player.name);
        gameService.AddPlayer(instance);

        if (player.name.equals(instance.joueur1.name))
        {
            return instance.joueur1.piece + instance.playerTurn;

        }else{
            return instance.joueur2.piece + instance.playerTurn;
        }

    }


    @PostMapping(
            value = "/positiongrille",
            consumes = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE},
            produces = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE}
    )
    public String receptionPosition(@RequestBody GameDto position){

        System.out.println(position.getX());
        System.out.println(position.getY());

        int posX = Integer.parseInt(position.positionX);
        int posY = Integer.parseInt(position.positionY);

        gameService.updateGrille(instance, posX, posY);
        System.out.println(instance.grille2);

        if (instance.playerTurn == 1)
        {
            instance.setPlayerTurn(2);
        } else {
            instance.setPlayerTurn(1);
        }

        return "position ajouter";
    }

    @PostMapping(
            value = "/resetGrille",
            consumes = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE},
            produces = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE})
    public String resetGrille(@RequestBody String value) {

        System.out.println(value);

        if (value == "reset grille"){

            for(int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    instance.grille2[y][x] = " ";
                }
            }
        }
        return "Grille Réinitialiser";

    }


}
