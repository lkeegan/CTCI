#include "stacks_and_queues.hpp"
using namespace animal_shelter;

void queue::enqueue(const animal& item) {
  oldest_animal = animal_list.insert_after(oldest_animal, item);
}

animal queue::dequeue_any() {
  animal item = animal_list.front();
  animal_list.pop_front();
  return item;
}
animal queue::dequeue(Species species) {
  std::forward_list<animal>::iterator current = animal_list.begin();
  std::forward_list<animal>::iterator prev = animal_list.before_begin();
  while ((*current).species != species) {
    ++current;
    ++prev;
  }
  animal item = (*current);
  animal_list.erase_after(prev);
  return item;
}