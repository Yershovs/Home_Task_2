#include <iostream>
#include <stdexcept>
#define EPS 1e-12

class Value {
public:
    virtual Value* CreateZeroValue() = 0;
    virtual Value* Duplicate() = 0;

    virtual Value& operator+=(const Value&) = 0;
    virtual Value& operator-=(const Value&) = 0;
    virtual Value& operator*=(const Value&) = 0;
    virtual Value& operator/=(const Value&) = 0;

    virtual Value& operator+(const Value&) = 0;
    virtual Value& operator-(const Value&) = 0;
    virtual Value& operator*(const Value&) = 0;
    virtual Value& operator/(const Value&) = 0;

    virtual Value& operator-() = 0;

    virtual ~Value() {}
};

class RealValue : public Value {
  public:
  double value;
  //Конструктор - он будет свой у каждого класса RealValue и ComplexValue  
  RealValue(): value(0){}
  RealValue(double r_value) : value(r_value){}
  Value* CreateZeroValue() override{
    return new RealValue(0);
  }
  Value* Duplicate() override{
    return new RealValue(value);
  }

  Value& operator+=(const Value& other) override { 
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)) {
      value += realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in addition");
    }
    return *this; 
  }
  Value& operator-=(const Value& other) override { 
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)) {
      value -= realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in differense");
    }
    return *this; 
  }
  Value& operator*=(const Value& other) override { 
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)) {
      value *= realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in multiplication");
    }
    return *this; 
  }
  Value& operator/=(const Value& other) override { 
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)){
      if(!((realOther->value < 0+EPS) && (realOther->value > 0-EPS))){
        value /= realOther->value;
      }else{
        throw std::invalid_argument("Dividing by zero");
      }
    }else{
      throw std::invalid_argument("Unknown type in division");
    }
    return *this; 
  }

   RealValue& operator+(const Value& other) override{
    RealValue* v;
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)){
      v->value = value + realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in binary addition");
    }
    return *v; 
   }
   RealValue& operator-(const Value& other) override{
    RealValue* v;
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)){
      v->value = value + realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in binary addition");
    }
    return *v; 
   }
   RealValue& operator*(const Value& other) override{
    RealValue* v;
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)){
      v->value = value * realOther->value;
    }else{
      throw std::invalid_argument("Unknown type in binary addition");
    }
    return *v; 
   }
  RealValue& operator/(const Value& other) override{
    RealValue* v;
    if (const RealValue* realOther = dynamic_cast<const RealValue*>(&other)){
      if(!((realOther->value < 0+EPS) && (realOther->value > 0-EPS))){
        v->value = value / realOther->value;
      }else{
        throw std::invalid_argument("Dividing by zero");
      }
    }else{
      throw std::invalid_argument("Unknown type in binary addition");
    }
    return *v; 
   }

   RealValue& operator-(){
    this->value *= -1;
    return *this;
   }

};

class ComplexValue : public Value {
  public:
  double re_part;
  double im_part;
  //Конструктор - он будет свой у каждого класса RealValue и ComplexValue
  ComplexValue() : re_part(0), im_part(0){}
  ComplexValue(double re_part_of_value, double im_part_of_value) : re_part(re_part_of_value), im_part(im_part_of_value){}
  Value* CreateZeroValue() override{
    return new ComplexValue(0, 0);
  }
  Value* Duplicate() override{
    return new ComplexValue(re_part, im_part);
  }
  Value& operator+=(const Value& other) override {
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)) {
      re_part += complexOther->re_part;
      im_part += complexOther->im_part;
    }else{
      throw std::invalid_argument("Unknown type in addition");
    }
    return *this;
  }
  Value& operator-=(const Value& other) override {
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)) {
      re_part -= complexOther->re_part;
      im_part -= complexOther->im_part;
    }else{
      throw std::invalid_argument("Unknown type in difference");
    }
    return *this;
  }
  Value& operator*=(const Value& other) override {
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)) {
      double re_1 = re_part*complexOther->re_part - im_part*complexOther->im_part;
      double im_1 = re_part*complexOther->im_part + complexOther->re_part*im_part;
      re_part = re_1;
      im_part = im_1;
    }else{
      throw std::invalid_argument("Unknown type in multiplication");
    }
    return *this;
  }
  Value& operator/=(const Value& other) override {
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)) {
      if(!(((complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part) < 0+EPS) && ((complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part) > 0-EPS))){
        double re_1 = (re_part*complexOther->re_part + im_part*complexOther->im_part)/(complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part);
        double im_1 = (re_part*complexOther->im_part - complexOther->re_part*im_part)/(complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part);
        re_part = re_1;
        im_part = im_1;
      }else{
        throw std::invalid_argument("Dividing by zero");
      }
    }else{
      throw std::invalid_argument("Unknown type in division");
    }
    return *this;
  }
  ComplexValue& operator+(const Value& other) override{
    ComplexValue* complexNew;
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)){
      complexNew->re_part = re_part + complexOther->re_part;
      complexNew->im_part = im_part + complexOther->im_part;
    }else{
      throw std::invalid_argument("Unknown type in addition");
    }
    return *complexNew;
  }  
  ComplexValue& operator-(const Value& other) override{
    ComplexValue* complexNew;
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)){
      complexNew->re_part = re_part + complexOther->re_part;
      complexNew->im_part = im_part + complexOther->im_part;
    }else{
      throw std::invalid_argument("Unknown type in addition");
    }
    return* complexNew;
  } 
  ComplexValue& operator*(const Value& other) override{
    ComplexValue* complexNew;
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)){
      complexNew->re_part = re_part*complexOther->re_part - im_part*complexOther->im_part;
      complexNew->im_part = re_part*complexOther->im_part + complexOther->re_part*im_part;
    }else{
      throw std::invalid_argument("Unknown type in addition");
    }
    return* complexNew;
  } 
  ComplexValue& operator/(const Value& other) override {
    ComplexValue* complexNew;
    if (const ComplexValue* complexOther = dynamic_cast<const ComplexValue*>(&other)) {
      if(!(((complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part) < 0+EPS) && ((complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part) > 0-EPS))){
        complexNew->re_part = (re_part*complexOther->re_part + im_part*complexOther->im_part)/(complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part);
        complexNew->im_part = (re_part*complexOther->im_part - complexOther->re_part*im_part)/(complexOther->re_part*complexOther->re_part+complexOther->im_part*complexOther->im_part);
      }else{
        throw std::invalid_argument("Dividing by zero");
      }
    }else{
      throw std::invalid_argument("Unknown type in division");
    }
    return* complexNew;
  }
  ComplexValue& operator-(){
    this->re_part *= -1;
    this->im_part *= -1;
    return *this;
  }
};

// Функция для решения уравнения ax + b = 0 для RealValue и ComplexValue
void Solve(Value& a, Value& b, Value& result) {
  b /= -a;
}

int main(void){

  try{
  RealValue a(2);
  RealValue b(4);
  RealValue c;
  Solve(a, b, c);
  std::cout << "Test 1: "; 
  std::cout<< b.value << std::endl;
  }catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
  }

  try{
  ComplexValue a_1 (3, 6);
  ComplexValue b_1 (3, 3);
  ComplexValue c_1;
  Solve(a_1, b_1, c_1);
  std::cout << "Test 2: "; 
  std::cout << b_1.re_part << " + "<< b_1.im_part << "i" <<  std::endl;
  }catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
  }

  return 0;
}