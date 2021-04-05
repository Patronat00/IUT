package appli.Game;

import appli.Game.Element.Card;
import appli.Game.Element.Deck;
import appli.Game.Element.Hand;

import java.util.Stack;

public class Player implements Cloneable {

    private String name;
    private Stack<Card> asc;
    private Stack<Card> desc;
    private Hand hand;
    private Deck deck;

    public Player(String name) {
        this.name = name;

        asc = new Stack<>();
        desc = new Stack<>();

        asc.push(new Card(1));
        desc.push(new Card(60));

        hand = new Hand();
        deck = new Deck();
        drawNumberOfCards(6);
    }

    public void drawNumberOfCards(int nbOfCards) {
        for(int i = 0; i < nbOfCards; i++) {
            hand.addCard(deck.drawCard());
        }
    }

    public String getName() {
        return name;
    }

    public Stack<Card> getAsc() {
        return asc;
    }

    public Stack<Card> getDesc() {
        return desc;
    }

    public Hand getHand() {
        return hand;
    }

    public Deck getDeck() {
        return deck;
    }

    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    public String getPlayerInfos() {
        String playerName = name.equals("SUD") ? name + " " : name;
        String ascStackNumber = asc.peek().toString();
        String descStackNumber = desc.peek().toString();
        String nbCardsInHand = Integer.toString(hand.nbCardsInHand());
        String nbCardsInDeck = Integer.toString(deck.nbCardsInDeck());

        return  playerName
                + " ^[" + ascStackNumber + "]"
                + " v[" + descStackNumber + "]"
                + " (m" + nbCardsInHand
                + "p" + nbCardsInDeck + ")";
    }

    public String displayHand() {
        return "cartes " + name + " " + hand.displayHand();
    }

}
