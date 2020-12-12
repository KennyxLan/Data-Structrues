    fun hasCycle(head: ListNode?): Boolean {
        var slow: ListNode? = head
        var fast: ListNode? = head?.next
        while(fast != null){
            if(fast == slow)
                return true
            slow = slow?.next
            fast = fast?.next?.next
        }
        return false
    }
