#include <iostream>
#include <cstring>
using namespace std;

class Device
{
protected:

    double memorySize;
    double screenSize;
    double price;
    char *brand;
    static int counter;
    const char *constantSerial;
    // The device should have memory in GB, screen size, price, brand and constant serial number.
    // There should be a counter for the number of active devices(instances)

public:
    Device(double memorySize, double screenSize, double price, const char *brand, const char *constantSerial) {
        if(memorySize <= 0)
            throw invalid_argument("Memory must be more than 0");
        this->memorySize = memorySize;
        if(screenSize <= 0)
            throw invalid_argument("Screen Size must be more than 0");
        this->screenSize = screenSize;
        if(price <= 0)
            throw invalid_argument("Price must be more than 0");
        this->price = price;
        if(brand == nullptr || !strcmp(brand, ""))
            throw invalid_argument("Brand is empty");
        this->brand = strdup(brand);
        if(constantSerial == nullptr || !strcmp(constantSerial, ""))
            throw invalid_argument("Serial Number is empty");
        this->constantSerial = strdup(constantSerial);
        counter++;
    }

    int Device::counter = 0;

    Device(const Device &other) {
        this->memorySize = other.memorySize;
        this->screenSize = other.screenSize;
        this->price = other.price;
        this->brand = strdup(other.brand);
        this->constantSerial = strdup(other.constantSerial);
    }

    Device &operator=(const Device &other) {
        if(this != &other) {
            delete[] this->brand;
            delete[] this->constantSerial;
            this->memorySize = other.memorySize;
            this->screenSize = other.screenSize;
            this->price = other.price;
            this->brand = strdup(other.brand);
            this->constantSerial = strdup(other.constantSerial);
        }
        return *this;
    }

    /*
         (memory*size) / price greater than 0.1 is worth buying
    */
    bool isWorthBuying() const {
        if((memorySize * screenSize) / price > 0.1)
            return true;
        return false;
    }

    // Getters and setters

    double getMemorySize() const {
        return memorySize;
    }

    double getScreenSize() const {
        return screenSize;
    }

    double getPrice() const {
        return price;
    }

    char* getBrand() const {
        return brand;
    }

    const char* getSerialNumber() const {
        return constantSerial;
    }

protected:

    void setMemorySize(double memorySize) {
        this->memorySize = memorySize;
    }

    void setScreenSize(double screenSize) {
        this->screenSize = screenSize;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void setBrand(char *brand) {
        this->brand = strdup(brand);
    }

    void setSerialNumber(const char *constantSerial) {
        this->constantSerial = constantSerial;
    }
};

class Phone : public Device
{
    int cameraParameters;

public:
    Phone(double memorySize, double screenSize, double price, const char *brand, const char *constantSerial, int cameraParameters) 
    : Device(memorySize, screenSize, price, brand, constantSerial)
    {
        if(cameraParameters <= 0) 
            throw invalid_argument("Camera Parameters must be more than 0");
        this->cameraParameters = cameraParameters;
    }
    Phone(const Phone &other) 
    : Device(other)
    {
        this->cameraParameters = other.cameraParameters;
    }
    Phone &operator=(const Phone &other) {
        Device::operator=(other);
        if(this != &other) {
            this->cameraParameters = other.cameraParameters;
        }
        return *this;
    }

    /*
         (memory*size) + (memory*cameraParameters) / price greater than 0.1 is worth buying
    */
    bool isWorthBuying() const {
        if((memorySize * screenSize + memorySize * cameraParameters) / price >= 0.1)
            return true;
        return false;
    }

    // Getters and setters
    
    double getMemorySize() const {
        return memorySize;
    }

    double getScreenSize() const {
        return screenSize;
    }

    double getPrice() const {
        return price;
    }

    char* getBrand() const {
        return brand;
    }

    const char* getSerialNumber() const {
        return constantSerial;
    }

    int getCameraParameters() const {
        return cameraParameters;
    }

protected:

    void setMemorySize(double memorySize) {
        this->memorySize = memorySize;
    }

    void setScreenSize(double screenSize) {
        this->screenSize = screenSize;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void setBrand(char *brand) {
        this->brand = strdup(brand);
    }

    void setSerialNumber(const char *constantSerial) {
        this->constantSerial = constantSerial;
    }

    void setCameraParameters(int cameraParameters) {
        this->cameraParameters = cameraParameters;
    }
};