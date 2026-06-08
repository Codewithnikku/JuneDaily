class TWNIR_I {
    public int totalWaviness(int num1, int num2) {
        int total = 0;
        for (int n = num1; n <= num2; n++) {
            String s = Integer.toString(n);
            int len = s.length();
            for (int i = 1; i < len - 1; i++) {
                if ((s.charAt(i) > s.charAt(i-1) && s.charAt(i) > s.charAt(i+1)) ||
                    (s.charAt(i) < s.charAt(i-1) && s.charAt(i) < s.charAt(i+1)))
                    total++;
            }
        }
        return total;
    }
}

public class TotalWavinessofNumbersInRange_I {
    public static void main(String[] args) {
        TWNIR_I twnir = new TWNIR_I();
        int num1 = 120, num2 = 130;
        int result = twnir.totalWaviness(num1, num2);
        System.out.println("Total Waviness: " + result);
    }
}
