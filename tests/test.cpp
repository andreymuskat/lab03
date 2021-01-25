// Copyright 2021 Slava-100 <svat.strel.2001@gmail.com>

#include <gtest/gtest.h>

#include <shared_ptr.hpp>
#include <utility>

TEST(DefaultFeatures, DefaultConstructor) {
  shared_ptr<int> ptr;
  auto count = ptr.use_count();
  EXPECT_EQ(count, 0);
  EXPECT_FALSE(ptr);
}

TEST(DefaultFeatures, CopyingConstructor) {
  shared_ptr<int> ptr1(new int(123));
  shared_ptr<int> ptr2(ptr1);
  EXPECT_EQ(ptr1.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr1.use_count(), 2);
  EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(DefaultFeatures, MovingConstructor) {
  EXPECT_TRUE(std::is_move_constructible_v<shared_ptr<int>>);

  shared_ptr<int> ptr1(new int(123));
  auto ptr1_obj = ptr1.get();
  auto ptr1_use_count = ptr1.use_count();

  shared_ptr<int> ptr2(std::move(ptr1));
  EXPECT_FALSE(ptr1);
  EXPECT_EQ(ptr1.use_count(), 0);

  EXPECT_EQ(ptr2.get(), ptr1_obj);
  EXPECT_EQ(ptr2.use_count(), ptr1_use_count);
}

TEST(DefaultFeatures, CopyingAssignable) {
  shared_ptr<int> ptr1(new int(123));
  auto ptr2 = ptr1;
  EXPECT_EQ(ptr1.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr1.use_count(), 2);
  EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(DefaultFeatures, MovingAssignable) {
  EXPECT_TRUE(std::is_move_assignable_v<shared_ptr<int>>);
  shared_ptr<int> ptr1(new int(123));
  auto ptr1_obj = ptr1.get();
  auto ptr1_use_count = ptr1.use_count();

  auto ptr2 = std::move(ptr1);
  EXPECT_FALSE(ptr1);
  EXPECT_EQ(ptr1.use_count(), 0);

  EXPECT_EQ(ptr2.get(), ptr1_obj);
  EXPECT_EQ(ptr2.use_count(), ptr1_use_count);
}

TEST(DefaultFeatures, Destructor) {
  shared_ptr<int> ptr1(new int(123));
  {
    auto ptr2 = ptr1;
    EXPECT_EQ(ptr2.use_count(), 2);
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr1.get(), ptr2.get());
  }
  EXPECT_EQ(ptr1.use_count(), 1);
}
