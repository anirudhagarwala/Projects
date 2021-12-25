import java.util.Date;
import java.lang.Math;
public class Circle extends GeometricObject {


    private double radius;
    {
    super.color = "white";
    super.x = 0;
    super.y = 0;
    setRadius(1.0);
    }
    public Circle(){
        
    }
    public Circle(double Radius){
        setRadius(Radius);
    }
    public Circle(double Radius, double X, double Y){
        setRadius(Radius);
        super.x = X;
        super.y = Y;
    }

    public double getRadius(){
        return this.radius;
    }
    public void setRadius(double Radius){
        this.radius = Radius;
    }

    public double getArea(){
        return radius*radius*Math.PI;
    }
    public double getPerimeter(){
        return 2*Math.PI*radius;
    }

    public void printCircle(){

    }

    public String toString(){
        return "("+String.format("%.02f", super.getX())+","+String.format("%.02f", super.getY())+"),r:"+String.format("%.02f", this.getRadius());
    }
    public String getPara(){
        return Double.toString(radius);
    }
}
