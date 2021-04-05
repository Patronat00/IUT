package appli.Game.Element;

import java.util.ArrayList;
import java.util.Collections;

public class Hand {

    private ArrayList<Card> cards;

    public Hand() {
        cards = new ArrayList<>();
    }

    public void addCard(Card card) {
        cards.add(card);
    }

    public void removeCard(int nbOfCard) {
        for(int i =0; i < cards.size(); i++) {
            if(cards.get(i).getCardNumber() == nbOfCard) {
                cards.remove(i);
                break;
            }
        }
    }

    public int nbCardsInHand() {
        return cards.size();
    }

    public String displayHand() {
        Collections.sort(cards);
        
        String cardsListing = "{ ";

        for(int i = 0; i < cards.size(); i++) {
            cardsListing += cards.get(i).toString() + " ";
        }

        return cardsListing + "}";
    }

    public boolean isInHand(int nbToPut) {
        for(int i = 0; i < cards.size(); i++) {

            if(nbToPut == cards.get(i).getCardNumber()) {
                return true;
            }

        }

        return false;
    }
}
