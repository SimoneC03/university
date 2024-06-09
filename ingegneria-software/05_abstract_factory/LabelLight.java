import java.awt.Color;

/*
 * This class represents a Product which implements the Label AbstractProduct interface
 * and can be created by a ConcreteFactory.
 * 
 * This implementation exposes a light version of the Label
 */
public class LabelLight implements Label {
    @Override
    public String getText() {
        return "Light Theme";
    }

    @Override
    public Color getColor() {
        return new Color(42, 42, 42);
    }
}
