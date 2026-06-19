import java.util.*;

class ABCH {
    public double angleClock(int hour, int minutes) {
        double hourDegree = (hour % 12) * 30 + (0.5) * minutes;
        double minuteDegree = (minutes) * 6;
        double diff = Math.abs(hourDegree - minuteDegree);
        return Math.min(diff, 360 - diff);
    }
}

public class AngleBetweenHandsOfClock {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int hour = sc.nextInt();
        int minutes = sc.nextInt();

        ABCH sol = new ABCH();
        System.out.println(sol.angleClock(hour, minutes));

        sc.close();
    }
}
