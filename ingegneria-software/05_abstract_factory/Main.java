import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.Container;

/*
 * This class represents the Client that uses only interfaces declared by the AbstractFactory
 * and AbstractProduct.
 * 
 * AbstractFactory is implemented by ConcreteFactoryDark and ConcreteFactoryLight classes
 * which can be used to change theme colors
 * 
 * AbstractProduct has more implementations in different classes like Frame and Label.
 */

public class Main {
    public static void main(String[] args) {
        // Theme object (dark or light)
        AbstractFactory theme = new ConcreteFactoryDark();

        // Create a frame (window)
        Frame themeFrame = theme.getFrame();
        JFrame frame = new JFrame(themeFrame.getText());
        Container c = frame.getContentPane();
        c.setBackground(themeFrame.getBackgroundColor());

        // Create a label text
        Label themeLabel = theme.getLabel();
        JLabel label = new JLabel(themeLabel.getText());
        label.setForeground(themeLabel.getColor());
        
        // Add the label to the frame
        c.add(label);

        // Set frame properties
        frame.setSize(300, 200); // Set size (width, height) in pixels
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Close operation
        frame.setVisible(true); // Make the frame visible
    }
}