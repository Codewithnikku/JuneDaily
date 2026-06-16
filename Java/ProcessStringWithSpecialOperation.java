class ProcessStringWithSpecialOperation {
    public String processStr(String s) {
        StringBuilder result = new StringBuilder();

        for (char ch : s.toCharArray()) {
            if (Character.isLowerCase(ch)) {
                result.append(ch);
            }
            else if (ch == '*') {
                if (result.length() > 0) {
                    result.deleteCharAt(result.length() - 1);
                }
            }
            else if (ch == '#') {
                result.append(result.toString());
            }
            else if (ch == '%') {
                result.reverse();
            }
        }

        return result.toString();
    }

    public static void main(String[] args) {
        ProcessStringWithSpecialOperation sol = new ProcessStringWithSpecialOperation();

        String s = "a#b%*";

        System.out.println("Input: " + s);
        System.out.println("Output: " + sol.processStr(s));
    }
}