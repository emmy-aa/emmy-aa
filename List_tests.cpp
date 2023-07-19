// FILE: List_tests.cpp
// CS 223 Winter 2023, Lab 2
//
// Student Name: Emmy Apaloo
// Date: 03-20-2023
//
// List class testing for a circular DLL with sentinel node.
//

#include <iostream>
#include <sstream>
#include <string>

#include "List.hpp"
#include "gtest/gtest.h"  // declares the testing framework

using namespace std;
using namespace cs223_dll;

/*
 * Tests for the List class are given below. For this lab,
 * you are responsible for writing any tests not already provided.
 *
 * Write tests ONE AT A TIME as you go through the
 * Test-Driven Development (TDD) process.
 *
 * Take time to plan out each test! Remember: Setup, Execute, Check!
 *
 * NOTE: Once a function has been tested and is working, you can use 
 *   it when writing later tests. 
 *
 * REMINDER: For 2-argument EXPECTS and ASSERTS, the first argument 
 *   is the actual value from executing the function, and the second 
 *   argument is the expected correct value.
 *
 * --------- DO NOT CHANGE THE ORDER OF THE TESTS ---------
 */

namespace {

// Create some global Person objects to use in tests
Person Mickey_Mouse("Mickey", "Mouse", 45);
Person Minnie_Mouse("Minnie", "Mouse", 45);
Person Peter_Pan("Peter", "Pan", 100);
Person Ziggy_Wilson("Ziggy", "Wilson", 5);
Person Skye_Wilson("Skye", "Wilson", 4);
Person Mister_Gray("Mister", "Gray", 10);
Person Xerea_Cat("Xerea", "Cat", 5);
Person Dopey_Dwarf("Dopey", "Dwarf", 73);
Person Sleepy_Dwarf("Sleepy", "Dwarf", 73);
Person Happy_Dwarf("Happy", "Dwarf", 73);
Person Snow_White("Snow", "White", 21);

// An array of 10 persons
Person person[] = {Mickey_Mouse, Minnie_Mouse, Peter_Pan,   Ziggy_Wilson,
                   Skye_Wilson,  Mister_Gray,  Dopey_Dwarf, Sleepy_Dwarf,
                   Happy_Dwarf,  Snow_White};


/* ---------------------------------------------------------
 *  Tests for default constructor and is_empty (PROVIDED)
 *    - Default_Constructor_Creates_Empty_List
 * ---------------------------------------------------------
 */

TEST(DefaultConstructorTest, Default_Constructor_Creates_Empty_List)
{
    List L1;
    EXPECT_TRUE(L1.is_empty());
}

 /*---------------------------------------------------------
 *  Tests for append, front, back, and is_empty (PROVIDED)
 *    - Append_to_an_Empty_List
 *    - Append_to_a_List_Containing_One_Item
 *    - Append_to_a_List_Containing_Two_Items
 *    - Append_Three_Times_then_Traverse_BackToFront
 *    - Append_Three_Times_then_Traverse_FrontToBack
 * --------------------------------------------------------- */
 

