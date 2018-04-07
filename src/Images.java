import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public enum Images {
	
	NORTHEAST(0),
	SOUTHEAST(1),
	SOUTHWEST(2),
	NORTHWEST(3);
	
    private BufferedImage bufferedImageNE;
    private BufferedImage bufferedImageNW;
    private BufferedImage bufferedImageSE;
    private BufferedImage bufferedImageSW;
	
	private BufferedImage image;
    
	private Images(int s){
		BufferedImage bufferedImage = null;
    	try {
    		bufferedImageNE = ImageIO.read(new File("images/orc_forward_northeast.png")); 
    		bufferedImageNW = ImageIO.read(new File("images/orc_forward_northwest.png"));
    		bufferedImageSE = ImageIO.read(new File("images/orc_forward_southeast.png"));
    		bufferedImageSW = ImageIO.read(new File("images/orc_forward_southwest.png"));
    	switch (s) {
    	case 0: 
    		bufferedImage = bufferedImageNE;
    		break;
    	case 1:
    		bufferedImage = bufferedImageSE;
    		break;
    	case 2: 
    		bufferedImage = bufferedImageSW;
    		break;
    	case 3: 
    		bufferedImage = bufferedImageNW;
    		break;
    	}
    	}
    	catch (IOException e) {
    		e.printStackTrace();
    	}
    	image = bufferedImage;
	}
	public BufferedImage getImage() {
		return image;
	}
	

}
