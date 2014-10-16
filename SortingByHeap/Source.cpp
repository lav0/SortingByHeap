#include <iostream>
#include <string>

using namespace std;


long RangedRand( long range_min, long range_max )
{
   // Generate random numbers in the half-closed interval
   // [range_min, range_max). In other words,
   // range_min <= random number < range_max
   
  return long ((double)rand() / (RAND_MAX + 1) * (range_max - range_min)
          + range_min);
}

class BinaryHeap 
{
public:

  BinaryHeap(long a_size) : m_size(a_size), m_b_defined(false) {
    m_p_array = new long[a_size];
    m_p_last  = m_p_array;
  }

  ~BinaryHeap() {
    if (m_p_array != nullptr) {
      delete[] m_p_array;
    }
  }

  void push_back(long a_value) {
    if (m_b_defined) {
      increase_array_size();
    }

    *m_p_last = a_value;
    if (m_p_array + m_size-1 != m_p_last) {
      ++m_p_last;
    } else {
      m_b_defined = true;
    }
  }

  long at(long a_ind) const {
    if (a_ind > m_size-1 || a_ind < 0) {
      return 0;
    }
    return m_p_array[a_ind];
  }

  // the biggest element is on the root
  bool down(long& a_ind) {
    long left_child_ind  = get_child(a_ind, 0) - 1;
    long right_child_ind = get_child(a_ind, 1) - 1;

    long ind_of_aim = at(left_child_ind) > at(right_child_ind) ? 
      left_child_ind : right_child_ind;
    
    if (at(a_ind - 1) < at(ind_of_aim)) {
      swap(&m_p_array[ind_of_aim], &m_p_array[a_ind - 1]);
      a_ind = ind_of_aim + 1;
      return true;
    }
    return false;
  }

  void sift_down(long a_ind) {
    while (down(a_ind)) {}
  }
  
  long* get_first() { return m_p_array; }
  long* get_last () { return m_p_last ; }
  
  long get_size() { return m_size; }
  bool is_defined() { return m_b_defined; }
  
protected:

  void swap(long* a_p1, long* a_p2) {
    long tmp = *a_p1;
    *a_p1 = *a_p2;
    *a_p2 = tmp;
  }

  void decrease() {
    --m_size;
  }
  
private:

  void increase_array_size() {
    long* p_tmp = m_p_array;
    m_p_array = new long[2*m_size];

    long i=0;
    for (; i<m_size; i++) {
      m_p_array[i] = p_tmp[i];
    }

    m_p_last = &m_p_array[i];
    delete[] p_tmp;

    m_b_defined = false;
  }

  long get_parent_index(long a_ind) const {
    if (a_ind == 1) {
      return -1;
    }
    return a_ind / 2;
  }

  long get_child(long a_ind, int a_num) const {
    long res = 2 * a_ind + a_num;
    return res > m_size ? -1 : res;
  }

protected:

  long* m_p_array;
  long* m_p_last;

private:
  
  bool m_b_defined;
  long m_size;
};

class SortingByHeap : public BinaryHeap 
{
public:
  SortingByHeap(long a_size) : BinaryHeap(a_size) {}
  
  bool sort() {
    if (!is_defined()) {
      return false;
    }

    sort_heap();
    
    long last_ind = get_size()-1;
    while (m_p_last != m_p_array) {
      swap(m_p_last--, m_p_array);
      decrease();
      sift_down(1);
    }

    m_p_last = m_p_array + last_ind;
    return true;
  }

  void display() {
    cout << "\n";
    long* p = m_p_array;
    do {
      cout << *p << " ";
    } while (p++ != m_p_last);
  }

private:

  void sort_heap() {
    long l_middle = get_size() / 2;
    for (long i = l_middle; i > 0; i--) {
      sift_down(i);
    }
  }

};



bool test() {
  long size = RangedRand(1l, 100000l); 
  
  SortingByHeap heap(size);

  for (long i=0; i<size; i++) {
    heap.push_back(RangedRand(1l, 1000000000l));
  }
    
  heap.sort();

  long* itr = heap.get_first();
  long prev = 0;
  while (itr != heap.get_last()) {
    if (prev > *itr) {
      return false;
    }
    prev = *itr++;
  }
  return true;
}

int main() {
  long n; 
  cin >> n;
  
  SortingByHeap heap(n);

  for (long i=0; i<n; i++) {
    long value;
    cin >> value;
    heap.push_back(value);
  }
  
  heap.sort();
  heap.display();

  return 0;
}
