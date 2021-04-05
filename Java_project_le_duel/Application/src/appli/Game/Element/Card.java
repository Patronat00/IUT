package appli.Game.Element;

public class Card implements Comparable<Card> {

    private int cardNumber;

    public Card(int cardNumber) {
        this.cardNumber = cardNumber;
    }

    public int getCardNumber() {
        return cardNumber;
    }

    @Override
    public String toString() {
        return cardNumber < 10 ? "0" + cardNumber : Integer.toString(cardNumber);
    }

    @Override
    public int compareTo(Card card) {
        return (Integer.compare(cardNumber, card.getCardNumber()));
    }

}
