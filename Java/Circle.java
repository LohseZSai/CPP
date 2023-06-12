package Java;

public class Circle {
    private int r;
    public Circle(int r){
        this.r = r;
    }
    public void setR(int newR){
        this.r = newR;
    }
    public int getR(){return r;}
    public double  area(){
        double S;
        S = r*r*3.14;
        return S;
    }
}







