#include <iostream>
#include <cmath>
#include <cassert>
#include <utility>

using namespace std;

class Car {
private:
    double speed;        // м/с
    double acceleration; // м/с²
    double angle;        // градусы
    double x;
    double y;

public:
    // Конструктор по умолчанию
    Car() : speed(0), acceleration(0), angle(0), x(0), y(0) {}

    // Конструктор инициализации
    Car(double spd, double acc, double ang, double xPos, double yPos) 
        : speed(spd), acceleration(acc), angle(ang), x(xPos), y(yPos) {}

    // Конструктор копирования
    Car(const Car& other) 
        : speed(other.speed), acceleration(other.acceleration), angle(other.angle), x(other.x), y(other.y) {}

    // Геттеры
    double getSpeed() const { return speed; }
    double getAcceleration() const { return acceleration; }
    double getAngle() const { return angle; }
    pair<double, double> getPosition() const { return {x, y}; }

    void setSpeed(double spd) { 
        if (spd < 0) {
            cerr << "Error: Speed cannot be negative." << endl;
            return;
        }
        speed = spd;
    }

    void setAcceleration(double acc) { acceleration = acc; }

    void setAngle(double ang) {  // Ф-ия нормализации угла, т.е. ограничивает его в пределах от 0 до 360 градусов, сохраняя значения на окружности.
        angle = ang - 360 * floor(ang / 360);
    }

    void updatePosition(double time) {
        speed += acceleration * time;
        if (speed < 0) {
            speed = 0;
        }

        double radians = angle * M_PI / 180.0;

        x += speed * cos(radians) * time;
        y += speed * sin(radians) * time;
    }

    void printState() const {
        cout << "Car state: Speed = " << speed
             << ", Acceleration = " << acceleration
             << ", Angle = " << angle
             << ", X = " << x << ", Y = " << y << endl;
    }
};

void runTests() {
    // Тест: Конструктор по умолчанию
    Car defaultCar;
    assert(defaultCar.getSpeed() == 0);
    assert(defaultCar.getAcceleration() == 0);
    assert(defaultCar.getAngle() == 0);
    assert(defaultCar.getPosition() == make_pair(0.0, 0.0));
    cout << "Test 1 passed: Default constructor\n";

    // Тест: Конструктор инициализации
    Car initializedCar(10, 2, 45, 0, 0);
    assert(initializedCar.getSpeed() == 10);
    assert(initializedCar.getAcceleration() == 2);
    assert(initializedCar.getAngle() == 45);
    assert(initializedCar.getPosition() == make_pair(0.0, 0.0));
    cout << "Test 2 passed: Initialization constructor\n";

    // Тест: Конструктор копирования
    Car copiedCar(initializedCar);
    assert(copiedCar.getSpeed() == 10);
    assert(copiedCar.getAcceleration() == 2);
    assert(copiedCar.getAngle() == 45);
    assert(copiedCar.getPosition() == make_pair(0.0, 0.0));
    cout << "Test 3 passed: Copy constructor\n";

    // Тест: Обновление позиции; Вручную были вычислены точные ожидаемые координаты, чтобы проверить, что ф-ия updatePosition работает правильно.
    initializedCar.updatePosition(1);
    pair<double, double> pos = initializedCar.getPosition();
    double expected_x = 10 * cos(45 * M_PI / 180) + 1 * 2 * cos(45 * M_PI / 180);
    double expected_y = 10 * sin(45 * M_PI / 180) + 1 * 2 * sin(45 * M_PI / 180);
    assert(fabs(pos.first - expected_x) < 0.01); 
    assert(fabs(pos.second - expected_y) < 0.01); 
    cout << "Test 4 passed: Position update\n";

    // Тест: Попытка установки отрицательной скорости
    Car carWithNegativeSpeed;
    carWithNegativeSpeed.setSpeed(-10);
    assert(carWithNegativeSpeed.getSpeed() == 0); 
    cout << "Test 5 passed: Negative speed rejected\n";

    // Тест: Нормализация угла
    Car angleTestCar;
    angleTestCar.setAngle(370);
    assert(angleTestCar.getAngle() == 10); // 370 градусов = 10 градусов

    angleTestCar.setAngle(-30);
    assert(angleTestCar.getAngle() == 330); // -30 градусов = 330 градусов
    cout << "Test 6 passed: Angle normalization\n";
}

int main() {
    runTests();
    cout << "All tests passed successfully!\n";

    // Пример работы с объектом автомобиля
    Car car;
    car.setSpeed(20);
    car.setAcceleration(3);
    car.setAngle(30);

    cout << "Before update:\n";
    car.printState();

    car.updatePosition(2);

    cout << "After update:\n";
    car.printState();

    return 0;
}