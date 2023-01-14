# File Compression using Huffman Coding in C++ language

## Introduction
The project is to design compression and decompression programs using Huffman Coding. The idea is to assign variable length codes to input characters based on their frequencies. The more the frequency of the character the shorter the code assigned to it. To reduce the weighted expected storage by means of assigning shorter codes to frequently occurring characters.  


### Compression:
➡ Provide the input.  
➡ Note the frequency of all the characters in the input.  
➡ Construct a min priority queue with respect to the frequencies of the characters.  
➡ Construct Huffman Tree from the priority queue.  
➡ Encode the file, store the encoding table and compress the input based on the encoding table.  

***The codes are stored as bits and each character is provided a prefix code which is a string of bits.***

![EncodeHuffman](https://user-images.githubusercontent.com/76005388/212450745-69366ee0-3730-4654-8d28-ce13b7742aef.png)



### Decompression:
➡ Open the file and reconstruct the Huffman Tree based on the encoded table.  
➡ Decode the file and store it into the desired file.  

![DecodeString](https://user-images.githubusercontent.com/76005388/212450829-375ad8de-7eec-4b1f-8b5d-a8670adc5acd.png)


### Finding Compression Rate:
➡ A compression varying from 6-7% of the initial input is achieved.

![Compression rate](https://user-images.githubusercontent.com/76005388/212451257-5aacb025-0626-4f78-b787-da15804af8f2.png)


### Output:
➡  An output consisting of Original string, Encoded string, Decoded string and Compression rate has been generated.

![Output](https://user-images.githubusercontent.com/76005388/212452489-fd938a8e-74a8-4dbe-b889-3feebe9f116b.png)
