#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  // 0-based indix
  int left_ch(int idx){return 2*idx+1;}
  int right_ch(int idx) {return 2*idx+2;}

  void SiftDown(int idx){
    int heap_size = data_.size();
    int minidx = idx;
    int left = left_ch(idx);
    int right = right_ch(idx);
    if(left < heap_size && data_[left]<data_[minidx]) minidx=left;

    if(right < heap_size && data_[right]<data_[minidx]) minidx=right;
    //Base case for the recurence 
    if(idx != minidx){
        swap(data_[idx], data_[minidx]);
        swaps_.push_back(make_pair(idx,minidx));
        SiftDown(minidx);
    }
 }
  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for(int i =(data_.size()-1)/2; i>=0; i--) SiftDown(i);
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
