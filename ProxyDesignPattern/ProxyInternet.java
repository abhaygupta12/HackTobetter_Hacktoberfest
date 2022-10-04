import java.util.ArrayList;
import java.util.Scanner;

public class ProxyInternet implements Internet {
    Scanner sc = new Scanner(System.in);
    private RealInternet ri = new RealInternet();

    static ArrayList<String> acceptedUrl = new ArrayList<>();

    public void showData(String url) {
        ProxyInternet.acceptedUrl.add("www.github.com");
        if (acceptedUrl.contains(url)) {
            ri.showData(url);
            return;
        } else {
            System.out.println("Access Denied \nThe url you entered is not accepted");
        }
    }
}
