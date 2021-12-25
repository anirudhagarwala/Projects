import java.util.Date;
import java.lang.Math;
public class Rectangle extends GeometricObject {

  
    private double width;
    private double height;
    {
        this.width = 1;
        this.height = 1;
        super.x = 0;
        super.y = 0;
        super.color = "white";
    }

    public Rectangle(){

    }
    public Rectangle(double Width, double Height){
        setWidth(Width);
        setHeight(Height);
    }
    public Rectangle(double Width, double Height, double X, double Y, double Theta){
        setWidth(Width);
        setHeight(Height);
        super.x = X;
        super.y = Y;
        super.theta = Theta;
    }
    
    public double getWidth(){
        return this.width;
    }
    public double getHeight(){
        return this.height;
    }
    public void setWidth(double Width){
        this.width = Width;
    }
    public void setHeight(double Height){
        this.height = Height;
    }

    public double getArea(){
        return getHeight()*getWidth();
    }
    public double getPerimeter(){
        return 2*(getHeight()+getWidth());
    }
    public void changeColor(String Color){
        super.color = Color;
    }
    public String toString(){
      /*  String lala = "(" + String.format("%.02f", super.getX()) + "," + String.format("%.02f", super.getY()) + ")";
        lala = lala + "," + "(" + String.format("%.02f", getX()+getWidth()*Math.cos(this.getTheta()))+","+String.format("%.02f", getY()+getWidth()*Math.sin(this.getTheta()))+")";
        double prevX = getX()+getWidth()*Math.cos(this.getTheta());
        double prevY = getY()+getWidth()*Math.sin(this.getTheta());
        lala = lala + "," + "(" + String.format("%.02f", prevX-getHeight()*Math.sin(this.getTheta()))+","+String.format("%.02f", prevY-getHeight()*Math.sin(this.getTheta()))+")";
*/
        double prevX = getX();
        double prevY = getY();
        double secX = getX() + getWidth()*Math.cos(theta);
        double secY = getY() + getWidth()*Math.sin(theta);
        double thiX = secX - getHeight()*Math.sin(theta);
        double thiY = secY + getHeight()*Math.cos(theta);
        double fouX = getX() - getHeight()*Math.sin(theta);
        double fouY = getY() + getHeight()*Math.cos(theta);
        String lll = "(" + String.format("%.02f", prevX) + "," + String.format("%.02f", prevY) + ")," + "(" + String.format("%.02f", secX) + "," + String.format("%.02f", secY) + ")," + "(" + String.format("%.02f", thiX) + "," + String.format("%.02f", thiY) + ")," + "(" + String.format("%.02f", fouX) + "," + String.format("%.02f", fouY) + ")";
        
        return lll;
    }
    public String getPara(){
        return width + "," + height;
    }

}
