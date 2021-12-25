import java.util.ArrayList;
import java.io.*;

public class BucketOfObjects {
    public static void main(String[] args) {
     Triangle tri1 = new Triangle(5, 5, 5);
     Triangle tri2 = new Triangle(3, 5, 4);
     GeometricObject geo = tri2;
     tri2.setColor("blue");
     System.out.println(geo.toString());
      RegularPolygon pol1 = new RegularPolygon(6, 4);
      RegularPolygon pol2 = new RegularPolygon(10, 4, 5.6, 7.8);
      GeometricObject obj2 = new Rectangle();
      GeometricObject obj3 = new Circle();      
      geo = pol2;
      BucketOfObjects bucket = new BucketOfObjects();
      bucket.addObject((GeometricObject) tri1);
      bucket.addObject((GeometricObject) pol1);
      bucket.addObject(obj2);
      bucket.addObject(geo);
      System.out.println(bucket.toString().contains("RegularPolygon:(5,60,7,80),(9,60,7,80),(12,84,10,15),(14,07,13,96),(12,84,17,76)"));
      for (int i=1; i<20; i++) {
        bucket.addObject(new Circle());
        bucket.addObject(new Triangle());
      }      
      bucket.addObject(new Circle());      
      bucket.addObject((GeometricObject) tri2);
      bucket.addObject((GeometricObject) pol2);
      System.out.println(pol2.getColor());
      geo.setColor("red");
      bucket.removeObject((GeometricObject) tri2);
      bucket.removeObject(pol2);
      bucket.save("mybucket.txt");
      BucketOfObjects bucket2 = new BucketOfObjects();
      bucket2.load("mybucket.txt");
      System.out.println(bucket2.toString().contains("Circle:(0,00,0,00),r:1,00"));
      bucket.load("mybucket.txt");

    }
    public ArrayList<GeometricObject> items = new ArrayList<GeometricObject>();

    public BucketOfObjects(){

    }
    public void addObject(GeometricObject geobj){
            items.add(geobj);
    }
    public double getTotalArea(){
        double totalArea = 0.0;
        for (int i = 0; i < items.size();i++){
            totalArea += items.get(i).getArea();
        }
        return totalArea;
    }
    public double getTotalPerimeter(){
        double perimeter = 0.0;
        for ( int i = 0; i < items.size(); i++){
            perimeter = perimeter + items.get(i).getPerimeter();
        }
        return perimeter;
    }
    public String toString(){
        String str = "";
        for ( int i = 0; i < items.size(); i++){
        str = str + (i+1) + ":" + items.get(i).getClass().getSimpleName() + ":" + items.get(i).toString();
        str = str + "\n";
        }
        return str;
    }
    public void removeObject(GeometricObject iTems){
        items.remove(iTems);
    }

    public boolean load(String filename){
        BufferedReader rd;
        try{
            rd = new BufferedReader(new FileReader(filename));
            String line;
            String lines[];
            while ((line = rd.readLine()) != null) {
                lines = line.split(",");
                switch(lines[0]){
                    case "Circle":
                        addObject(new Circle(Double.parseDouble(lines[1])));
                        break;
                    case "Rectangle":
                        addObject(new Rectangle(Double.parseDouble(lines[1]), Double.parseDouble(lines[2])));
                        break;
                    case "RegularPolygon":
                        addObject(new RegularPolygon(Integer.parseInt(lines[1]), Double.parseDouble(lines[2]),Double.parseDouble(lines[3]),Double.parseDouble(lines[4])));
                        break;
                    case "Triangle":
                        addObject(new Triangle(Double.parseDouble(lines[1]), Double.parseDouble(lines[2]),Double.parseDouble(lines[3])));
                        break;
                }
            }
            rd.close();
            return true;
        }catch (IOException ex){
            System.out.println("Error loading from" + filename);
            return false;
        }
    }

    public boolean save(String filename){
        FileWriter fw;
        try {
            fw = new FileWriter(filename);
            //write
            for (int i = 0; i < items.size();i++){
                GeometricObject geo = items.get(i);
                String line = geo.getClass().getSimpleName() + "," + geo.getPara();
                fw.write(line);
                fw.write(System.getProperty( "line.separator" ));
            }
            fw.close();
            return true;
        } catch (IOException ex){
            System.out.println("Error saving into" + filename);
            return false;
        }
        
    }

}
