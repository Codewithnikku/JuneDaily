class MaximumElementAfterDescendingAndRearranging {
    public int maximumElementAfterDecrementingAndRearranging(int[] arr) {
        int n = arr.length; int ans = 1;
        int count[] = new int[n+1];
        for(int a : arr) { int idx=Math.min(a, n); count[idx]++; }
        for(int i=2; i<=n; i++) { int curr=ans+count[i]; ans=Math.min(i, curr); }
        return ans;
    }
}