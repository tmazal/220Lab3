import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.Timer;

/**
 * Do not modify this file without permission from your TA.
 **/
public class Controller {

	private Model model;
	private View view;
	
	private JButton toggleRunButton;
    private JButton reverseButton;
    private ActionListener drawActionEvent;
    private ActionListener reverseActionEvent;
    private Action drawAction;
    private Timer t;
	
	public Controller(){
		view = new View();
		model = new Model(view.getWidth(), view.getHeight(), view.getImageWidth(), view.getImageHeight());
		view.makeFrame();
		toggleRunButton = view.getToggleRunButton();
		reverseButton = view.getReverseButton();
		drawActionEvent = new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				// pause/unpause the running
				if(model.getRunning()){
					System.out.println("You paused the animation");
				}
				else{
					System.out.println("You started the animation");
				}
				model.startOrStop(t);
			}
    		
    	};
    	reverseActionEvent = new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				// pause/unpause the running
				System.out.println("You pressed the reverse button");
				model.reverse();//Reverse the flags(and direction)
				view.update(model.getX(), model.getY(), model.getDirect());//Updates the view
			}
    		
    	};
    	toggleRunButton.addActionListener(drawActionEvent);
    	reverseButton.addActionListener(reverseActionEvent);
    	
	}
	
    //run the simulation
	public void start(){
		drawAction = new AbstractAction(){
			@Override
			public void actionPerformed(ActionEvent e) {
				//System.out.println(model.getRunning());
				if(model.getRunning()){
					model.updateLocationAndDirection();
					System.out.println("Direction: " + model.getDirect() + "   X: " + model.getX() + " Y: " + model.getY());
					view.update(model.getX(), model.getY(), model.getDirect()); //Updates the view
				}
				else if(!model.getRunning()){
					//Don't do anything, the game is paused
				}
			}
    	 };
		EventQueue.invokeLater(new Runnable(){
			@Override
			public void run() {
				t = new Timer(view.getDrawDelay(),drawAction);
				t.start();
			}
			
		});
		/*for(int i = 0; i < 1000; i++)
		{	
			//increment the x and y coordinates, alter direction if necessary
			model.updateLocationAndDirection();
			System.out.println("Direction: " + model.getDirect() + "   X: " + model.getX() + " Y: " + model.getY());
			view.update(model.getX(), model.getY(), model.getDirect()); //Updates the view
		}*/
	}
}
