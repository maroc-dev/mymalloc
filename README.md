# mymalloc
A implementation of a malloc and free in c 

## Authors
maf407 - Marco Ferreira

## Metadata

Metadata is a byte (8 bits) and this is the structure:

0000 0000
^
Indicator on if the chunk is free or not
0: free
1: allocated

0000 0000
 ^^^ ^^^^

last 7 bits is the size of the data stored

If the chunk is 1 address from the metadata 

size_of an avaliable chunk would be the difference between the address point of metadata_chunk_2 and metadata_chunk_1