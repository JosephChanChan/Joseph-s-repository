package tables;

/**
 * 剑指Offer 22 easy
 *
 * Question Description:
 *  输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
 *  例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
 * 示例：
 * 给定一个链表: 1->2->3->4->5, 和 k = 2.
 * 返回链表 4->5.
 *
 * Analysis:
 *  快慢指针。先让快指针走k步，之后双指针一起走，直到快指针到达链表结尾。
 *  时间复杂度：O(n)
 *  空间复杂度：O(1)
 *
 * @author Joseph
 * @since 2020-03-28 16:25
 */
public class KthNodeFromEnd {

    public ListNode getKthFromEnd(ListNode head, int k) {
        if (null == head || null == head.next)
            return head;

        ListNode slow = head, fast = head;

        int temp = k;
        while (temp-- > 0) {
            fast = fast.next;
        }
        while (null != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow;
    }

    public class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

}
