public class Triangle extends GeometricObject{
    
    double side1=1.0;
    double side3 = 1.0;
    private double side2 = 1.0;
    {
    super.setColor("white");
    super.setFilled(false);
    super.x = 0;
    super.y = 0;
    super.theta = 0;
    }
    Triangle(){

    }
    Triangle(double Side1, double Side2, double Side3){
        this.side1 = Side1;
        this.side2 = Side2;
        this.side3 = Side3;
    }
    Triangle(double Side1, double Side2, double Side3, double X, double Y, double Theta){
        this.side1 = Side1;
        this.side2 = Side2;
        this.side3 = Side3;
        super.x = X;
        super.y = Y;
        super.theta = Theta;
    }
    Triangle(String Color, boolean Filled, double Side1, double Side2, double Side3, double X, double Y, double Theta){
        super.setColor(Color);
        super.setFilled(Filled);
        this.side1 = Side1;
        this.side2 = Side2;
        this.side3 = Side3;
        super.x = X;
        super.y = Y;
        super.theta = Theta;
    }

    void setSide1(double Side1){
        this.side1 = Side1;
    }
    void setSide2(double Side2){
        this.side2 = Side2;
    }
    void setSide3(double Side3){
        this.side3 = Side3;
    }

    double getSide1(){
        return this.side1;
    }
    double getSide2(){
        return this.side2;
    }
    double getSide3(){
        return this.side3;
    }

    public double getArea(){
        double s = getPerimeter()/2.0;
        double area = Math.sqrt(s*(s-getSide1())*(s-getSide2())*(s-getSide3()));
        return area;
    }
    public double getPerimeter(){
        return this.side1 + this.side2 + this.side3;
    }
    void rotate(double Theta) {
        super.theta = super.theta + Theta;
    }
    
    public String toString(){
        double gamma=Math.acos((Math.pow(this.side3,2)+(this.side1*this.side1)-(this.side2*this.side2))/(2*this.side3*this.side1));
        String lalala;
        double x=super.x;
        double y=super.y;
        double theta=super.theta;
        lalala="("+String.format("%.2f",x)+","+String.format("%.2f",y)+"),";
        lalala+="("+String.format("%.2f",x+this.side1*Math.cos(theta))+","+String.format("%.2f",y+this.side1*Math.sin(theta))+"),";
        lalala+="("+String.format("%.2f",x + this.side3*Math.cos(gamma+theta))+","+String.format("%.2f",y+ this.side3*Math.sin(gamma+theta))+")";
        return lalala;
    }
    public String getPara(){
        return side1 + "," + side2 + "," + side3;
    }

}
