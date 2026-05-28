#include <iostream>
#include <string>
#include <vector>

class Base {
public:
    int base_val;
    Base() : base_val(1) {}
    virtual ~Base() {}
};

class Layer1_Left : public Base { public: int l1_l; };
class Layer1_middle : public Base { public: int l1_m; };
class Layer1_right : public Base { public: int l1_r; };

class Layer2_Left : public Layer1_Left, public Layer1_middle { public: int l2_l; };
class Layer2_Right : public Layer1_middle, public Layer1_right { public: int l2_r; };

class Top_Left : public Layer2_Left { public: int top_l; };
class Top_Right : public Layer2_Right { public: int top_r; };

class VLayer1_Left : virtual public Base { public: int l1_l; };
class VLayer1_middle : virtual public Base { public: int l1_m; };
class VLayer1_right : virtual public Base { public: int l1_r; };

class VLayer2_Left : public VLayer1_Left, public VLayer1_middle { public: int l2_l; };
class VLayer2_Right : public VLayer1_middle, public VLayer1_right { public: int l2_r; };

class VTop_Left : public VLayer2_Left { public: int top_l; };
class VTop_Right : public VLayer2_Right { public: int top_r; };

class Data {
public:
    virtual void display() const = 0;
    virtual void save() const = 0;
    virtual void process() = 0;
    virtual ~Data() {}
};

class SignalData : public Data {
private:
    std::vector<double> amplitude;
    std::string signal_name;
public:
    SignalData(std::string name, std::vector<double> amplic) : signal_name(name), amplitude(amplic) {}

    void display() const override {
        std::cout << "Signal Data: " << signal_name << "\nValues: ";
        for (double val : amplitude) std::cout << val << " ";
        std::cout << "\n";
    }
    void save() const override {
        std::cout << "Saved: " << signal_name << "\n";
    }
    void process() override {
        for (double& val : amplitude) val *= 1.05;
    }
};

class ResultData : public Data {
private:
    double accuracy;
    std::string status;
public:
    ResultData(double acc, std::string stat) : accuracy(acc), status(stat) {}

    void display() const override {
        std::cout << "Result: " << status << " | " << accuracy << "%\n";
    }
    void save() const override {
        std::cout << "Saved report.\n";
    }
    void process() override {
        if (accuracy > 90.0) status = "Success";
    }
};

class HelperData : public Data {
private:
    std::string timestamp;
    int sensor_id;
public:
    HelperData(int id, std::string time) : sensor_id(id), timestamp(time) {}

    void display() const override {
        std::cout << "Sensor ID: " << sensor_id << " | Time: " << timestamp << "\n";
    }
    void save() const override {
        std::cout << "Saved log for #" << sensor_id << "\n";
    }
    void process() override {}
};

class Software {
public:
    std::string version;
    Software() : version("1.0") {}
    virtual ~Software() {}
};

class OperatingSystem : virtual public Software {
public:
    std::string os_kernel;
    OperatingSystem() : os_kernel("NT") {}
};

class ApplicationSoftware : virtual public Software {
public:
    std::string app_type;
    ApplicationSoftware() : app_type("Desktop") {}
};

class Windows : public OperatingSystem, public ApplicationSoftware {
public:
    std::string win_edition;
    Windows() : win_edition("Windows 11") {}
};

int main() {
    int choice = 0;

    std::cout << "1. Task 1" << std::endl;
    std::cout << "2. Task 2" << std::endl;
    std::cout << "3. Task 3" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        Top_Right normal_obj;
        VTop_Right virtual_obj;
        std::cout << "Normal size: " << sizeof(normal_obj) << " bytes" << std::endl;
        std::cout << "Virtual size: " << sizeof(virtual_obj) << " bytes" << std::endl;
        break;
    }
    case 2: {
        Data* hardware_dataset[3];
        hardware_dataset[0] = new SignalData("ECG_01", { 0.1, 0.5, 1.2, 0.2 });
        hardware_dataset[1] = new ResultData(94.2, "Processing");
        hardware_dataset[2] = new HelperData(404, "23:15:00");

        for (int i = 0; i < 3; ++i) {
            hardware_dataset[i]->display();
            hardware_dataset[i]->process();
            hardware_dataset[i]->display();
            hardware_dataset[i]->save();
        }

        for (int i = 0; i < 3; ++i) {
            delete hardware_dataset[i];
        }
        break;
    }
    case 3: {
        Windows win_obj;
        std::cout << win_obj.win_edition << std::endl;
        std::cout << win_obj.os_kernel << std::endl;
        std::cout << win_obj.app_type << std::endl;
        std::cout << win_obj.version << std::endl;
        std::cout << "Size: " << sizeof(win_obj) << " bytes" << std::endl;
        break;
    }
    case 4:
        break;
    default:
        break;
    }

    return 0;
}