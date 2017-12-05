# Welcome to Huffman Encoding

### About

This project was a school assignment that I took way too far.
I took and threaded this assignment, even though it is pretty unnecessary.

The algorithm will compress documents down to about 50% of their normal size.

### Try it out

There is a usable executable right in the [root folder](https://github.com/AidanFairman/HuffmanEncoding) of this repository, as well as a txt version of Leo Tolstoy's "War and Peace" for testing purposes. 

### How does it work

The compression part of the algorithm is a producer-consumer model, where one thread reads the document and finds the encoding for the current byte, and puts it in a queue. The consumer, at the same time, consumes these encodings by doing bit shifting and writing out every byte.

Decompression is not multi-threaded. It builds the encoding table, and then decompresses all on the same thread.

Compression is actually a bit slower than decompression, and this is probably due to the way the threads sleep and wake up. The reason I did the threading was not really for performance gain, but more for the challenge of making it work.
