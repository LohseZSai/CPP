package Java;

abstract public class Shape {
    private double centerX;
    private double centerY;
    public Shape(double centerX,double centerY){
        this.centerX = centerX;
        this.centerY = centerY;
    }
    public abstract double area();
    interface Iprint{
        void display();
    }
}
 class circle2 extends Shape{
    double R;
    public circle2(double centerX, double centerY,double R) {
        super(centerX, centerY);
        this.R = R;

    
}
public void display(){
        System.out.println("这个圆的半径为"+R+"面积为"+area());
    }

    @Override
    public double area() {
        double S;
        S = 3.14*R*R;
        return S;
    }
}
class Rectangle extends Shape{
    double width,length;
    public Rectangle(double centerX,double centerY,double length,double width){
        super(centerX,centerY);
        this.width = width;
        this.length = length;
    }
    @Override
    public double area() {
        double s;
        s = length * width;
        return s;
    }
    public void display(){

    }
}
