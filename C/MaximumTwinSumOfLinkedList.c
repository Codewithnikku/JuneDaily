struct ListNode* reverse(struct ListNode* head) {
    struct ListNode* prev = NULL;
    
    while (head) {
        struct ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    
    return prev;
}

int pairSum(struct ListNode* head) {
    struct ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct ListNode* second = reverse(slow);
    int ans = 0;

    while (second) {
        int sum = head->val + second->val;
        if (sum > ans) ans = sum;

        head = head->next;
        second = second->next;
    }

    return ans;
}