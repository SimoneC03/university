import java.awt.Container;

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