   TEST(AppendTest, Append_to_an_Empty_List)
{
    List L1;
    L1.append(Happy_Dwarf);
    ASSERT_FALSE(L1.is_empty());
    EXPECT_EQ(L1.front(), Happy_Dwarf);
    EXPECT_EQ(L1.back(), Happy_Dwarf);
}

TEST(AppendTest, Append_to_a_List_Containing_One_Item)
{
    List L1;
    L1.append(Happy_Dwarf);
    L1.append(Minnie_Mouse);
    EXPECT_EQ(L1.front(), Happy_Dwarf);
    EXPECT_EQ(L1.back(), Minnie_Mouse);
}

TEST(AppendTest, Append_to_a_List_Containing_Two_Items)
{
    List L1;
    L1.append(Happy_Dwarf);
    L1.append(Minnie_Mouse);
    L1.append(Ziggy_Wilson);
    EXPECT_EQ(L1.front(), Happy_Dwarf);
    EXPECT_EQ(L1.back(), Ziggy_Wilson);
}

// Make sure the prev pointers are being set correctly
TEST(TestPointersAfterAppend, Append_Three_Times_then_Traverse_BackToFront)
{
    List L1;
    L1.append(Happy_Dwarf);
    L1.append(Minnie_Mouse);
    L1.append(Ziggy_Wilson);
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterAppend, Append_Three_Times_then_Traverse_FrontToBack)
{
    List L1;
    L1.append(Happy_Dwarf);
    L1.append(Minnie_Mouse);
    L1.append(Ziggy_Wilson);
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

/* ---------------------------------------------------------
 *  Tests for length (PROVIDED)
 *    - Length_of_Empty_List
 *    - Length_of_List_with_One_Item
 *    - Length_of_List_with_Three_Items
 * ---------------------------------------------------------
 */

TEST(LengthTest, Length_of_Empty_List)
{
    List L1;
    EXPECT_EQ(L1.length(), 0);
}

TEST(LengthTest, Length_of_List_with_One_Item)
{
    List L1;
    L1.append(Ziggy_Wilson);
    EXPECT_EQ(L1.length(), 1);
}

TEST(LengthTest, Length_of_List_with_Three_Items)
{
    List L1;
    L1.append(Ziggy_Wilson);
    L1.append(Happy_Dwarf);
    L1.append(Minnie_Mouse);
    EXPECT_EQ(L1.length(), 3);
}

// /* ---------------------------------------------------------
//  *  Tests for contains (PROVIDED)
//  *    - Empty_List_and_Contains_Returns_True
//  *    - Length1_List_and_Contains_Returns_True
//  *    - Length1_List_and_Contains_Returns_False
//  *    - Length4_List_and_Contains_Returns_True_with_Item_at_Tail
//  *    - Length4_List_and_Contains_Returns_False
//  * ---------------------------------------------------------
//  */

TEST(ContainsTest, Empty_List_and_Contains_Returns_True)
{
    List L1;
    EXPECT_FALSE(L1.contains(Happy_Dwarf));
}

TEST(ContainsTest, Length1_List_and_Contains_Returns_True)
{
    List L1;
    L1.append(Happy_Dwarf);
    EXPECT_TRUE(L1.contains(Happy_Dwarf));
}

TEST(ContainsTest, Length1_List_and_Contains_Returns_False)
{
    List L1;
    L1.append(Happy_Dwarf);
    EXPECT_FALSE(L1.contains(Ziggy_Wilson));
}

TEST(ContainsTest, Length4_List_and_Contains_Returns_True_with_Item_at_Tail)
{
    List L1({Mickey_Mouse, Snow_White, Happy_Dwarf, Ziggy_Wilson});
    EXPECT_TRUE(L1.contains(Ziggy_Wilson));
}

TEST(ContainsTest, Length4_List_and_Contains_Returns_False)
{
    List L1({Mickey_Mouse, Snow_White, Happy_Dwarf, Ziggy_Wilson});
    EXPECT_FALSE(L1.contains(Skye_Wilson));
}

// /* ---------------------------------------------------------
 // *  Tests for bracket indexing [] (NOT PROVIDED)
 // *    - STUDENT_Index_0_in_Length1_List
 // *    - STUDENT_Index_0_in_Length3_List
 // *    - STUDENT_Index_1_in_Length3_List
 // *    - STUDENT_Index_2_in_Length3_List
 // * ---------------------------------------------------------
 // */

// Create some Person objects to use in these tests

Person Emmy_Black("Emmy", "Black", 34);
Person Emily_Stone("Emily","Stone", 45);
Person Zee_Richardson("Zee", "Richardson",21);
Person Kia_Wakuika("Kia", "Wakuika", 22);
Person Thomas_Steel("Thomas", "Steel", 35);

TEST(BracketIndexingTest, STUDENT_Index_0_in_Length1_List)
{
    List L1({Emmy_Black});
    EXPECT_EQ(L1[0], Emmy_Black);

}

TEST(BracketIndexingTest, STUDENT_Index_0_in_Length3_List)
{
    List L1({Emily_Stone, Thomas_Steel, Zee_Richardson});
    EXPECT_EQ(L1[0],Emily_Stone);

}

TEST(BracketIndexingTest, STUDENT_Index_1_in_Length3_List)
{
    List L1({Kia_Wakuika, Zee_Richardson, Emily_Stone});
    EXPECT_EQ(L1[1], Zee_Richardson);
}

TEST(BracketIndexingTest, STUDENT_Index_2_in_Length3_List)
{
    List L1({Zee_Richardson,Emmy_Black, Kia_Wakuika});
    EXPECT_EQ(L1[2], Kia_Wakuika);
}

/* ---------------------------------------------------------
 *  Tests for insert (PROVIDED)
 *    - Insert_at_Index_0_of_Empty_List
 *    - Insert_at_Index_0_of_Length1_List
 *    - Insert_at_Index_1_of_Length1_List
 *    - Insert_at_Index_1_of_Length3_List
 *    - Insert_at_Index_2_of_Length3_List
 *    - Insert_at_Index_3_of_Length3_List
 *    - Insert_into_Length3_List_then_Traverse_BackToFront
 *    - Insert_into_Length3_List_then_Traverse_FrontToBack
 * ---------------------------------------------------------
 */

 TEST(InsertTest, Insert_at_Index_0_of_Empty_List)
 {
    List L1;
    L1.insert(0, Happy_Dwarf);
    ASSERT_FALSE(L1.is_empty());
    EXPECT_EQ(L1[0], Happy_Dwarf);
}

TEST(InsertTest, Insert_at_Index_0_of_Length1_List)
{
    List L;
    L.append(Happy_Dwarf);
    L.insert(0, Minnie_Mouse);
    EXPECT_EQ(L[0], Minnie_Mouse);
    EXPECT_EQ(L[1], Happy_Dwarf);
}

TEST(InsertTest, Insert_at_Index_1_of_Length1_List)
{
    List L;
    L.append(Happy_Dwarf);
    L.insert(1, Minnie_Mouse);
    EXPECT_EQ(L[0], Happy_Dwarf);
    EXPECT_EQ(L[1], Minnie_Mouse);
}

TEST(InsertTest, Insert_at_Index_1_of_Length3_List)
{
    List L({Snow_White, Happy_Dwarf, Ziggy_Wilson});
    L.insert(1, Peter_Pan);
    EXPECT_EQ(L[0], Snow_White);
    EXPECT_EQ(L[1], Peter_Pan);
    EXPECT_EQ(L[2], Happy_Dwarf);
    EXPECT_EQ(L[3], Ziggy_Wilson);
}

TEST(InsertTest, Insert_at_Index_2_of_Length3_List)
{
    List L({Snow_White, Happy_Dwarf, Ziggy_Wilson});
    L.insert(2, Peter_Pan);
    EXPECT_EQ(L[0], Snow_White);
    EXPECT_EQ(L[1], Happy_Dwarf);
    EXPECT_EQ(L[2], Peter_Pan);
    EXPECT_EQ(L[3], Ziggy_Wilson);
}

TEST(InsertTest, Insert_at_Index_3_of_Length3_List)
{
    List L({Snow_White, Happy_Dwarf, Ziggy_Wilson});
    L.insert(3, Peter_Pan);
    EXPECT_EQ(L[0], Snow_White);
    EXPECT_EQ(L[1], Happy_Dwarf);
    EXPECT_EQ(L[2], Ziggy_Wilson);
    EXPECT_EQ(L[3], Peter_Pan);
}

// Make sure the prev pointers are being set correctly
TEST(TestPointersAfterInsert, Insert_into_Length3_List_then_Traverse_BackToFront)
{
    List L({Snow_White, Happy_Dwarf, Ziggy_Wilson});
    L.insert(1, Peter_Pan);
    const DLL_node* curr = L.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Peter_Pan);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Snow_White);
    curr = curr->prev();
    EXPECT_EQ(L.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterInsert, Insert_into_Length3_List_then_Traverse_FrontToBack)
{
    List L({Snow_White, Happy_Dwarf, Ziggy_Wilson});
    L.insert(1, Peter_Pan);
    const DLL_node* curr = L.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Snow_White);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Peter_Pan);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(L.get_head_ptr(), curr);
}

