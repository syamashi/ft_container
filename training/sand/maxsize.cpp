#include <memory>
#include <iostream>

template <class T, class Alloc>
class MyVector {
  T* data_;
  std::size_t size_;
  Alloc alloc_;
public:
  MyVector(std::size_t size)
  {
    using traits = std::allocator_traits<Alloc>;

    size_ = size;

    // メモリを確保
    data_ = traits::allocate(alloc_, size);

    // 要素を構築
    for (std::size_t i = 0; i < size_; ++i) {
      traits::construct(alloc_, &data_[i]);
    }
  }

  ~MyVector()
  {
    using traits = std::allocator_traits<Alloc>;

    // 要素を破棄
    for (std::size_t i = 0; i < size_; ++i) {
      traits::destroy(alloc_, &data_[i]);
    }

    // メモリを解放
    traits::deallocate(alloc_, data_, size_);
  }
};

int main()
{
  MyVector<int, std::allocator<int>> v(3);
  std::allocator<int> alloc;
  using traits = std::allocator_traits<decltype(alloc)>;

  std::cout << traits::max_size(alloc) << std::endl;
}}