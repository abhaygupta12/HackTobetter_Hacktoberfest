import java.util.*;

class City implements Comparable<City>{
   private String city;
    private int men,women;
    public City(String city, int man, int woman){
        this.city=city;
        this.men=man;
        this.women=woman;
    }
    public int compareTo(City other){
        if((other.men+other.women)==(this.men+this.women)){
            if(other.men==this.men){
                return this.city.compareTo(other.city);
            }
            return other.men-this.men;
        }
        return (other.men+other.women) - (this.men+this.women);
    }
    public String toString(){
        return this.city+" "+this.men+" "+this.women;
    }
}
public class sort_cities_by_population {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = Integer.parseInt(sc.nextLine().trim());
        List<City> cities = new ArrayList<>();
        for (int ctr = 1; ctr <= N; ctr++) {
            String currCity[] = sc.nextLine().trim().split("\\s+");
            cities.add(new City(currCity[0],
                    Integer.parseInt(currCity[1]),
                    Integer.parseInt(currCity[2])));
        }
        Collections.sort(cities);
        for (City city : cities) {
            System.out.println(city);
        }
    }
}
