/**
 * DO NOT EDIT THIS FILE 
 * author: Ronny Hartanto (2021)
 */

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import org.junit.jupiter.api.Test;

import java.io.*;
import java.util.GregorianCalendar;

public class TestExercise09b {

  @Test
  public void test01()
  {
    PrintStream originalOut = System.out;
    ByteArrayOutputStream bos = new ByteArrayOutputStream();
    System.setOut(new PrintStream(bos));
    Triangle tri1 = new Triangle(5, 5, 5);
    Triangle tri2 = new Triangle(3, 5, 4);
    GeometricObject geo = tri2;
    geo.rotate(Math.PI/2);
    assertEquals("white", tri2.getColor());
    tri2.setColor("blue");
    assertEquals(3.0, tri2.getSide1());
    assertEquals(4, tri2.getSide3());
    assertEquals(5, tri1.getSide2());
    assertEquals(15.0, tri1.getPerimeter(), 0.0001);
    assertEquals(12.0, geo.getPerimeter(), 0.0001);
    assertEquals(10.825317547305483, tri1.getArea(), 0.00000001);
    assertEquals(6.0, geo.getArea(), 0.00000001);
    assertEquals(geo.toString(), "(0.00,0.00),(0.00,3.00),(-4.00,0.00)");
    assertEquals("blue", geo.getColor());
     RegularPolygon pol1 = new RegularPolygon(6, 4);
     RegularPolygon pol2 = new RegularPolygon(10, 4, 5.6, 7.8);
     GeometricObject obj2 = new Rectangle();
     pol1.rotate(Math.PI/3);
     GeometricObject obj3 = new Circle();      
     geo = pol2;
     BucketOfObjects bucket = new BucketOfObjects();
     bucket.addObject((GeometricObject) tri1);
     bucket.addObject((GeometricObject) pol1);
     bucket.addObject(obj2);
     bucket.addObject(geo);
     assertEquals(176.5018784159687, bucket.getTotalArea(), 0.0000001);
     assertEquals(83.0, bucket.getTotalPerimeter(), 0.0000000001);
     assertTrue(bucket.toString().contains("RegularPolygon:(5.60,7.80),(9.60,7.80),(12.84,10.15),(14.07,13.96),(12.84,17.76)"));
     for (int i=1; i<20; i++) {
       bucket.addObject(new Circle());
       bucket.addObject(new Triangle());
     }      
     bucket.addObject(new Circle());      
     bucket.addObject((GeometricObject) tri2);
     pol2.rotate(Math.PI/2);
     bucket.addObject((GeometricObject) pol2);
     assertEquals("white", pol2.getColor());
     geo.setColor("red");
     assertEquals(0.0, pol1.getX());
     assertEquals(7.8, pol2.getY());
     assertEquals(6, pol1.getN());
     assertEquals(4, pol2.getSide());
     assertEquals(24.0, pol1.getPerimeter(), 0.0001);
     assertEquals(40.0, pol2.getPerimeter(), 0.0001);
     assertEquals(41.569219381653056, pol1.getArea(), 0.00000001);
     assertEquals(123.10734148701015, geo.getArea(), 0.00000001);
     assertEquals(376.6683143107265, bucket.getTotalArea(), 0.0000001);
     assertTrue(bucket.toString().contains("(5.60,7.80),(5.60,11.80),(3.25,15.04),(-0.56,16.27),(-4.36,15.04)"));
     assertEquals(317.6637061435918, bucket.getTotalPerimeter(), 0.0000000001);
     assertTrue(bucket.toString().contains("43:Circle:(0.00,0.00),r:1.00"));
     assertEquals(pol2.toString(), "(5.60,7.80),(5.60,11.80),(3.25,15.04),(-0.56,16.27),(-4.36,15.04),(-6.71,11.80),(-6.71,7.80),(-4.36,4.56),(-0.56,3.33),(3.25,4.56)");
     assertEquals("red", pol2.getColor());
     System.setOut(originalOut);
  }
   @Test
   public void test02()
   {
     PrintStream originalOut = System.out;
     ByteArrayOutputStream bos = new ByteArrayOutputStream();
     System.setOut(new PrintStream(bos));
     Triangle tri1 = new Triangle(5, 5, 5);
     Triangle tri2 = new Triangle(3, 5, 4);
     GeometricObject geo = tri2;
     assertEquals("white", tri2.getColor());
     tri2.setColor("blue");
     assertEquals(3.0, tri2.getSide1());
     assertEquals(4, tri2.getSide3());
     assertEquals(5, tri1.getSide2());
     assertEquals(15.0, tri1.getPerimeter(), 0.0001);
     assertEquals(12.0, geo.getPerimeter(), 0.0001);
     assertEquals(10.825317547305483, tri1.getArea(), 0.00000001);
     assertEquals(6.0, geo.getArea(), 0.00000001);
     assertEquals(geo.toString(), "(0.00,0.00),(3.00,0.00),(0.00,4.00)");
     assertEquals("blue", geo.getColor());
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
      assertEquals(176.5018784159687, bucket.getTotalArea(), 0.0000001);
      assertEquals(83.0, bucket.getTotalPerimeter(), 0.0000000001);
      assertTrue(bucket.toString().contains("RegularPolygon:(5.60,7.80),(9.60,7.80),(12.84,10.15),(14.07,13.96),(12.84,17.76)"));
      for (int i=1; i<20; i++) {
        bucket.addObject(new Circle());
        bucket.addObject(new Triangle());
      }      
      bucket.addObject(new Circle());      
      bucket.addObject((GeometricObject) tri2);
      bucket.addObject((GeometricObject) pol2);
      assertEquals("white", pol2.getColor());
      geo.setColor("red");
      assertEquals(0.0, pol1.getX());
      assertEquals(7.8, pol2.getY());
      assertEquals(6, pol1.getN());
      assertEquals(4, pol2.getSide());
      assertEquals(24.0, pol1.getPerimeter(), 0.0001);
      assertEquals(40.0, pol2.getPerimeter(), 0.0001);
      assertEquals(41.569219381653056, pol1.getArea(), 0.00000001);
      assertEquals(123.10734148701015, geo.getArea(), 0.00000001);
      assertEquals(376.6683143107265, bucket.getTotalArea(), 0.0000001);
      assertTrue(bucket.toString().contains("Triangle:(0.00,0.00),(1.00,0.00),(0.50,0.87)"));
      assertEquals(317.6637061435918, bucket.getTotalPerimeter(), 0.0000000001);
      bucket.removeObject((GeometricObject) tri2);
      bucket.removeObject(pol2);
      assertEquals(265.66370614359187, bucket.getTotalPerimeter(), 0.00000001);
      assertEquals(247.56097282371684, bucket.getTotalArea(), 0.0000001);
      assertTrue(bucket.toString().contains("RegularPolygon:(5.60,7.80),(9.60,7.80),(12.84,10.15),(14.07,13.96),(12.84,17.76)"));
      assertTrue(pol2.toString().contains("(5.60,7.80),(9.60,7.80),(12.84,10.15),(14.07,13.96),(12.84,17.76),(9.60,20.11),(5.60,20.11),(2.36,17.76)"));
      assertEquals("red", pol2.getColor());
      bucket.save("mybucket.txt");
      BucketOfObjects bucket2 = new BucketOfObjects();
      bucket2.load("mybucket.txt");
      assertEquals(265.66370614359187, bucket2.getTotalPerimeter(), 0.00000001);
      assertEquals(247.56097282371684, bucket2.getTotalArea(), 0.0000001);
      assertTrue(bucket2.toString().contains("Circle:(0.00,0.00),r:1.00"));
      bucket.load("mybucket.txt");
      assertEquals(531.3274122871832, bucket.getTotalPerimeter(), 0.00000001);
      assertEquals(495.12194564743317, bucket.getTotalArea(), 0.0000001);
      System.setOut(originalOut);
   }   
}