
public abstract class GeometricObject {
  public String color = "white";
  double x;
  double y;
  double theta;
  public boolean filled;
  public java.util.Date dateCreated;

  /**Default construct*/
  public GeometricObject() {
    dateCreated = new java.util.Date();
  }

  /**Construct a geometric object*/
  public GeometricObject(String color, boolean filled) {
    dateCreated = new java.util.Date();    
    this.color = color;
    this.filled = filled;
  }

  /**Getter method for color*/
  public String getColor() {
    return color;
  }

  /**Setter method for color*/
  public void setColor(String color) {
    this.color = color;
  }
  void rotate(double Theta){
    this.theta = this.theta + Theta;
  }
  /**Getter method for filled. Since filled is boolean,
     so, the get method name is isFilled*/
  public boolean isFilled() {
    return filled;
  }

  double getX(){
    return this.x;
  }
  double getY(){
    return this.y;
  }
  double getTheta(){
    return this.theta;
  }
  void setTheta(double Theta){
    this.theta = Theta;
  }

  /**Setter method for filled*/
  public void setFilled(boolean filled) {
    this.filled = filled;
  }

  /**Abstract method findArea*/
  public abstract double getArea();

  /**Abstract method getPerimeter*/
  public abstract double getPerimeter();

  public java.util.Date getDateCreated() {
    return dateCreated;
  }

  public String toString() {
    return "created on " + dateCreated + "\ncolor: " + color + " and filled: " + filled;
  }
  public abstract String getPara();
}
