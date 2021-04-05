package appli.Game;

public class Game {

    private Player nord;
    private Player sud;
    private boolean nordPlayerTurn;

    public Game() {
        nord = new Player("NORD");
        sud = new Player("SUD");
        nordPlayerTurn = true;
    }

    public Player getNord() {
        return nord;
    }

    public Player getSud() {
        return sud;
    }

    public void setNord(Player nord) {
        this.nord = nord;
    }

    public void setSud(Player sud) {
        this.sud = sud;
    }

    public boolean isNordPlayerTurn() {
        return nordPlayerTurn;
    }

    public void changePlayerTurn() {
        nordPlayerTurn = !nordPlayerTurn;
    }
}
