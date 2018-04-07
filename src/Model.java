import javax.swing.Timer;

/**
 * Model: Contains all the state and logic
 * Does not contain anything about images or graphics, must ask view for that
 *
 * has methods to
 *  detect collision with boundaries
 * decide next direction
 * provide direction
 * provide location
 **/

public class Model {
	
	private int width;//Frame-width
	private int height;//Frame-height
	private int imageWidth;
	private int imageHeight;
	private int x;
	private int y = 38; //defined here to give space for the buttons
	private Direction direction;
	
	final private int xChange = 8;
	final private int yChange = 2;
	
	//Used to tell direction
	//Direction that orc begins moving is !north and east
	private boolean north = false;
	private boolean east = true;
	private boolean running = false;
	
	public Model(int width, int height, int imageWidth, int imageHeight) {
		this.width = width;
		this.height = height;
		this.imageWidth = imageWidth;
		this.imageHeight = imageHeight;
	}

	//Update position of the orc
	public void updateLocationAndDirection() { 
		//printTestInfo();
	
		/*
		 *                        North(-y)
		 *			
		 *
		 *				West(-x)		     East(+x)
		 *
		 *
		 *						  South(+y)
		 */
		
		changeFlags();

		//Update the x and y position
		if(north){
			//North
			y = y - yChange;
		}
		else{
			//south
			y = y + yChange;
		}
		if(east){
			//East
			x = x + xChange;
		}
		else{
			//West
			x = x - xChange;
		}
		//direction = getDirect();//Get the direction that the orc is moving
	}
	
	//This is required from the Controller - Gets the direction the orc is moving.(Uses flags to find direction)
	public Direction getDirect() { 
		
		changeFlags();//Update the flags based on the orc'c current position so it correctly chooses its direction
		//^ is this method needed? may be attribruting to one frame lag	
		//Change return the direction 
		if(north && east) {
			return Direction.NORTHEAST;
		}
		else if(north && !east){
			return Direction.NORTHWEST;
		}
		if(!north && east){
			return Direction.SOUTHEAST;
		}
		else if(!north && !east) {
			return Direction.SOUTHWEST;
		}
		else{
			//Should never be reached
			return Direction.SOUTH;
		}	
	}
	
	public void changeFlags(){
		
		if(x < 0)//West(Left) Wall               
		{
    		east = true;
    	}
    	else if((x + imageWidth) > width)//East(Right) Wall
    	{
    		east = false;
    	}
    	if(y - 38 < 0)//North Wall (The number is cutting out room for the buttons on the top of the frame)    
    	{
    		north = false;
    	}
    	else if((y + imageHeight) > height)//South Wall
    	{
    		north = true;
    	}	
	}
	
	public void reverse(){
		north = !north;
		east = !east;
		updateLocationAndDirection();
	}
	
	public void startOrStop(Timer t){
		running = !running;//Change state of being
		if(running){
			t.start();
		}
		else if(!running){
			t.stop();
		}
	}
	
	public void printTestInfo()
	{
		System.out.println("Direction: " + getDirect() + "  xLoc: " + x + " yLoc: " + y);
	}
	
	//Getters
	
	public int getX(){	
		return x;
	}
	public int getY(){
		return y;
	}
	public Boolean getRunning(){
		return running;
	}
	
	//public int getXChange() {return xChange;}
	
	//public int getYChange() {return yChange;}
	
	
}
