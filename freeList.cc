#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  this->head = inRAM;
  this->head[0] = (long int)nullptr;
  this->head[1] = size - 2;
}

long int*
freeList::reserve_space( int size ) {
  long int* current = head;
  long int* prev = NULL;
  while(current != NULL && current[1] < size) {
    prev = current;
    current = (long int*)current[0];
  }
  if(current == NULL) {
    return (long int*)(-1);
  }
  if(prev == NULL) {
    this->head = (long int*)current[0];
  } else {
    prev[0] = current[0];
  }

  current[0] = (long int)nullptr;
  return current + 2;
}

void
freeList::free_space( long int* location ) {
  long int* prevHead = (long int*)this->head;
  this->head = location - 2;
  this->head[0] = (long int)(prevHead);
}

void
freeList::coalesce_forward() {
  long int* current = head;
  while(current != NULL) {
    long int* adjacent = current + 2 + current[1];
    long int* prev = NULL;
    long int* next = head;

    while(next != NULL && next != adjacent) {
      prev = next;
      next = (long int*)next[0];
    }

    if(next != NULL) {
      if(prev == NULL) {
        head = (long int*)next[0];
      } else {
        prev[0] = next[0];
      }
      current[1] += next[1] + 2;
    } else {
      current = (long int*)current[0];
    }
  }
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[0];
  }
}
