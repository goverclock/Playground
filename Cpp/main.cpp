#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Operation {
   public:
    virtual double get_result() = 0;
    virtual ~Operation() = default;

    double num_a = 0.0;
    double num_b = 0.0;
};

class AddOperation : public Operation {
   public:
    double get_result() override { return num_a + num_b; };
};

class SubOperation : public Operation {
   public:
    double get_result() override { return num_a - num_b; };
};

class OperationFactory {
   public:
    static unique_ptr<Operation> create_operation(char opr) {
        Operation* ret = nullptr;
        switch (opr) {
            case '+':
                ret = new AddOperation();
                break;
            case '-':
                ret = new SubOperation();
                break;
            default:
                // FUCK this shit
                break;
        }
        return unique_ptr<Operation>(ret);
    }
};

int main() {
    double num1 = 0.0;
    double num2 = 0.0;
    cin >> num1 >> num2;

    auto opr = OperationFactory::create_operation('+');
    opr->num_a = num1;
    opr->num_b = num2;

    cout << opr->get_result();

    return 0;
}
