#include "gmock/gmock.h"

#include "ItemList.h"
#include "MovementComputer.h"

using ::testing::_;
using ::testing::DoubleEq;
using ::testing::NiceMock;

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

class MovementComputerTest : public testing::Test
{

public:

    ItemList ballsList;
    NiceMock<MockAbstractItem> item1, item2;
    MovementComputer m_computer;

    virtual void SetUp()
    {

        ballsList.addItem(&item1);
        ballsList.addItem(&item2);

        m_computer.setItemsList( &ballsList);

    }
    virtual void TearDown()
    {

    }

};

TEST_F(MovementComputerTest, border)
{
    EXPECT_TRUE( m_computer.getBorderFlag() == BorderFlag::withoutBorder);
    double width, height;
    m_computer.getField( &width, &height);
    EXPECT_DOUBLE_EQ( width, 0);
    EXPECT_DOUBLE_EQ( height, 0);

    m_computer.setField(200, 300);
    m_computer.getField( &width, &height);
    EXPECT_DOUBLE_EQ( width, 200);
    EXPECT_DOUBLE_EQ( height, 300);

    m_computer.setBorderFlag( BorderFlag::withBorder);
    EXPECT_TRUE( m_computer.getBorderFlag() == BorderFlag::withBorder);
}

TEST_F(MovementComputerTest, typeOfInteractionBetweenItems)
{
    EXPECT_TRUE( m_computer.getInteractionType() == TypeOfInteraction::withoutInteraction);

    m_computer.setTypeOfInteraction( TypeOfInteraction::elastic);

    EXPECT_TRUE( m_computer.getInteractionType() == TypeOfInteraction::elastic);
}

TEST_F(MovementComputerTest, start)
{
    EXPECT_CALL( item1 , getX()).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , getY()).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , setVelocityX(_)).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , setVelocityY(_)).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , moveBy( _, _)).Times(testing::AtLeast(1));

    m_computer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    m_computer.stop();
}

TEST_F(MovementComputerTest, pause)
{
    m_computer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    m_computer.pause();

    EXPECT_CALL( item1 , getX()).Times(0);
    EXPECT_CALL( item1 , getY()).Times(0);
    EXPECT_CALL( item1 , setVelocityX(_)).Times(0);
    EXPECT_CALL( item1 , setVelocityY(_)).Times(0);
    EXPECT_CALL( item1 , moveBy( _, _)).Times(0);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST_F(MovementComputerTest, checkComputation)
{
    EXPECT_CALL( item1 , getX())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(100));
    EXPECT_CALL( item1 , getY())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(100));
    EXPECT_CALL( item1 , getId())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(1));

    EXPECT_CALL( item2 , getX())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(200));
    EXPECT_CALL( item2 , getY())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(100));
    EXPECT_CALL( item2 , getId())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(testing::Return(2));


    EXPECT_CALL( item1 , setVelocityX( DoubleEq(0.008))).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , setVelocityY( DoubleEq(0))).Times(testing::AtLeast(1));
    EXPECT_CALL( item1 , moveBy( _ , _ )).Times(testing::AtLeast(1));

    EXPECT_CALL( item2 , setVelocityX( DoubleEq(-0.008))).Times(testing::AtLeast(1));
    EXPECT_CALL( item2 , setVelocityY( DoubleEq(0))).Times(testing::AtLeast(1));
    EXPECT_CALL( item2 , moveBy( _ , _ )).Times(testing::AtLeast(1));

    m_computer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    m_computer.pause();

    EXPECT_CALL( item1 , setVelocityX( DoubleEq(0))).Times(testing::AtLeast(1));
    EXPECT_CALL( item2 , setVelocityX( DoubleEq(0))).Times(testing::AtLeast(1));
    m_computer.stop();
}
