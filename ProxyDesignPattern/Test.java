public class Test {
    public static void main(String[] args) {
        Internet i = new ProxyInternet();
        i.showData("www.github.com");
        i.showData("www.notgithub.com.com");
    }
}