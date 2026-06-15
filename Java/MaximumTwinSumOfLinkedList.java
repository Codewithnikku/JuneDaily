import java.util.*;

// Step 1: Find the mid node - slow/fast pointers
// Step 2: Reverse the second half of list
// Step 3: Compare correspondingtwin elements

class ListNode {
    public int pairSum(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        ListNode secondHalf = reverse(slow);
        int maxSum = 0;
        ListNode firstHalf = head;

        while (secondHalf != null) {
            maxSum = Math.max(maxSum, firstHalf.val + secondHalf.val);
            firstHalf = firstHalf.next;
            secondHalf = secondHalf.next;
        }

        return maxSum;
    }

    private ListNode reverse(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
}
public class MaximumTwinSumOfLinkedList {
    public static void main(String[] args) {
        
    }
}

