// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/text/writing_mode_utils.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"

namespace blink {

namespace {

enum { kTop, kRight, kBottom, kLeft };

TEST(WritingModeUtilsTest, PhysicalToLogicalHorizontalLtr) {
  PhysicalToLogical<int> converter(
      {WritingMode::kHorizontalTb, TextDirection::kLtr}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kLeft, converter.InlineStart());
  EXPECT_EQ(kRight, converter.InlineEnd());
  EXPECT_EQ(kTop, converter.BlockStart());
  EXPECT_EQ(kBottom, converter.BlockEnd());
}

TEST(WritingModeUtilsTest, PhysicalToLogicalHorizontalRtl) {
  PhysicalToLogical<int> converter(
      {WritingMode::kHorizontalTb, TextDirection::kRtl}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kRight, converter.InlineStart());
  EXPECT_EQ(kLeft, converter.InlineEnd());
  EXPECT_EQ(kTop, converter.BlockStart());
  EXPECT_EQ(kBottom, converter.BlockEnd());
}

TEST(WritingModeUtilsTest, PhysicalToLogicalVlrLtr) {
  PhysicalToLogical<int> converter(
      {WritingMode::kVerticalLr, TextDirection::kLtr}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kTop, converter.InlineStart());
  EXPECT_EQ(kBottom, converter.InlineEnd());
  EXPECT_EQ(kLeft, converter.BlockStart());
  EXPECT_EQ(kRight, converter.BlockEnd());
}

TEST(WritingModeUtilsTest, PhysicalToLogicalVlrRtl) {
  PhysicalToLogical<int> converter(
      {WritingMode::kVerticalLr, TextDirection::kRtl}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kBottom, converter.InlineStart());
  EXPECT_EQ(kTop, converter.InlineEnd());
  EXPECT_EQ(kLeft, converter.BlockStart());
  EXPECT_EQ(kRight, converter.BlockEnd());
}

TEST(WritingModeUtilsTest, PhysicalToLogicalVrlLtr) {
  PhysicalToLogical<int> converter(
      {WritingMode::kVerticalRl, TextDirection::kLtr}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kTop, converter.InlineStart());
  EXPECT_EQ(kBottom, converter.InlineEnd());
  EXPECT_EQ(kRight, converter.BlockStart());
  EXPECT_EQ(kLeft, converter.BlockEnd());
}

TEST(WritingModeUtilsTest, PhysicalToLogicalVrlRtl) {
  PhysicalToLogical<int> converter(
      {WritingMode::kVerticalRl, TextDirection::kRtl}, kTop, kRight, kBottom,
      kLeft);
  EXPECT_EQ(kBottom, converter.InlineStart());
  EXPECT_EQ(kTop, converter.InlineEnd());
  EXPECT_EQ(kRight, converter.BlockStart());
  EXPECT_EQ(kLeft, converter.BlockEnd());
}

enum { kInlineStart = 1000, kInlineEnd, kBlockStart, kBlockEnd };

TEST(WritingModeUtilsTest, LogicalToPhysicalHorizontalLtr) {
  LogicalToPhysical<int> converter(
      {WritingMode::kHorizontalTb, TextDirection::kLtr}, kInlineStart,
      kInlineEnd, kBlockStart, kBlockEnd);
  EXPECT_EQ(kInlineStart, converter.Left());
  EXPECT_EQ(kInlineEnd, converter.Right());
  EXPECT_EQ(kBlockStart, converter.Top());
  EXPECT_EQ(kBlockEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalHorizontalRtl) {
  LogicalToPhysical<int> converter(
      {WritingMode::kHorizontalTb, TextDirection::kRtl}, kInlineStart,
      kInlineEnd, kBlockStart, kBlockEnd);
  EXPECT_EQ(kInlineEnd, converter.Left());
  EXPECT_EQ(kInlineStart, converter.Right());
  EXPECT_EQ(kBlockStart, converter.Top());
  EXPECT_EQ(kBlockEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalVlrLtr) {
  LogicalToPhysical<int> converter(
      {WritingMode::kVerticalLr, TextDirection::kLtr}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockStart, converter.Left());
  EXPECT_EQ(kBlockEnd, converter.Right());
  EXPECT_EQ(kInlineStart, converter.Top());
  EXPECT_EQ(kInlineEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalVlrRtl) {
  LogicalToPhysical<int> converter(
      {WritingMode::kVerticalLr, TextDirection::kRtl}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockStart, converter.Left());
  EXPECT_EQ(kBlockEnd, converter.Right());
  EXPECT_EQ(kInlineEnd, converter.Top());
  EXPECT_EQ(kInlineStart, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalVrlLtr) {
  LogicalToPhysical<int> converter(
      {WritingMode::kVerticalRl, TextDirection::kLtr}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockEnd, converter.Left());
  EXPECT_EQ(kBlockStart, converter.Right());
  EXPECT_EQ(kInlineStart, converter.Top());
  EXPECT_EQ(kInlineEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalVrlRtl) {
  LogicalToPhysical<int> converter(
      {WritingMode::kVerticalRl, TextDirection::kRtl}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockEnd, converter.Left());
  EXPECT_EQ(kBlockStart, converter.Right());
  EXPECT_EQ(kInlineEnd, converter.Top());
  EXPECT_EQ(kInlineStart, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalSlrLtr) {
  LogicalToPhysical<int> converter(
      {WritingMode::kSidewaysLr, TextDirection::kLtr}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockStart, converter.Left());
  EXPECT_EQ(kBlockEnd, converter.Right());
  EXPECT_EQ(kInlineEnd, converter.Top());
  EXPECT_EQ(kInlineStart, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalSlrRtl) {
  LogicalToPhysical<int> converter(
      {WritingMode::kSidewaysLr, TextDirection::kRtl}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockStart, converter.Left());
  EXPECT_EQ(kBlockEnd, converter.Right());
  EXPECT_EQ(kInlineStart, converter.Top());
  EXPECT_EQ(kInlineEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalSrlLtr) {
  LogicalToPhysical<int> converter(
      {WritingMode::kSidewaysRl, TextDirection::kLtr}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockEnd, converter.Left());
  EXPECT_EQ(kBlockStart, converter.Right());
  EXPECT_EQ(kInlineStart, converter.Top());
  EXPECT_EQ(kInlineEnd, converter.Bottom());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalSrlRtl) {
  LogicalToPhysical<int> converter(
      {WritingMode::kSidewaysRl, TextDirection::kRtl}, kInlineStart, kInlineEnd,
      kBlockStart, kBlockEnd);
  EXPECT_EQ(kBlockEnd, converter.Left());
  EXPECT_EQ(kBlockStart, converter.Right());
  EXPECT_EQ(kInlineEnd, converter.Top());
  EXPECT_EQ(kInlineStart, converter.Bottom());
}

class PhysicalValues {
  STACK_ALLOCATED();

 public:
  int Top() const { return top_; }
  int Right() const { return right_; }
  int Bottom() const { return bottom_; }
  int Left() const { return left_; }
  void SetTop(int top) { top_ = top; }
  void SetRight(int right) { right_ = right; }
  void SetBottom(int bottom) { bottom_ = bottom; }
  void SetLeft(int left) { left_ = left; }

 private:
  int top_ = kTop;
  int right_ = kRight;
  int bottom_ = kBottom;
  int left_ = kLeft;
};

TEST(WritingModeUtilsTest, PhysicalToLogicalGetter) {
  PhysicalValues physical_values;
  PhysicalToLogicalGetter<int, PhysicalValues> getter(
      {WritingMode::kVerticalRl, TextDirection::kRtl}, physical_values,
      &PhysicalValues::Top, &PhysicalValues::Right, &PhysicalValues::Bottom,
      &PhysicalValues::Left);

  EXPECT_EQ(kBottom, getter.InlineStart());
  EXPECT_EQ(kTop, getter.InlineEnd());
  EXPECT_EQ(kRight, getter.BlockStart());
  EXPECT_EQ(kLeft, getter.BlockEnd());
}

TEST(WritingModeUtilsTest, LogicalToPhysicalSetter) {
  PhysicalValues physical_values;
  LogicalToPhysicalSetter<int, PhysicalValues> setter(
      {WritingMode::kVerticalRl, TextDirection::kRtl}, physical_values,
      &PhysicalValues::SetTop, &PhysicalValues::SetRight,
      &PhysicalValues::SetBottom, &PhysicalValues::SetLeft);
  setter.SetInlineStart(kInlineStart);
  setter.SetInlineEnd(kInlineEnd);
  setter.SetBlockStart(kBlockStart);
  setter.SetBlockEnd(kBlockEnd);

  EXPECT_EQ(kBlockEnd, physical_values.Left());
  EXPECT_EQ(kBlockStart, physical_values.Right());
  EXPECT_EQ(kInlineEnd, physical_values.Top());
  EXPECT_EQ(kInlineStart, physical_values.Bottom());
}

class LogicalValues {
  STACK_ALLOCATED();

 public:
  int InlineStart() const { return inline_start_; }
  int InlineEnd() const { return inline_end_; }
  int BlockStart() const { return block_start_; }
  int BlockEnd() const { return block_end_; }
  void SetInlineStart(int inline_start) { inline_start_ = inline_start; }
  void SetInlineEnd(int inline_end) { inline_end_ = inline_end; }
  void SetBlockStart(int block_start) { block_start_ = block_start; }
  void SetBlockEnd(int block_end) { block_end_ = block_end; }

 private:
  int inline_start_ = kInlineStart;
  int inline_end_ = kInlineEnd;
  int block_start_ = kBlockStart;
  int block_end_ = kBlockEnd;
};

TEST(WritingModeUtilsTest, LogicalToPhysicalGetter) {
  LogicalValues logical_values;
  LogicalToPhysicalGetter<int, LogicalValues> getter(
      {WritingMode::kVerticalRl, TextDirection::kRtl}, logical_values,
      &LogicalValues::InlineStart, &LogicalValues::InlineEnd,
      &LogicalValues::BlockStart, &LogicalValues::BlockEnd);

  EXPECT_EQ(kBlockEnd, getter.Left());
  EXPECT_EQ(kBlockStart, getter.Right());
  EXPECT_EQ(kInlineEnd, getter.Top());
  EXPECT_EQ(kInlineStart, getter.Bottom());
}

}  // namespace

}  // namespace blink
