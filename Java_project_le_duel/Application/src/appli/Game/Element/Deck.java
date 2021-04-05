package appli.Game.Element;

import java.util.ArrayList;
import java.util.Stack;

public class Deck {

    private Stack<Card> cards;

    public Deck() {
        cards = new Stack<>();
        createDeck();
    }

    private void createDeck() {
        ArrayList<Card> allCards = new ArrayList<>();

        for(int i = 2; i < 60; i++) {
            allCards.add(new Card(i));
        }

        int random;

        for(int i = 0; i < 58; i++) {
            random = (int) (Math.random() * (58 - i));
            cards.push(allCards.get(random));
            allCards.remove(random);
        }
    }

    public Card drawCard() {
        return cards.pop();
    }

    public int nbCardsInDeck() {
        return cards.size();
    }

}
