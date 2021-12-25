import java.lang.Math;

public class RegularPolygon extends GeometricObject {
    
    {
        super.color = "white";
        super.filled = false;
        
    }
    private int n = 3;
    private double side = 1;
    private double x = 0;
    private double y = 0;
    static int counter;

    //no-arg constructor
    RegularPolygon(){
        //takes in default values
        counter++;
    }

    RegularPolygon(int newN, double newSide){
        
        if((newN<3)&&(newSide<0)){
            this.x = 0;
            this.y = 0;
            counter++;      
        }else if((newN<3)&&(newSide>0)){
            this.side = newSide;
            this.x = 0;
            this.y = 0;
            counter++;      
        }else if((newN>3)&&(newSide<0)){
            this.n = newN;
            this.x = 0;
            this.y = 0;
            counter++;      
        }
        else{
            this.n = newN;
            this.side = newSide;
            this.x = 0;
            this.y = 0;
            counter++;
        }
    }

    RegularPolygon(int newN, double newSide, double newX, double newY){
        if((newN<3)&&(newSide<0)){
            this.x = newX;
            this.y = newY;
            counter++;      
        }else if((newN<3)&&(newSide>0)){
            this.side = newSide;
            this.x = newX;
            this.y = newY;
            counter++;      
        }else if((newN>3)&&(newSide<0)){
            this.n = newN;
            this.x = newX;
            this.y = newY;
            counter++;      
        }else{
            this.n = newN;
            this.side = newSide;
            this.x = newX;
            this.y = newY;
            counter++;
        }
    }
    RegularPolygon(String Color, boolean Filled, int newN, double newSide, double newX, double newY, double Theta){
        if((newN<3)&&(newSide<0)){
            this.x = newX;
            this.y = newY;
            super.color = Color;
            super.filled = Filled;
            super.theta = Theta;
            counter++;      
        }else if((newN<3)&&(newSide>0)){
            this.side = newSide;
            this.x = newX;
            this.y = newY;
            super.color = Color;
            super.filled = Filled;
            super.theta = Theta;
            counter++;      
        }else if((newN>3)&&(newSide<0)){
            this.n = newN;
            this.x = newX;
            this.y = newY;
            super.color = Color;
            super.filled = Filled;
            super.theta = Theta;
            counter++;      
        }else{
            this.n = newN;
            this.side = newSide;
            this.x = newX;
            this.y = newY;
            super.color = Color;
            super.filled = Filled;
            super.theta = Theta;
            counter++;
        }
    }
    int getN(){
        return n;
    }
    double getSide(){
        return this.side;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }

    public double getPerimeter(){
        return (double) getN()*getSide();
    }

    public double getArea(){
        double numerator = (double) getN()*getSide()*getSide();
        double denominator = 4*Math.tan(Math.PI/(double) getN());
        return numerator/denominator;
    }

    public String toString(){
        int numSides = getN();
        double sideSize = getSide();
        double angle = 2*Math.PI/numSides;
        String output;
        String firstV = "("+String.format("%.02f", getX())+","+String.format("%.02f", getY())+")";
        output = firstV + ",";
        
        String secV = "("+String.format("%.02f", getX()+getSide()*Math.cos(this.getTheta()))+","+String.format("%.02f", getY()+getSide()*Math.sin(this.getTheta()))+")";
        output = output + secV + ",";
        
        double prevX = getX()+getSide()*Math.cos(this.getTheta());
        double prevY = getY()+getSide()*Math.sin(this.getTheta());
        
        for(int i=1; i<=numSides-2;i++){
            String thiV = "("+String.format("%.02f", prevX + getSide()*Math.cos((i*angle)+this.getTheta()))+","+String.format("%.02f", prevY + getSide()*Math.sin((i*angle)+this.getTheta()))+")";
            prevX = prevX + getSide()*Math.cos((i*angle)+this.getTheta());
            prevY = prevY + getSide()*Math.sin((i*angle)+this.getTheta());
            if(i==numSides-2){
            output = output + thiV;}
            else{
                output = output + thiV + ",";
            }
            
        }
        
        return output;
    }
    public String getPara(){
        return n + "," + side + "," + x + "," + y;
    }
}
