#include "Microwave.h"

#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"

using ::testing::_;
using ::testing::Return;

class TestIdleState : public ::testing::Test
{
protected:
    TestIdleState()
        : microwave(light, motor, system, ui)
    {
    }

    virtual ~TestIdleState() {}

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave microwave;
};

TEST_F(TestIdleState, test_start_event)
{
    //  microwave start example
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(light, On()).Times(1);
    EXPECT_CALL(ui, StartClock());

    EXPECT_EQ(STATE_HEATING, microwave.HandleIdleState(EV_START));
}

TEST_F(TestIdleState, test_microwave_sequence_event)
{
    // microwave starts and reheat
    EXPECT_EQ(STATE_IDLE, microwave.getCurrentState());
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(light, On()).Times(1);
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.getCurrentState());

    // microwave pause
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());
    microwave.HandleEvent(EV_PAUSE);
    EXPECT_EQ(STATE_PAUSED, microwave.getCurrentState());

    // microwave restart
    EXPECT_CALL(ui, StartClock());
    EXPECT_CALL(ui, Ping());
    microwave.HandleEvent(EV_RESTART);
    EXPECT_EQ(STATE_RESTARTED, microwave.getCurrentState());

    // microwave reheat
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.getCurrentState());

    // microwave time up
    microwave.HandleEvent(EV_TIME_UP);
    EXPECT_EQ(STATE_COOKING_COMPLETE, microwave.getCurrentState());

    // microwave finish
    EXPECT_CALL(light, Off()).Times(1);
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());
    microwave.HandleEvent(EV_COOKING_COMPLETE);
    EXPECT_EQ(STATE_IDLE, microwave.getCurrentState());
}

TEST_F(TestIdleState, test_microwave_stop_event)
{
    // microwave starts and reheat
    EXPECT_EQ(STATE_IDLE, microwave.getCurrentState());
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(light, On()).Times(1);
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.getCurrentState());

    // microwave pause
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());
    microwave.HandleEvent(EV_PAUSE);
    EXPECT_EQ(STATE_PAUSED, microwave.getCurrentState());

    // microwave stop
    microwave.HandleEvent(EV_STOP);
    EXPECT_EQ(STATE_COOKING_COMPLETE, microwave.getCurrentState());

    // microwave finish
    EXPECT_CALL(light, Off()).Times(1);
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());
    microwave.HandleEvent(EV_COOKING_COMPLETE);
    EXPECT_EQ(STATE_IDLE, microwave.getCurrentState());
}