/* ---------------------------------------------------------
 *  Tests for remove(item) (NOT PROVIDED)
 *    - STUDENT_Remove_Item_from_Empty_List_Returns_False
 *    - STUDENT_Remove_Item_from_Length1_List_Returns_True
 *    - STUDENT_Remove_Item_from_Length1_List_Returns_False
 *    - STUDENT_Remove_Item_from_Longer_List_without_Duplicates_Returns_True
 *    - STUDENT_Remove_Item_from_Longer_List_without_Duplicates_Returns_False
 *    - STUDENT_Remove_Item_from_Longer_List_with_Item_at_Indexes_1_and_3
 *
 *  Hint: Use bracket indexing to check that all items still
 *        in the list are in the correct order.
 * ---------------------------------------------------------
 */

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Empty_List_Returns_False)
{
    List L1;
    EXPECT_FALSE(L1.remove(Emmy_Black));
}

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Length1_List_Returns_True)
{
    List L1({Emily_Stone});
    EXPECT_TRUE(L1.remove(Emily_Stone));
}

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Length1_List_Returns_False)
{
    List L1({Emily_Stone});
    EXPECT_FALSE(L1.remove(Kia_Wakuika));
}

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Longer_List_without_Duplicates_Returns_True)
{
    List L1({Emmy_Black, Zee_Richardson, Emily_Stone});
    EXPECT_TRUE(L1.remove(Emily_Stone));
}

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Longer_List_without_Duplicates_Returns_False)
{
    List L1({Emmy_Black, Emily_Stone, Zee_Richardson, Kia_Wakuika});
    EXPECT_FALSE(L1.remove(Thomas_Steel));

}

