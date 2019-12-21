#include <iostream>
#include <string>
using std::string;
using std::exception;

/**
 * class NoPrice - Exception object to throw when trying to purchase a non
 *                 purchasable seat
 */
class NoPrice:public exception{
public:
    const char* what() const noexcept {return "Not For Sale !";}
};

/**
 * abstract class Seat - a default seat object
 */
class Seat
{
protected:
    int line;
    int chair;
    int base_price;
    /**
     * @return the line and chair of the seat in a string
     * example -  "line: 4 , chair: 7"
     */
    string lineChair() const;
public:
    /**
     * virtual method
     * @return the location of the seat
     */
    virtual string location() const = 0;
    /**
     * virtual method
     * @return the price of the seat
     */
    virtual int price() const = 0;
    virtual ~Seat(){};
};

/**
 * abstract class MainHallSeat - object of a seat in the main hall
 */
class MainHallSeat:public Seat
{
protected:
    //additional price for all main hall seats
    int main_hall_price = 100;
public:
    virtual ~MainHallSeat(){};
};

/**
 * abstract class RegularSeat - object of a Regular seat in the main hall
 */
class RegularSeat:public MainHallSeat
{
protected:
    //the area name of the seat (uppercase english letter)
    char area;
    /**
     * @return the area of the seat in a string
     * example -  "area: A"
     */
    string areaLocation() const;
public:
    virtual ~RegularSeat(){};
};

/**
 * class FrontRegularSeat - a Regular seat in the front of the main hall
 */
class FrontRegularSeat:public RegularSeat
{
    //additional price for all front seats in the main hall
    int front_regular_price = 500;
public:
    FrontRegularSeat(char area, int line, int chair, int base_price);
    string location() const;
    int price() const;
};

/**
 * class MiddleRegularSeat - a Regular seat in the middle of the main hall
 */
class MiddleRegularSeat:public RegularSeat
{
    //additional price for all middle seats in the main hall
    int middle_regular_price = 250;
public:
    MiddleRegularSeat(char area, int line, int chair, int base_price);
    string location() const;
    int price() const;
};

/**
 * class RearRegularSeat - a Regular seat in the rear of the main hall
 */
class RearRegularSeat:public RegularSeat
{
public:
    RearRegularSeat(char area, int line, int chair, int base_price);
    string location() const;
    int price() const;
};

/**
 * abstract class SpecialSeat - object of a Special seat in the main hall
 */
class SpecialSeat:public MainHallSeat
{
protected:
    //additional price for all special seats in the main hall
    int special_seat_price = 300;
public:
    virtual ~SpecialSeat(){};
};

/**
 * class GoldenCircleSeat - a special seat in the main hall which is the most
 *                          expensive
 */
class GoldenCircleSeat:public SpecialSeat
{
    //additional price for all Golden Circle seats in the main hall
    int golden_circle_price = 1000;
public:
    GoldenCircleSeat(int line, int chair, int base_price);
    string location() const;
    int price() const;
};

/**
 * class DisablePodiumSeat - a special seat in the main hall which is reserved
 *                           for disabled people only and have a fixed price
 */
class DisablePodiumSeat:public SpecialSeat
{
    //fixed price for all the seats in the disabled podium
    int disable_podium_price = 200;
public:
    DisablePodiumSeat(int line, int chair, int base_price = 0);
    string location() const;
    int price() const;
};

/**
 * class GreenRoomSeat - object of a seat in the Green room which is for VIP
 *                       only and not for sale
 */
//price() method returning an explantion that there is no price
class GreenRoomSeat:public Seat
{
public:
    GreenRoomSeat(int line, int chair);
    //price() method returning an explanation that there is no price
    int price() const;
    string location() const;
};
