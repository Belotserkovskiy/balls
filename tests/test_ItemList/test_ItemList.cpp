#include <cstdio>

#include "gmock/gmock.h"

#include "ItemList.h"

class MockAbstractItem : public AbstractItem {
 public:
  MOCK_METHOD1(setParentList,
      void(ItemList *ballsList));
  MOCK_METHOD0(getId,
      itemId());
  MOCK_METHOD2(setSize,
      void(double width, double height));
  MOCK_METHOD0(getCoordinates,
      Coordinates());
  MOCK_METHOD0(getX,
      double());
  MOCK_METHOD0(getY,
      double());
  MOCK_METHOD0(getWidth,
      double());
  MOCK_METHOD0(getHeight,
      double());
  MOCK_METHOD2(checkTouch,
      bool(double X, double Y));
  MOCK_METHOD0(getVelocityX,
      double());
  MOCK_METHOD0(getVelocityY,
      double());
  MOCK_METHOD1(setVelocityX,
      void(double velocityX));
  MOCK_METHOD1(setVelocityY,
      void(double velocityY));
  MOCK_METHOD2(setCoordinates,
      int(double X, double Y));
  MOCK_METHOD2(moveBy,
      int(double deltaX, double deltaY));
  MOCK_METHOD0(lock,
      int());
  MOCK_METHOD0(isLocked,
      int());
  ~MockAbstractItem(){}
};

class ItemListTest : public testing::Test
{

public:

    ItemList ballsList;
    MockAbstractItem *item1, *item2;

    virtual void SetUp()
    {
        item1 = new MockAbstractItem;
        item2 = new MockAbstractItem;

        ballsList.addItem(item1);
        ballsList.addItem(item2);

    }
    virtual void TearDown()
    {

    }

};

TEST_F(ItemListTest, count)
{
    EXPECT_TRUE( ballsList.count() == 2);
    ballsList.clear();
}

TEST_F(ItemListTest, addItem)
{
    MockAbstractItem *item3 = new MockAbstractItem;
    ballsList.addItem(item3);
    EXPECT_TRUE( ballsList.count() == 3);
    ballsList.clear();
}

TEST_F(ItemListTest, deleteItem)
{
    ballsList.deleteItem( item1);
    EXPECT_TRUE( ballsList.count() == 2);
    ballsList.clear();
}

TEST_F(ItemListTest, clearItems)
{
    ballsList.clear();
    EXPECT_TRUE(ballsList.begin() == ballsList.end());
    EXPECT_TRUE( ballsList.count() == 0);
}
