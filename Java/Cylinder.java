package Java;

public class Cylinder extends Circle {
    private int h;

    public Cylinder(int r, int h) {
        super(r);
        this.h = h;
    }

    public void setH(int newH) {
        h = newH;
    }

    public int getH() {
        return h;
    }

    public double volume() {
        double v;
        v = super.area() * h;
        return v;
    }

    public double area() {
        double s;
        s = 3.14 * 2 * getR() * h;
        return s;
    };

   
public static void main(String[] args) {
        Circle a = new Circle(5);
        System.out.println(a.area());
        Cylinder b = new Cylinder(5, 4);
        System.out.println("圆柱体的体积是："+b.volume());
        System.out.println("圆柱体的侧面积是："+ b.area());
        
    }
}