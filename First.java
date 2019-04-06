import javax.swing.*;
import java.awt.*;

public class First {
				public static void main(String [] args) {
								JFrame frame = new JFrame("My First Frame");
								frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
								frame.getContentPane().setLayout(new BorderLayout());
								frame.getContentPane().add(new JLabel("I Love Swing"), BorderLayout.CENTER);
								frame.getContentPane().add(new JPanel(),BorderLayout.SOUTH);

								frame.pack();
								frame.setVisible(true);
								System.out.println("\nTesting from JAVA\n");
								System.out.println("\nTesting from JAVA\n");
								System.out.println("\nTesting from JAVA\n");

				}
}