TEST(RemoveItemTest, STUDENT_Remove_Item_from_Longer_List_with_Item_at_Indexes_1_and_3)
{
    List L1({Thomas_Steel, Emily_Stone, Zee_Richardson, Emily_Stone, Kia_Wakuika});
    EXPECT_TRUE(L1.remove(Emily_Stone));

}

/* ------------------------------------------------------------
 *  Test pointers after remove(item) (PROVIDED)
 *    - Remove_Item_from_Length3_List_then_Traverse_BackToFront
 *    - Insert_Item_from_Length3_List_then_Traverse_FrontToBack
 * ------------------------------------------------------------
 */

//Make sure the prev pointers are being set correctly
TEST(TestPointersAfterRemoveITEM, Remove_Item_from_Length3_List_then_Traverse_BackToFront)
{
    List L1({Happy_Dwarf, Snow_White, Mickey_Mouse});
    L1.remove(Snow_White);
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Mickey_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterRemoveITEM, Remove_Item_from_Length3_List_then_Traverse_FrontToBack)
{
    List L1({Happy_Dwarf, Minnie_Mouse, Ziggy_Wilson});
    L1.remove(Minnie_Mouse);
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

/* ---------------------------------------------------------
 *  Tests for remove(index) (PROVIDED)
 *    - Remove_Item_at_Index_0_of_Length1_List
 *    - Remove_Item_at_Index_0_of_Length3_List
 *    - Remove_Item_at_Index_1_of_Length3_List
 *    - Remove_Item_at_Index_2_of_Length3_List
 *    - Remove_from_Length3_List_then_Traverse_BackToFront
 *    - Remove_Item_from_Length3_List_then_Traverse_FrontToBack
 * ---------------------------------------------------------
 */

TEST(RemoveIndexTest, Remove_Item_at_Index_0_of_Length1_List)
{
    List L1;
    L1.append(Skye_Wilson);
    L1.remove(0);
    EXPECT_TRUE(L1.is_empty());
}

TEST(RemoveIndexTest, Remove_Item_at_Index_0_of_Length3_List)
{
    List L1({Mister_Gray, Skye_Wilson, Sleepy_Dwarf});
    L1.remove(0);
    EXPECT_EQ(L1.front(), Skye_Wilson);
    EXPECT_EQ(L1.back(), Sleepy_Dwarf);
}

TEST(RemoveIndexTest, Remove_Item_at_Index_1_of_Length3_List)
{
    List L1({Mister_Gray, Skye_Wilson, Sleepy_Dwarf});
    L1.remove(1);
    EXPECT_EQ(L1.front(), Mister_Gray);
    EXPECT_EQ(L1.back(), Sleepy_Dwarf);
}

TEST(RemoveIndexTest, Remove_Item_at_Index_2_of_Length3_List)
{
    List L1({Mister_Gray, Skye_Wilson, Sleepy_Dwarf});
    L1.remove(2);
    EXPECT_EQ(L1.front(), Mister_Gray);
    EXPECT_EQ(L1.back(), Skye_Wilson);
}

// Make sure the prev pointers are being set correctly
TEST(TestPointersAfterRemoveINDEX, Remove_from_Length3_List_then_Traverse_BackToFront)
{
    List L1({Happy_Dwarf, Snow_White, Mickey_Mouse});
    L1.remove(Snow_White);
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Mickey_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterRemoveINDEX, Insert_from_Length3_List_then_Traverse_FrontToBack)
{
    List L1({Happy_Dwarf, Minnie_Mouse, Ziggy_Wilson});
    L1.remove(Minnie_Mouse);
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

/* ------------------------------------------------------------
 *  Test clear (PROVIDED)
 *    - Clear_Empty_List
 *    - Clear_Length1_List
 *    - Clear_Length3_List
 * ------------------------------------------------------------
 */

TEST(ClearTest, Clear_Empty_List)
{
    List L1;
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

TEST(ClearTest, Clear_Length1_List)
{
    List L1;
    L1.append(Happy_Dwarf);
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

TEST(ClearTest, Clear_Length3_List)
{
    List L1;
    L1.append(person[0]);
    L1.append(person[1]);
    L1.append(person[2]);
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

/* ---------------------------------------------------------
 *  Tests for copy constructor (PROVIDED)
 *    - Copy_Empty_List
 *    - Copy_Length1_List
 *    - Copy_Length3_List
 *    - Copy_and_Other_List_Are_Independent
 * ---------------------------------------------------------
 */

TEST(CopyConstructorTest, Copy_Empty_List)
{
    List L1;
    List L2(L1);
    EXPECT_TRUE(L2.is_empty());
}

TEST(CopyConstructorTest, Copy_Length1_List)
{
    List L1;
    L1.append(person[0]);
    List L2(L1);
    EXPECT_EQ(L2.front(), person[0]);
    EXPECT_EQ(L2.back(), person[0]);
}

TEST(CopyConstructorTest, Copy_Length3_List)
{
    List L1({person[2], person[1], person[0]});
    List L2(L1);
    EXPECT_EQ(L2.front(), person[2]);
    EXPECT_EQ(L2.back(), person[0]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());
}

TEST(CopyConstructorTest, Copy_and_Other_List_Are_Independent)
{
    List L1({person[2], person[1], person[0]});
    List L2(L1);
    L1.clear();
    EXPECT_FALSE(L2.is_empty());
}

/* ---------------------------------------------------------
 *  Tests for assignment operator (PROVIDED)
 *    - Self_Assignment_Does_Not_Crash
 *    - Assign_Length3_List_to_Different_Length3_List
 *    - Assign_Longer_List_to_Shorter_List
 *    - Assign_Shorter_List_to_Longer_List
 *    - Assignment_Chaining
 *    - This_List_is_Independent_of_Other_List
 * ---------------------------------------------------------
 */

TEST(AssignmentOperatorTest, Self_Assignment_Does_Not_Crash)
{
    List L1({person[2], person[1], person[0]});
    L1 = L1;
    EXPECT_EQ(L1.front(), person[2]);
    L1.remove(0);
    EXPECT_EQ(L1.front(), person[1]);
    L1.remove(0);
    EXPECT_EQ(L1.front(), person[0]);
    L1.remove(0);
    EXPECT_TRUE(L1.is_empty());
}

TEST(AssignmentOperatorTest, Assign_Length3_List_to_Different_Length3_List)
{
    List L1({person[2], person[1], person[0]});
    List L2({person[5], person[4], person[3]});
    L2 = L1;
    EXPECT_EQ(L2.front(), person[2]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());
}

TEST(AssignmentOperatorTest, Assign_Longer_List_to_Shorter_List)
{
    List L1({person[2], person[1], person[0]});
    List L2({person[4], person[3]});
    L2 = L1;
    EXPECT_EQ(L2.front(), person[2]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());
}

TEST(AssignmentOperatorTest, Assign_Shorter_List_to_Longer_List)
{
    List L1({person[1], person[0]});
    List L2({person[5], person[4], person[3]});
    L2 = L1;
    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());
}

TEST(AssignmentOperatorTest, Assignment_Chaining)
{
    List L1({person[1], person[0]});
    List L2({person[5], person[4], person[3]});
    List L3({person[7], person[6]});
    L3 = L2 = L1;

    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());

    EXPECT_EQ(L3.front(), person[1]);
    L3.remove(0);
    EXPECT_EQ(L3.front(), person[0]);
    L3.remove(0);
    EXPECT_TRUE(L3.is_empty());
}

TEST(AssignmentOperatorTest, This_List_is_Independent_of_Other_List)
{
    List L1({person[2], person[1], person[0]});
    List L2({person[5], person[4], person[3]});
    L2 = L1;
    L1.clear();
    EXPECT_EQ(L2.front(), person[2]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[1]);
    L2.remove(0);
    EXPECT_EQ(L2.front(), person[0]);
    L2.remove(0);
    EXPECT_TRUE(L2.is_empty());
}

/* ---------------------------------------------------------------
 *  Tests for equivalence operator (PROVIDED)
 *    - EmptyList_same_as_Another_EmptyList
 *    - EmptyList_not_same_as_Length1_List
 *    - Length3_List_not_same_as_Length3_List_With_Diff_First_Item
 *    - Length3_List_not_same_as_Length3_List_With_Diff_Last_Item
 *    - Length3_List_not_same_as_Length4_List_With_Same_First_Three_Items
 * ---------------------------------------------------------------
 */

TEST(EquivalenceTest, EmptyList_same_as_Another_EmptyList)
{
    List L1;
    List L2;
    EXPECT_TRUE(L1 == L2);
}

TEST(EquivalenceTest, EmptyList_not_same_as_Length1_List)
{
    List L1;
    List L2;

    L1.append(Skye_Wilson);
    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(EquivalenceTest, Length3_List_not_same_as_Length3_List_With_Diff_First_Item)
{
    List L1({Mister_Gray, Skye_Wilson, Ziggy_Wilson});
    List L2({Xerea_Cat, Skye_Wilson, Ziggy_Wilson});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(EquivalenceTest, Length3_List_not_same_as_Length3_List_With_Diff_Last_Item)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Xerea_Cat});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(EquivalenceTest, Length3_List_same_as_Length3_List_With_Same_Items_Same_Order)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Mister_Gray});

    EXPECT_TRUE(L1 == L2);
}

