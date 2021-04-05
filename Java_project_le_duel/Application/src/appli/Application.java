package appli;

import appli.Game.Element.Card;
import appli.Game.Game;
import appli.Game.Player;

import java.util.Scanner;

public class Application {

    public static void main(String[] args) throws CloneNotSupportedException {
        Game game = new Game();
        String winner = "";
        boolean regulatoryMove;

        while(true) {
            System.out.println(game.getNord().getPlayerInfos());
            System.out.println(game.getSud().getPlayerInfos());

            if(game.isNordPlayerTurn()) {
                System.out.println(game.getNord().displayHand());
            } else {
                System.out.println(game.getSud().displayHand());
            }

            regulatoryMove = readPlayerInput(game);

            if(game.isNordPlayerTurn() && game.getNord().getHand().nbCardsInHand() == 0 && game.getNord().getDeck().nbCardsInDeck() == 0) {
                winner = game.getNord().getName();
                break;

            } else if(!game.isNordPlayerTurn() && game.getSud().getHand().nbCardsInHand() == 0 && game.getSud().getDeck().nbCardsInDeck() == 0) {
                winner = game.getSud().getName();
                break;

            } else if(game.isNordPlayerTurn() && !regulatoryMove) {
                winner = game.getSud().getName();
                break;

            } else if(!game.isNordPlayerTurn() && !regulatoryMove){
                winner = game.getNord().getName();
                break;

            }

            int nbCardsToDraw = 2;

            if(nbCardPlacedToEnemy > 0) {
                nbCardsToDraw = 6 - game.getNord().getHand().nbCardsInHand();
            }

            if(game.isNordPlayerTurn()) {
                game.getNord().drawNumberOfCards(nbCardsToDraw);
            } else {
                game.getSud().drawNumberOfCards(nbCardsToDraw);
            }

            game.changePlayerTurn();
        }

        System.out.println("partie finie, " + winner + " a gagné");
    }

    private static int nbCardPlaced = 0;
    private static int nbCardPlacedToEnemy = 0;

    private static boolean readPlayerInput(Game game) throws CloneNotSupportedException {
        boolean inputError = false;
        boolean finish = false;

        Scanner scanner = new Scanner(System.in);

        while(!finish) {
            finish = true;

            if(!inputError)
                System.out.print("> ");
            else
                System.out.print("#> ");

            String input = scanner.nextLine();

            String[] tabInput = input.split(" ");

            Player nord = (Player) game.getNord().clone();
            Player sud = (Player) game.getSud().clone();

            nbCardPlaced = 0;
            nbCardPlacedToEnemy = 0;

            boolean asc;
            boolean onCurrentPlayerStack;

            for (String s : tabInput) {
                try {
                    if(s.length() > 4) {
                        inputError = true;
                        finish = false;
                        break;
                    }

                    int nbToPut = Integer.parseInt(s.substring(0, 2));
                    char stackDirection = s.charAt(2);

                    if(stackDirection == '^') {
                        asc = true;
                    } else if(stackDirection == 'v') {
                        asc = false;
                    } else {
                        inputError = true;
                        finish = false;
                        break;
                    }

                    onCurrentPlayerStack = true;

                    if(s.length() == 4) {
                        if(s.charAt(3) == '\'') {
                            onCurrentPlayerStack = false;
                        } else {
                            inputError = true;
                            finish = false;
                            break;
                        }

                    }

                    if(!nbToPutInHand(game, nbToPut)) {
                        inputError = true;
                        finish = false;
                        break;
                    }

                    boolean impossibleMove;

                    if(game.isNordPlayerTurn()) {
                        impossibleMove = isImpossibleMove(nord, sud, asc, onCurrentPlayerStack, nbToPut);
                    } else {
                        impossibleMove = isImpossibleMove(sud, nord, asc, onCurrentPlayerStack, nbToPut);
                    }

                    if(impossibleMove || nbCardPlacedToEnemy > 1) {
                        inputError = true;
                        finish = false;
                        break;
                    }

                } catch (Exception e) {
                    inputError = true;
                    finish = false;
                    break;
                }
            }
        }

        return nbCardPlaced >= 2;
    }

    private static boolean isImpossibleMove(Player nord, Player sud, boolean asc, boolean onCurrentPlayerStack, int nbToPut) {
        boolean impossibleMove = false;

        // TODO : gestion de l'erreur potentielle pour la main et la pile du player

        if(asc) {
            if(onCurrentPlayerStack) {
                if(nord.getAsc().peek().getCardNumber() < nbToPut
                        || nord.getAsc().peek().getCardNumber() - 10 == nbToPut) {
                    nord.getAsc().push(new Card(nbToPut));
                    nord.getHand().removeCard(nbToPut);
                    nbCardPlaced++;
                } else { impossibleMove = true; }
            } else {
                if(sud.getAsc().peek().getCardNumber() > nbToPut) {
                    sud.getAsc().push(new Card(nbToPut));
                    sud.getHand().removeCard(nbToPut);
                    nbCardPlaced++;
                    nbCardPlacedToEnemy++;
                } else { impossibleMove = true; }
            }
        } else {
            if(onCurrentPlayerStack) {
                if(nord.getDesc().peek().getCardNumber() > nbToPut
                        || nord.getDesc().peek().getCardNumber() + 10 == nbToPut) {
                    nord.getDesc().push(new Card(nbToPut));
                    nord.getHand().removeCard(nbToPut);
                    nbCardPlaced++;
                } else { impossibleMove = true; }
            } else {
                if(sud.getDesc().peek().getCardNumber() < nbToPut) {
                    sud.getDesc().push(new Card(nbToPut));
                    sud.getHand().removeCard(nbToPut);
                    nbCardPlaced++;
                    nbCardPlacedToEnemy++;
                } else { impossibleMove = true; }
            }
        }
        return impossibleMove;
    }

    private static boolean nbToPutInHand(Game game, int nbToPut) {
        if(game.isNordPlayerTurn()) {
            return game.getNord().getHand().isInHand(nbToPut);
        }

        return game.getSud().getHand().isInHand(nbToPut);
    }

}
