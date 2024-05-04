import java.awt.Container;

/*
 * This class represents a ConcreteFactory and implements the operations to create
 * all the families of objects for a dark theme.
 */

public class ConcreteFactoryDark implements AbstractFactory {

    @Override
    public Label getLabel() {
        return new LabelDark();
    }

    @Override
    public Frame getFrame() {
        return new FrameDark();
    }
}