TEST(EquivalenceTest, Length3_List_not_same_as_Length4_List_With_Same_First_Three_Items)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Mister_Gray, Xerea_Cat});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

/* ---------------------------------------------------------
 *  Tests for stream output operator (PROVIDED)
 *    - Send_EmptyList_to_OutputStream
 *    - Send_Length1_List_to_OutputStream
 *    - Send_Length3_List_to_OutputStream
 * ---------------------------------------------------------
 */

/*/*TEST(StreamOutputTest, Send_EmptyList_to_OutputStream)
{
    stringstream out;
    List L1;
    out << L1;
    EXPECT_EQ(out.str(), "Empty List\n");
}

TEST(StreamOutputTest, Send_Length1_List_to_OutputStream)
{
    stringstream out;
    List L1;
    L1.append(Skye_Wilson);
    out << L1;
    EXPECT_EQ(out.str(), "List:\nPerson: Skye Wilson, age 4\n");
}

TEST(StreamOutputTest, Send_Length3_List_to_OutputStream)
{
    stringstream out;
    List L1({Mister_Gray, Skye_Wilson, Ziggy_Wilson});
    string correct = "List:\n";
    correct += "Person: Mister Gray, age 10\n";
    correct += "Person: Skye Wilson, age 4\n";
    correct += "Person: Ziggy Wilson, age 5\n";
    out << L1;
    EXPECT_EQ(out.str(), correct);
}*/


 } //namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
