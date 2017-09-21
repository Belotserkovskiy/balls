#include <gmock/gmock.h>

#include <Ball.h>

class BallTest : public testing::Test
{

public:

    Ball *ball;

    virtual void SetUp()
    {
        ball = new Ball( 200, 300, 1);


    }
    virtual void TearDown()
    {
        delete ball;
    }

};

TEST_F(BallTest, getId)
{
    EXPECT_TRUE( ball->getId() == 1);
}

TEST_F(BallTest, getX)
{
    EXPECT_DOUBLE_EQ( ball->getX(), 200);
}

TEST_F(BallTest, getY)
{
    EXPECT_DOUBLE_EQ( ball->getY(),300);
}

TEST_F(BallTest, getCoordinates)
{
    Coordinates temp =  ball->getCoordinates();
    EXPECT_DOUBLE_EQ( temp.x, 200);
    EXPECT_DOUBLE_EQ( temp.y, 300);
}


TEST_F(BallTest, checkTouch)
{
    EXPECT_TRUE( ball->checkTouch( 220, 310));
    EXPECT_FALSE( ball->checkTouch( 250, 350));
}

TEST_F(BallTest, checkSize)
{
    EXPECT_DOUBLE_EQ( ball->getWidth(),50);  // default value
    EXPECT_DOUBLE_EQ( ball->getHeight(),50); // default value

    ball->setSize(100, 120);  // it use only the first value

    EXPECT_DOUBLE_EQ( ball->getWidth(),100);
    EXPECT_DOUBLE_EQ( ball->getHeight(),100); // because it is circle
}

TEST_F(BallTest, velocity)
{
    EXPECT_DOUBLE_EQ( ball->getVelocityX(),0);
    EXPECT_DOUBLE_EQ( ball->getVelocityY(),0);

    ball->setVelocityX(10);
    ball->setVelocityY(15);

    EXPECT_DOUBLE_EQ( ball->getVelocityX(),10);
    EXPECT_DOUBLE_EQ( ball->getVelocityY(),15);
}

TEST_F(BallTest, setCoordinates)
{
    ball->setCoordinates(12, 17);

    EXPECT_DOUBLE_EQ( ball->getX(),12);
    EXPECT_DOUBLE_EQ( ball->getY(),17);
}

TEST_F(BallTest, moveBy)
{
    ball->setCoordinates(12, 17);
    ball->moveBy(5, 7);

    EXPECT_DOUBLE_EQ( ball->getX(),17);
    EXPECT_DOUBLE_EQ( ball->getY(),24);
}

TEST_F(BallTest, lock)
{
    ball->lock();
    EXPECT_TRUE( ball->isLocked());

    ball->unlock();
    EXPECT_FALSE( ball->isLocked());
}
