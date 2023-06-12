package Java;

public class complex {
    int re;
    int im;
    public complex(int re,int im){
        this.re = re;
        this.im = im;
    }
    public void setre(int newre){
        re = newre;
    }
    public void setim(int newim){
        im = newim;
    }
    public int getre(){return re;}
    
    public int getim(){return im;}

    public String conj(){
        return "共轭复数"+re+"-"+im+"i";
    }
    public static String add(complex x,complex y){
        int a,b;
        a = x.getre() + y.getre();
        b = x.getim() + y.getim();
        return  a + "+" + b + "i";
        
    }
    
    public String toString(){
        return "该复数是"+ re + '+'+ im + 'i';

    }
    public static void main(String[] args) {
        complex x = new complex(1,2);
        complex y = new complex(3,4);
        

        System.out.println(x);
        System.out.println(x.conj());
        System.out.println("x和y相加"+add(x,y));
        y.setre(5);
        System.out.println("修改后的y"+y);
    }
}
