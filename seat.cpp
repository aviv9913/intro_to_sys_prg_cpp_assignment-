#include "seat.h"
using std::to_string;


string Seat::lineChair() const {
    string str = "line: " + to_string(this->line) +
            ", chair: " + to_string(this->chair);
    return str;
}


string RegularSeat::areaLocation() const {
    string str = "area: ";
    str+=this->area;
    str+= ", ";
    return str;
}

FrontRegularSeat::FrontRegularSeat(char area, int line, int chair,
        int base_price) {
    this->area = area;
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

string FrontRegularSeat::location() const {
    string str ="Front-> " + this->areaLocation() + this->lineChair();
    return str;
}

int FrontRegularSeat::price() const {
    return this->base_price + main_hall_price + front_regular_price;
}

MiddleRegularSeat::MiddleRegularSeat(char area, int line, int chair,
                                   int base_price) {
    this->area = area;
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

string MiddleRegularSeat::location() const {
    string str ="Middle-> " + this->areaLocation() + this->lineChair();
    return str;
}

int MiddleRegularSeat::price() const {
    return this->base_price + main_hall_price + middle_regular_price;
}

RearRegularSeat::RearRegularSeat(char area, int line, int chair,
                                     int base_price) {
    this->area = area;
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

string RearRegularSeat::location() const {
    string str ="Rear-> " + this->areaLocation() + this->lineChair();
    return str;
}

int RearRegularSeat::price() const {
    return this->base_price + main_hall_price;
}

GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int base_price) {
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

string GoldenCircleSeat::location() const {
    string str ="Golden Circle-> " + this->lineChair();
    return str;
}

int GoldenCircleSeat::price() const {
    return this->base_price + main_hall_price + special_seat_price
                + golden_circle_price;
}

DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int base_price) {
    this->line = line;
    this->chair = chair;
    this->base_price = base_price;
}

string DisablePodiumSeat::location() const {
    string str ="Disable Podium-> " + this->lineChair();
    return str;
}

int DisablePodiumSeat::price() const {
    return disable_podium_price;
}

GreenRoomSeat::GreenRoomSeat(int line, int chair) {
    this->line = line;
    this->chair = chair;
}

string GreenRoomSeat::location() const {
    string str ="Green Room-> " + this->lineChair();
    return str;
}

int GreenRoomSeat::price() const {
    throw NoPrice();
}
