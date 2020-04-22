## Exercise: Threadsafe Intra-Process Queue

In this exercise you are asked to put what you have learned in this module to work by designing and implementing a queue data structure that supports safe, concurrent access from an arbitrary number of threads in a single process context.

### Procedure

Design and implement a queue data structure with a fixed maximum capacity. The queue must support safe, concurrent access from multiple threads. The methods that your queue must support and their associated semantics are enumerated below. Note, however, that the precise signature of these functions is deliberately omitted.

- `queue_initialize()`: Creates / initializes a new queue data structure. This method need not support safe concurrent invocation. 
- `queue_destroy()`: Releases any dynamically-allocated or operating system resources associated with a queue data structure. This method need not support safe concurrent invocation.
- `queue_push_back()`: Writes a new data element to the queue. This method must support safe concurrent invocation. When this method is invoked on a queue that is full (the number of elements in the queue is equal to the capacity that was specified at the time of its creation) it blocks indefinitely until it successfully writes the provided data to the queue.
- `queue_pop_front()`: Reads a data element from the queue and removes it. This method must support safe concurrent invocation. When this method is invoked on a queue that is empty (the number of elements in the queue is 0) it blocks indefinitely until it successfully reads one element of data from the queue.

The above specification of the queue's methods places some limits on the API that your queue must support, but many choices are deliberately left to your discretion. For instance, the actual data type stored by your queue as well as its associated ownership model is completely unspecified - you may choose to require that consumers of your queue provide generic pointers (`void*`) to arbitrary, dynamically-allocate data or you may choose to implement some internal copying by which your queue takes ownership of the data elements that are written to it. Furthermore, you may choose to implement the underlying data structure for your queue with a linked-list, or you may choose to do so with a fixed-size circular buffer. The choice is yours!

While you should feel free to explore the wide world of Windows synchronization primitives while determining how to make your queue safe for concurrent access, the user-mode-specific synchronization primitives that are the focus of this module should be at the top of your list. Specifically, if you have not done so already, this exercise presents a great opportunity to study the API provided by:

- Critical Sections (`CRITICAL_SECTION`)
- Slim Reader / Writer Locks (`SRWLOCK`)
- Condition Variables (`CONDITION_VARIABLE`)

Note that the reading material for this module in _Windows System Programming, Fourth Edition_ contains an example queue implementation that meets these requirements. This material is a fantastic reference and studying it will strengthen your understanding of effective concurrent programming, but for the purpose of this exercise, try to complete your implementation without referring directly to the example. The author discusses all of the strategies that he exercises in the queue implementation at earlier points in the chapter, so referring to the material in the chapter in question that leads up to the example should provide more than enough inspiration to see your own implementation through to the end.   

As usual, a sample implementation that meets these requirements is provided in the `reference/` directory; don't refer to the provided sample until you have attempted the exercise yourself!