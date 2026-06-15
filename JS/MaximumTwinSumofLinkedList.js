var pairSum = function(head) {
    let slow = head;
    let fast = head;

    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
    }

    let prev = null;
    let curr = slow;

    while (curr) {
        let next = curr.next;
        curr.next = prev;
        prev = curr;
        curr = next;
    }

    let ans = 0;
    let first = head;
    let second = prev;

    while (second) {
        ans = Math.max(ans, first.val + second.val);
        first = first.next;
        second = second.next;
    }

    return ans;
};