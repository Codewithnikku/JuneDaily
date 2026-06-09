class PAAGP {
    public int[] pivotArray(int[] nums, int pivot) {
        int n = nums.length;
        int less = 0, equal = 0;

        for (int x : nums) {
            if (x < pivot) {
                less++;
            } else if (x == pivot) {
                equal++;
            }
        }

        int[] ans = new int[n];

        int i = 0;             
        int j = less;          
        int k = less + equal;  

        for (int x : nums) {
            if (x < pivot) {
                ans[i++] = x;
            } else if (x == pivot) {
                ans[j++] = x;
            } else {
                ans[k++] = x;
            }
        }

        return ans;
    }
}

public class PartitionArrayAccordingToGivenPivot {
    public static void main(String[] args) {
        
    }
}