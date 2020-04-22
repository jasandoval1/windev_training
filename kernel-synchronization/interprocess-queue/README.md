## Exercise: Threadsafe Inter-Process Queue

In this exercise you are asked to combine what you learned in this module with the practical experience you gained in the previous module to design and implement a queue data structure that supports safe, concurrent access from multiple process contexts.

### Procedure

Design and implement a queue data structure with a fixed maximum capacity. The queue must support safe, concurrent access from multiple process contexts. The methods that your queue must support and their associated semantics are enumerated below. Note, however, that the precise signature of these functions is deliberately omitted.

- `queue_initialize()`: Creates / initializes a new queue data structure. This method need not support safe concurrent invocation. 
- `queue_destroy()`: Releases any dynamically-allocated or operating system resources associated with a queue data structure. This method need not support safe concurrent invocation.
- `queue_push_back()`: Writes a new data element to the queue. This method must support safe concurrent invocation from multiple process contexts. When this method is invoked on a queue that is full (the number of elements in the queue is equal to the capacity that was specified at the time of its creation) it blocks indefinitely until it successfully writes the provided data to the queue.
- `queue_pop_front()`: Reads a data element from the queue and removes it. This method must support safe concurrent invocation from multiple process contexts. When this method is invoked on a queue that is empty (the number of elements in the queue is 0) it blocks indefinitely until it successfully reads one element of data from the queue.

I'll refrain from restating the guidance provided in the queue exercise from the previous module regarding the flexibility of both the API and your implementation - all of that guidance applies here as well.

Well... almost all of it. What does it mean for a data structure to be accessible from multiple process contexts? Fundamentally, one should be able to write data to the queue in one process context and subsequently read this data from the queue in a distinct process context. The necessity for inter-process communication of this kind severely limits the options available to you regarding the underlying storage for your data structure. Two approaches to this problem are the following:

- Implement your queue in a dynamic library and back its underlying storage with a shared memory segment
- Use a file mapping backed by the system page file

That should be sufficient guidance to get you started on implementing inter-process shared storage. But what about the necessity for safe concurrent access? Again, there are multiple ways to approach this problem, including:

- Using Windows semaphores 
- Using Windows mutexes combined with Windows events to implement the "condition variable model"

One thing that this exercise should make viscerally apparent is both the power and limitations of Windows synchronization primitives. For instance, this exercise would be a perfect opportunity to employ a condition variable, much as you (hopefully) did in the previous exercise, but alas, the condition variables exposed by Win32 (`CONDITION_VARIABLE`s) are synchronization _structures_ rather than proper synchronization _objects_ (more precisely, they are not backed by a kernel _dispatcher object_) and therefore they cannot be used to synchronize operations across process boundaries. 

A sample implementation that meets these requirements is provided in the `reference/` directory; don't refer to the provided sample until you have attempted the exercise yourself!