// implementation of linked list

class ListNode(value: Int = 0, nextNode: ListNode? = null){
    var data: Int
    var next: ListNode?

    init{
        data = value
        next = nextNode
    }

    fun printListNode(){
        print(data)
    }
}

class LinkedList{
    var head: ListNode?
    init{
        head = null
    }

    fun insertFront(number: Int){
        head = ListNode(number, head)
    }

    fun insertBack(number: Int){
        if(head == null){
            head = ListNode(number)
            return
        }else{
            var currentListNode: ListNode? = head
            while(currentListNode?.next != null){
                currentListNode = currentListNode?.next
            }
            currentListNode?.next = ListNode(number)
        }
    }

    fun printLinkedList(){
        var currentListNode: ListNode? = head
        print("head -> ")
        while(currentListNode != null){
            currentListNode?.printListNode()
            print(" -> ")
            currentListNode = currentListNode?.next
        }
        print("null\n")
    }
}

fun main() {
    var myLinkedList: LinkedList = LinkedList()
    myLinkedList.insertFront(1)
    myLinkedList.insertFront(2)
    myLinkedList.insertFront(3)
    myLinkedList.insertFront(4)
    myLinkedList.insertFront(5)

    myLinkedList.insertBack(6)
    myLinkedList.insertBack(7)
    myLinkedList.insertBack(8)
    myLinkedList.insertBack(9)
    myLinkedList.insertBack(10)

    myLinkedList.printLinkedList()
}
