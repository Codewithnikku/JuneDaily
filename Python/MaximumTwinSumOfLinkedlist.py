class Solution(object):
    def pairSum(self, head):
        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        second_half = self.reverse(slow)

        ans = 0
        first_half = head

        while second_half:
            ans = max(ans, first_half.val + second_half.val)
            first_half = first_half.next
            second_half = second_half.next

        return ans

    def reverse(self, head):
        prev = None
        curr = head

        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt

        return prev