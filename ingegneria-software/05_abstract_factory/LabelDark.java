import java.awt.Color;

/*
 * This class represents a Product which implements the Label AbstractProduct interface
 * and can be created by a ConcreteFactory.
 * 
 * This implementation exposes a dark version of the Label
 */

public class LabelDark implements Label {
    @Override
    public String getText() {
        return "Dark Theme";
    }

    @Override
    public Color getColor() {
        return new Color(226, 226, 226);
    }
}
